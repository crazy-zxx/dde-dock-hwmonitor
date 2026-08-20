// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QElapsedTimer>
#include <QObject>

class QProcess;
class QTimer;

/**
 * @brief 硬件信息采集后端
 *
 * 从 /proc 与 /sys 读取 CPU 使用率、内存使用率、GPU 使用率、
 * CPU/GPU 温度以及网络上传下载速度，并通过 Q_PROPERTY 暴露给 QML。
 */
class MonitorBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cpuUsage READ cpuUsage NOTIFY updated FINAL)
    Q_PROPERTY(double memUsage READ memUsage NOTIFY updated FINAL)
    Q_PROPERTY(double gpuUsage READ gpuUsage NOTIFY updated FINAL)
    Q_PROPERTY(double gpuMemoryUsage READ gpuMemoryUsage NOTIFY updated FINAL)
    Q_PROPERTY(double cpuTemp READ cpuTemp NOTIFY updated FINAL)
    Q_PROPERTY(double gpuTemp READ gpuTemp NOTIFY updated FINAL)
    Q_PROPERTY(double netDownSpeed READ netDownSpeed NOTIFY updated FINAL)
    Q_PROPERTY(double netUpSpeed READ netUpSpeed NOTIFY updated FINAL)
    Q_PROPERTY(bool gpuAvailable READ gpuAvailable NOTIFY availabilityChanged FINAL)
    Q_PROPERTY(bool gpuMemoryAvailable READ gpuMemoryAvailable NOTIFY updated FINAL)
    Q_PROPERTY(bool cpuTempAvailable READ cpuTempAvailable NOTIFY availabilityChanged FINAL)
    Q_PROPERTY(bool gpuTempAvailable READ gpuTempAvailable NOTIFY availabilityChanged FINAL)
    Q_PROPERTY(int pollInterval READ pollInterval WRITE setPollInterval NOTIFY pollIntervalChanged FINAL)
    Q_PROPERTY(QStringList netInterfaces READ netInterfaces CONSTANT FINAL)

public:
    explicit MonitorBackend(QObject *parent = nullptr);

    void start();
    void stop();

    double cpuUsage() const { return m_cpuUsage; }
    double memUsage() const { return m_memUsage; }
    double gpuUsage() const { return m_gpuUsage; }
    double gpuMemoryUsage() const { return m_gpuMemoryUsage; }
    double cpuTemp() const { return m_cpuTemp; }
    double gpuTemp() const { return m_gpuTemp; }
    double netDownSpeed() const { return m_netDownSpeed; }
    double netUpSpeed() const { return m_netUpSpeed; }
    bool gpuAvailable() const { return m_gpuAvailable; }
    bool gpuMemoryAvailable() const { return m_gpuMemoryAvailable; }
    bool cpuTempAvailable() const { return m_cpuTempAvailable; }
    bool gpuTempAvailable() const { return m_gpuTempAvailable; }
    int pollInterval() const { return m_pollInterval; }
    void setPollInterval(int ms);

    QStringList netInterfaces() const { return m_netInterfaces; }
    void setNetInterface(const QString &iface);

Q_SIGNALS:
    void updated();
    void availabilityChanged();
    void pollIntervalChanged();

private Q_SLOTS:
    void refresh();
    void onNvidiaFinished();

private:
    enum class GpuKind {
        NoGpu,
        AmdGpu,
        NvidiaGpu,
    };

    void detectHardware();
    void detectNetInterfaces();
    void readCpuUsage();
    void readMemUsage();
    void readGpu();
    void readGpuMemory();
    void readTemps();
    void readNetSpeed();

    static qulonglong readCpuTimes(qulonglong &user, qulonglong &nice, qulonglong &system,
                                   qulonglong &idle, qulonglong &iowait, qulonglong &irq,
                                   qulonglong &softirq, qulonglong &steal);
    static qint64 readMilliDegrees(const QString &path);
    static QString findTempInput(const QString &hwmonDir, const QStringList &preferredLabels = {});
    static bool isCpuHwmon(const QString &name);

    QTimer *m_timer = nullptr;
    int m_pollInterval = 1000;

    double m_cpuUsage = 0.0;
    double m_memUsage = 0.0;
    double m_gpuUsage = -1.0;
    double m_gpuMemoryUsage = -1.0;
    double m_cpuTemp = -1.0;
    double m_gpuTemp = -1.0;
    double m_netDownSpeed = 0.0;
    double m_netUpSpeed = 0.0;

    bool m_gpuAvailable = false;
    bool m_gpuMemoryAvailable = false;
    bool m_cpuTempAvailable = false;
    bool m_gpuTempAvailable = false;

    // CPU
    bool m_cpuValid = false;
    qulonglong m_prevUser = 0, m_prevNice = 0, m_prevSystem = 0, m_prevIdle = 0;
    qulonglong m_prevIowait = 0, m_prevIrq = 0, m_prevSoftirq = 0, m_prevSteal = 0;

    // GPU
    GpuKind m_gpuKind = GpuKind::NoGpu;
    QString m_gpuBusyPath;
    QString m_gpuMemoryUsedPath;
    QString m_gpuMemoryTotalPath;
    QProcess *m_nvidiaProcess = nullptr;

    // 温度
    QString m_cpuTempPath;
    QString m_gpuTempPath;

    // 网络
    QElapsedTimer m_netTimer;
    bool m_netValid = false;
    qulonglong m_lastRxBytes = 0;
    qulonglong m_lastTxBytes = 0;
    QStringList m_netInterfaces;
    QString m_selectedInterface;
};
