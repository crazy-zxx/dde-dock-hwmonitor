// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "hwmonitorapplet.h"

#include "monitorbackend.h"
#include "settings.h"

#include <DGuiApplicationHelper>
#include <pluginfactory.h>

using Dtk::Gui::DGuiApplicationHelper;

HwMonitorApplet::HwMonitorApplet(QObject *parent)
    : DApplet(parent)
{
    qWarning() << "[hwmonitor] applet constructed";
}

HwMonitorApplet::~HwMonitorApplet() = default;

QObject *HwMonitorApplet::monitor() const
{
    return m_backend;
}

QObject *HwMonitorApplet::settings() const
{
    return m_settings;
}

bool HwMonitorApplet::load()
{
    qWarning() << "[hwmonitor] applet load()";
    m_settings = new Settings(this);
    m_backend = new MonitorBackend(this);
    m_backend->setPollInterval(m_settings->pollInterval());
    connect(m_settings, &Settings::pollIntervalChanged, this, [this]() {
        m_backend->setPollInterval(m_settings->pollInterval());
    });
    m_backend->setNetInterface(m_settings->netInterface());
    connect(m_settings, &Settings::netInterfaceChanged, this, [this]() {
        m_backend->setNetInterface(m_settings->netInterface());
    });
    connect(m_settings, &Settings::enabledChanged, this, [this]() {
        // 退出（禁用）时彻底停止监控采集；重新启用时恢复
        if (m_settings->enabled())
            m_backend->start();
        else
            m_backend->stop();
    });
    return DApplet::load();
}

bool HwMonitorApplet::init()
{
    DApplet::init();
    qWarning() << "[hwmonitor] applet init()";

    updateThemeType();

    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this,
            [this](DGuiApplicationHelper::ColorType) { updateThemeType(); });
    connect(m_settings, &Settings::themeModeChanged, this, [this]() { updateThemeType(); });

    // 若上次退出过（enabled=false），启动时不采集
    if (m_settings->enabled())
        m_backend->start();
    return true;
}

void HwMonitorApplet::updateThemeType()
{
    const QString mode = m_settings->themeMode();
    int type = 0;
    if (mode == QLatin1String("dark")) {
        type = DGuiApplicationHelper::DarkType;
    } else if (mode == QLatin1String("light")) {
        type = DGuiApplicationHelper::LightType;
    } else {
        type = DGuiApplicationHelper::instance()->themeType();
    }

    if (type != m_themeType) {
        m_themeType = type;
        Q_EMIT themeTypeChanged();
    }
}

D_APPLET_CLASS(HwMonitorApplet)
#include "hwmonitorapplet.moc"
