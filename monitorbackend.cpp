// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "monitorbackend.h"

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTimer>

MonitorBackend::MonitorBackend(QObject *parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(m_pollInterval);
    connect(m_timer, &QTimer::timeout, this, &MonitorBackend::refresh);

    detectHardware();
    refresh();
}

void MonitorBackend::start()
{
    if (!m_timer->isActive())
        m_timer->start();
}

void MonitorBackend::stop()
{
    m_timer->stop();
}

void MonitorBackend::setPollInterval(int ms)
{
    ms = qBound(200, ms, 10000);
    if (ms == m_pollInterval)
        return;
    m_pollInterval = ms;
    m_timer->setInterval(ms);
    Q_EMIT pollIntervalChanged();
}

void MonitorBackend::detectHardware()
{
    // ---- GPU：优先 AMD amdgpu sysfs，其次 NVIDIA nvidia-smi ----
    const QDir drmDir(QStringLiteral("/sys/class/drm"));
    const QStringList cards = drmDir.entryList({QStringLiteral("card*")}, QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &card : cards) {
        const QString busyPath = drmDir.filePath(card) + QStringLiteral("/device/gpu_busy_percent");
        if (QFile::exists(busyPath)) {
            m_gpuBusyPath = busyPath;
            m_gpuMemoryUsedPath = drmDir.filePath(card) + QStringLiteral("/device/mem_info_vram_used");
            m_gpuMemoryTotalPath = drmDir.filePath(card) + QStringLiteral("/device/mem_info_vram_total");
            m_gpuKind = GpuKind::AmdGpu;
            m_gpuAvailable = true;
            break;
        }
    }
    if (m_gpuKind == GpuKind::NoGpu && !QStandardPaths::findExecutable(QStringLiteral("nvidia-smi")).isEmpty()) {
        m_gpuKind = GpuKind::NvidiaGpu;
        m_gpuAvailable = true;
    }

    // ---- 温度：扫描 hwmon ----
    const QDir hwmonDir(QStringLiteral("/sys/class/hwmon"));
    const QStringList hwmons = hwmonDir.entryList({QStringLiteral("hwmon*")}, QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString &hw : hwmons) {
        const QString base = hwmonDir.filePath(hw);
        QFile nameFile(base + QStringLiteral("/name"));
        if (!nameFile.open(QIODevice::ReadOnly))
            continue;
        const QString name = QString::fromUtf8(nameFile.readAll()).trimmed();
        nameFile.close();

        if (name == QLatin1String("amdgpu")) {
            const QString p = findTempInput(base);
            if (!p.isEmpty()) {
                m_gpuTempPath = p;
                m_gpuTempAvailable = true;
            }
        } else if (isCpuHwmon(name)) {
            // k10temp/coretemp 等：优先 Tctl/Tdie/Package/Core 标签
            const QString p = findTempInput(base, {QStringLiteral("Tctl"), QStringLiteral("Tdie"),
                                                   QStringLiteral("Package"), QStringLiteral("Core 0"),
                                                   QStringLiteral("Core0")});
            if (p.isEmpty())
                m_cpuTempPath = findTempInput(base);
            else
                m_cpuTempPath = p;
            m_cpuTempAvailable = !m_cpuTempPath.isEmpty();
        }
    }

    qWarning() << "[hwmonitor] GPU kind:" << static_cast<int>(m_gpuKind)
            << "cpuTempPath:" << m_cpuTempPath << "gpuTempPath:" << m_gpuTempPath;
    detectNetInterfaces();
    Q_EMIT availabilityChanged();
}

bool MonitorBackend::isCpuHwmon(const QString &name)
{
    static const QStringList cpuNames = {
        QStringLiteral("k10temp"), QStringLiteral("coretemp"), QStringLiteral("zenpower"),
        QStringLiteral("cpu_thermal"), QStringLiteral("x86_pkg_temp"), QStringLiteral("acpitz")
    };
    return cpuNames.contains(name);
}

QString MonitorBackend::findTempInput(const QString &hwmonDir, const QStringList &preferredLabels)
{
    const QDir dir(hwmonDir);
    // 收集 temp*_input 与对应 label
    QList<QPair<QString, QString>> inputs; // path, label
    const QStringList entries = dir.entryList({QStringLiteral("temp*_input")}, QDir::Files, QDir::Name);
    for (const QString &entry : entries) {
        const QString path = dir.filePath(entry);
        const QString labelPath = path;
        QFile labelFile(labelPath.left(labelPath.size() - 5) + QStringLiteral("label")); // temp1_input -> temp1_label
        QString label;
        if (labelFile.open(QIODevice::ReadOnly)) {
            label = QString::fromUtf8(labelFile.readAll()).trimmed();
            labelFile.close();
        }
        inputs.append({path, label});
    }

    // 优先匹配首选标签
    for (const QString &preferred : preferredLabels) {
        for (const auto &item : inputs) {
            if (item.second.contains(preferred, Qt::CaseInsensitive))
                return item.first;
        }
    }
    if (!inputs.isEmpty())
        return inputs.first().first;
    return QString();
}

qint64 MonitorBackend::readMilliDegrees(const QString &path)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly))
        return -1;
    const QByteArray data = f.readAll().trimmed();
    f.close();
    bool ok = false;
    const qint64 value = data.toLongLong(&ok);
    return ok ? value : -1;
}

qulonglong MonitorBackend::readCpuTimes(qulonglong &user, qulonglong &nice, qulonglong &system,
                                        qulonglong &idle, qulonglong &iowait, qulonglong &irq,
                                        qulonglong &softirq, qulonglong &steal)
{
    QFile f(QStringLiteral("/proc/stat"));
    if (!f.open(QIODevice::ReadOnly))
        return 0;
    const QByteArray line = f.readLine();
    f.close();
    QList<QByteArray> parts = line.split(' ');
    parts.removeAll(QByteArray());
    if (parts.size() < 5)
        return 0;

    bool ok = false;
    user = parts.value(1).toULongLong(&ok);
    nice = parts.value(2).toULongLong(&ok);
    system = parts.value(3).toULongLong(&ok);
    idle = parts.value(4).toULongLong(&ok);
    iowait = parts.size() > 5 ? parts.value(5).toULongLong(&ok) : 0;
    irq = parts.size() > 6 ? parts.value(6).toULongLong(&ok) : 0;
    softirq = parts.size() > 7 ? parts.value(7).toULongLong(&ok) : 0;
    steal = parts.size() > 8 ? parts.value(8).toULongLong(&ok) : 0;
    return user + nice + system + idle + iowait + irq + softirq + steal;
}

void MonitorBackend::refresh()
{
    readCpuUsage();
    readMemUsage();
    readGpu();
    readTemps();
    readNetSpeed();
    Q_EMIT updated();
}

void MonitorBackend::setNetInterface(const QString &iface)
{
    m_selectedInterface = iface;
}

void MonitorBackend::detectNetInterfaces()
{
    // 枚举非 lo 的网卡，供设置面板选择
    QFile f(QStringLiteral("/proc/net/dev"));
    if (!f.open(QIODevice::ReadOnly))
        return;
    const QByteArray content = f.readAll();
    f.close();

    m_netInterfaces.clear();
    const QList<QByteArray> lines = content.split('\n');
    for (const QByteArray &rawLine : lines) {
        const QString line = QString::fromUtf8(rawLine).trimmed();
        if (line.startsWith(QLatin1String("Inter-")) || line.isEmpty())
            continue;
        const int colon = line.indexOf(QLatin1Char(':'));
        if (colon < 0)
            continue;
        const QString iface = line.left(colon).trimmed();
        if (iface == QLatin1String("lo"))
            continue;
        m_netInterfaces.append(iface);
    }
}

void MonitorBackend::readCpuUsage()
{
    qulonglong user = 0, nice = 0, system = 0, idle = 0;
    qulonglong iowait = 0, irq = 0, softirq = 0, steal = 0;
    const qulonglong total = readCpuTimes(user, nice, system, idle, iowait, irq, softirq, steal);
    if (total == 0)
        return;

    if (m_cpuValid) {
        const qulonglong prevTotal = m_prevUser + m_prevNice + m_prevSystem + m_prevIdle
                                   + m_prevIowait + m_prevIrq + m_prevSoftirq + m_prevSteal;
        const qulonglong prevIdle = m_prevIdle + m_prevIowait;
        const qulonglong curIdle = idle + iowait;
        const qulonglong totalDelta = total > prevTotal ? total - prevTotal : 0;
        const qulonglong idleDelta = curIdle > prevIdle ? curIdle - prevIdle : 0;
        if (totalDelta > 0)
            m_cpuUsage = (totalDelta - idleDelta) * 100.0 / totalDelta;
    }

    m_prevUser = user;
    m_prevNice = nice;
    m_prevSystem = system;
    m_prevIdle = idle;
    m_prevIowait = iowait;
    m_prevIrq = irq;
    m_prevSoftirq = softirq;
    m_prevSteal = steal;
    m_cpuValid = true;
}

void MonitorBackend::readMemUsage()
{
    // 注意：/proc/meminfo 是 size=0 的虚拟文件，不能用 while(!atEnd()) 循环
    QFile f(QStringLiteral("/proc/meminfo"));
    if (!f.open(QIODevice::ReadOnly))
        return;
    const QByteArray content = f.readAll();
    f.close();

    qulonglong total = 0, available = 0;
    const QList<QByteArray> lines = content.split('\n');
    for (const QByteArray &line : lines) {
        if (line.startsWith("MemTotal:"))
            total = line.mid(9).trimmed().split(' ').first().toULongLong();
        else if (line.startsWith("MemAvailable:"))
            available = line.mid(13).trimmed().split(' ').first().toULongLong();
        if (total > 0 && available > 0)
            break;
    }
    if (total > 0 && available > 0)
        m_memUsage = (total - available) * 100.0 / total;
}

void MonitorBackend::readGpu()
{
    if (m_gpuKind == GpuKind::AmdGpu) {
        QFile f(m_gpuBusyPath);
        if (f.open(QIODevice::ReadOnly)) {
            const QByteArray data = f.readAll().trimmed();
            f.close();
            bool ok = false;
            const double v = data.toDouble(&ok);
            m_gpuUsage = ok ? qBound(0.0, v, 100.0) : -1.0;
            m_gpuAvailable = m_gpuUsage >= 0.0;
        } else {
            m_gpuUsage = -1.0;
            m_gpuAvailable = false;
        }
        readGpuMemory();
    } else if (m_gpuKind == GpuKind::NvidiaGpu) {
        // nvidia-smi 异步读取
        if (!m_nvidiaProcess) {
            m_nvidiaProcess = new QProcess(this);
            connect(m_nvidiaProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
                    this, &MonitorBackend::onNvidiaFinished);
        }
        if (m_nvidiaProcess->state() == QProcess::NotRunning) {
            m_nvidiaProcess->start(QStringLiteral("nvidia-smi"),
                                   {QStringLiteral("--query-gpu=utilization.gpu,temperature.gpu,memory.used,memory.total"),
                                    QStringLiteral("--format=csv,noheader,nounits")});
        }
    }
}

void MonitorBackend::readGpuMemory()
{
    if (m_gpuKind != GpuKind::AmdGpu || m_gpuMemoryUsedPath.isEmpty()
        || m_gpuMemoryTotalPath.isEmpty()) {
        return;
    }

    QFile usedFile(m_gpuMemoryUsedPath);
    QFile totalFile(m_gpuMemoryTotalPath);
    if (!usedFile.open(QIODevice::ReadOnly) || !totalFile.open(QIODevice::ReadOnly)) {
        m_gpuMemoryUsage = -1.0;
        m_gpuMemoryAvailable = false;
        return;
    }

    bool usedOk = false;
    bool totalOk = false;
    const qulonglong used = usedFile.readAll().trimmed().toULongLong(&usedOk);
    const qulonglong total = totalFile.readAll().trimmed().toULongLong(&totalOk);
    if (usedOk && totalOk && total > 0) {
        m_gpuMemoryUsage = qBound(0.0, used * 100.0 / total, 100.0);
        m_gpuMemoryAvailable = true;
    } else {
        m_gpuMemoryUsage = -1.0;
        m_gpuMemoryAvailable = false;
    }
}

void MonitorBackend::onNvidiaFinished()
{
    const QByteArray out = m_nvidiaProcess->readAllStandardOutput();
    const QString line = QString::fromUtf8(out).trimmed().split(QLatin1Char('\n')).value(0);
    const QStringList parts = line.split(QLatin1Char(','));
    if (parts.size() >= 4) {
        bool ok1 = false, ok2 = false;
        bool ok3 = false, ok4 = false;
        const double usage = parts.value(0).trimmed().toDouble(&ok1);
        const double temp = parts.value(1).trimmed().toDouble(&ok2);
        const double usedMemory = parts.value(2).trimmed().toDouble(&ok3);
        const double totalMemory = parts.value(3).trimmed().toDouble(&ok4);
        if (ok1) {
            m_gpuUsage = qBound(0.0, usage, 100.0);
            m_gpuAvailable = true;
        }
        if (ok2) {
            m_gpuTemp = temp;
            m_gpuTempAvailable = true;
        }
        if (ok3 && ok4 && totalMemory > 0) {
            m_gpuMemoryUsage = qBound(0.0, usedMemory * 100.0 / totalMemory, 100.0);
            m_gpuMemoryAvailable = true;
        } else {
            m_gpuMemoryUsage = -1.0;
            m_gpuMemoryAvailable = false;
        }
        Q_EMIT updated();
    }
}

void MonitorBackend::readTemps()
{
    if (!m_cpuTempPath.isEmpty()) {
        const qint64 v = readMilliDegrees(m_cpuTempPath);
        m_cpuTemp = v >= 0 ? v / 1000.0 : -1.0;
        m_cpuTempAvailable = v >= 0;
    }
    if (!m_gpuTempPath.isEmpty() && m_gpuKind != GpuKind::NvidiaGpu) {
        const qint64 v = readMilliDegrees(m_gpuTempPath);
        m_gpuTemp = v >= 0 ? v / 1000.0 : -1.0;
        m_gpuTempAvailable = v >= 0;
    }
}

void MonitorBackend::readNetSpeed()
{
    // 注意：/proc/net/dev 是 size=0 的虚拟文件，不能用 while(!atEnd()) 循环
    QFile f(QStringLiteral("/proc/net/dev"));
    if (!f.open(QIODevice::ReadOnly))
        return;
    const QByteArray content = f.readAll();
    f.close();

    qulonglong rx = 0, tx = 0;
    const QList<QByteArray> lines = content.split('\n');
    for (const QByteArray &rawLine : lines) {
        const QString line = QString::fromUtf8(rawLine).trimmed();
        if (line.startsWith(QLatin1String("Inter-")) || line.isEmpty())
            continue;
        const int colon = line.indexOf(QLatin1Char(':'));
        if (colon < 0)
            continue;
        const QString iface = line.left(colon).trimmed();
        if (iface == QLatin1String("lo"))
            continue;
        if (!m_selectedInterface.isEmpty() && iface != m_selectedInterface)
            continue;
        const QStringList parts = line.mid(colon + 1).trimmed().split(QRegularExpression(QStringLiteral("\\s+")));
        if (parts.size() < 9)
            continue;
        rx += parts.value(0).toULongLong();
        tx += parts.value(8).toULongLong();
    }

    if (m_netValid) {
        const qint64 elapsedMs = m_netTimer.restart();
        const qint64 rxDelta = static_cast<qint64>(rx - m_lastRxBytes);
        const qint64 txDelta = static_cast<qint64>(tx - m_lastTxBytes);
        if (elapsedMs > 0) {
            m_netDownSpeed = qMax<qint64>(0, rxDelta) * 1000.0 / elapsedMs;
            m_netUpSpeed = qMax<qint64>(0, txDelta) * 1000.0 / elapsedMs;
        }
    } else {
        m_netTimer.start();
    }

    m_lastRxBytes = rx;
    m_lastTxBytes = tx;
    m_netValid = true;
}
