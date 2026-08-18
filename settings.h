// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>
#include <QStringList>
#include <QVariantMap>

namespace Dtk {
namespace Core {
class DConfig;
}
}

/**
 * @brief 通过 DConfig 持久化的插件设置
 *
 * 设置项：主题模式（自动/亮色/暗色）、单行/双行显示、
 * 监控项显隐与排序、自定义文字颜色、刷新间隔。
 */
class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString themeMode READ themeMode WRITE setThemeMode NOTIFY themeModeChanged FINAL)
    Q_PROPERTY(QString displayMode READ displayMode WRITE setDisplayMode NOTIFY displayModeChanged FINAL)
    Q_PROPERTY(QString dockPosition READ dockPosition WRITE setDockPosition NOTIFY dockPositionChanged FINAL)
    Q_PROPERTY(QString netInterface READ netInterface WRITE setNetInterface NOTIFY netInterfaceChanged FINAL)
    Q_PROPERTY(QString fontFamily READ fontFamily WRITE setFontFamily NOTIFY fontFamilyChanged FINAL)
    Q_PROPERTY(int fontSize READ fontSize WRITE setFontSize NOTIFY fontSizeChanged FINAL)
    Q_PROPERTY(bool useCustomColor READ useCustomColor WRITE setUseCustomColor NOTIFY useCustomColorChanged FINAL)
    Q_PROPERTY(QString textColorLight READ textColorLight WRITE setTextColorLight NOTIFY textColorLightChanged FINAL)
    Q_PROPERTY(QString textColorDark READ textColorDark WRITE setTextColorDark NOTIFY textColorDarkChanged FINAL)
    Q_PROPERTY(QStringList itemOrder READ itemOrder NOTIFY itemOrderChanged FINAL)
    Q_PROPERTY(QVariantMap itemVisible READ itemVisible NOTIFY itemVisibleChanged FINAL)
    Q_PROPERTY(QVariantMap itemWidth READ itemWidth NOTIFY itemWidthChanged FINAL)
    Q_PROPERTY(int pollInterval READ pollInterval WRITE setPollInterval NOTIFY pollIntervalChanged FINAL)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(QStringList itemKeys READ itemKeys CONSTANT FINAL)

public:
    explicit Settings(QObject *parent = nullptr);

    QString themeMode() const { return m_themeMode; }
    QString displayMode() const { return m_displayMode; }
    QString dockPosition() const { return m_dockPosition; }
    QString netInterface() const { return m_netInterface; }
    QString fontFamily() const { return m_fontFamily; }
    int fontSize() const { return m_fontSize; }
    bool useCustomColor() const { return m_useCustomColor; }
    QString textColorLight() const { return m_textColorLight; }
    QString textColorDark() const { return m_textColorDark; }
    QStringList itemOrder() const { return m_itemOrder; }
    QVariantMap itemVisible() const { return m_itemVisible; }
    QVariantMap itemWidth() const { return m_itemWidth; }
    int pollInterval() const { return m_pollInterval; }
    bool enabled() const { return m_enabled; }
    QStringList itemKeys() const { return m_itemKeys; }

    Q_INVOKABLE void setThemeMode(const QString &mode);
    Q_INVOKABLE void setDisplayMode(const QString &mode);
    Q_INVOKABLE void setDockPosition(const QString &position);
    Q_INVOKABLE void setNetInterface(const QString &iface);
    Q_INVOKABLE void setFontFamily(const QString &family);
    Q_INVOKABLE void setFontSize(int size);
    Q_INVOKABLE void resetTextColors();
    Q_INVOKABLE void setUseCustomColor(bool on);
    Q_INVOKABLE void setTextColorLight(const QString &color);
    Q_INVOKABLE void setTextColorDark(const QString &color);
    Q_INVOKABLE void setPollInterval(int ms);
    Q_INVOKABLE void setEnabled(bool on);

    Q_INVOKABLE void setItemOrder(const QStringList &order);
    Q_INVOKABLE void setItemVisible(const QString &id, bool visible);
    Q_INVOKABLE void setItemWidth(const QString &id, int chars);

Q_SIGNALS:
    void themeModeChanged();
    void displayModeChanged();
    void dockPositionChanged();
    void netInterfaceChanged();
    void fontFamilyChanged();
    void fontSizeChanged();
    void useCustomColorChanged();
    void textColorLightChanged();
    void textColorDarkChanged();
    void itemOrderChanged();
    void itemVisibleChanged();
    void itemWidthChanged();
    void pollIntervalChanged();
    void enabledChanged();

private:
    void reload();

    Dtk::Core::DConfig *m_config = nullptr;

    QString m_themeMode = QStringLiteral("auto");
    QString m_displayMode = QStringLiteral("single");
    QString m_dockPosition = QStringLiteral("right");
    QString m_netInterface;
    QString m_fontFamily = QStringLiteral("DejaVu Sans Mono");
    int m_fontSize = 10;
    bool m_useCustomColor = false;
    QString m_textColorLight = QStringLiteral("#262626");
    QString m_textColorDark = QStringLiteral("#E6E6E6");
    QStringList m_itemOrder = {QStringLiteral("cpu"), QStringLiteral("gpu"), QStringLiteral("memory"),
                               QStringLiteral("cputemp"), QStringLiteral("gputemp"), QStringLiteral("netspeed")};
    QVariantMap m_itemVisible;
    QVariantMap m_itemWidth;
    int m_pollInterval = 1000;
    bool m_enabled = true;
    const QStringList m_itemKeys = {QStringLiteral("cpu"), QStringLiteral("memory"), QStringLiteral("gpu"),
                                    QStringLiteral("cputemp"), QStringLiteral("gputemp"), QStringLiteral("netspeed")};
};
