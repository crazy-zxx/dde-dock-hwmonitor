// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <applet.h>

DS_USE_NAMESPACE

class MonitorBackend;
class Settings;

/**
 * @brief 硬件监控 Dock Applet
 *
 * 组合硬件信息采集后端与 DConfig 设置，并暴露给 QML。
 */
class HwMonitorApplet : public DApplet
{
    Q_OBJECT
    Q_PROPERTY(QObject *monitor READ monitor CONSTANT FINAL)
    Q_PROPERTY(QObject *settings READ settings CONSTANT FINAL)
    Q_PROPERTY(int themeType READ themeType NOTIFY themeTypeChanged FINAL)

public:
    explicit HwMonitorApplet(QObject *parent = nullptr);
    ~HwMonitorApplet() override;

    bool load() override;
    bool init() override;

    QObject *monitor() const;
    QObject *settings() const;

    /**
     * @brief 当前系统主题类型
     * @return Dtk::Gui::DGuiApplicationHelper::ColorType
     */
    int themeType() const { return m_themeType; }

Q_SIGNALS:
    void themeTypeChanged();

private:
    void updateThemeType();

    MonitorBackend *m_backend = nullptr;
    Settings *m_settings = nullptr;
    int m_themeType = 0;
};
