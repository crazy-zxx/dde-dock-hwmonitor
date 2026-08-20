// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "settings.h"

#include <DConfig>

#include <QDebug>

namespace {
constexpr char kAppId[] = "org.deepin.dde.shell";
constexpr char kConfigId[] = "org.deepin.ds.dock.hwmonitor";
constexpr int kDefaultItemWidth = 3;
constexpr int kDefaultNetworkWidth = 5;
}

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    m_config = Dtk::Core::DConfig::create(QLatin1String(kAppId), QLatin1String(kConfigId), QString(), this);
    if (!m_config || !m_config->isValid()) {
        qWarning() << "[hwmonitor] DConfig unavailable, using built-in defaults";
    } else {
        connect(m_config, &Dtk::Core::DConfig::valueChanged, this, [this](const QString &) {
            reload();
        });
    }
    reload();
}

void Settings::reload()
{
    auto value = [this](const char *key, const QVariant &fallback) {
        return m_config && m_config->isValid() ? m_config->value(QLatin1String(key), fallback) : fallback;
    };

    const QString displayMode = value("displayMode", m_displayMode).toString();
    if (displayMode != m_displayMode) {
        m_displayMode = displayMode;
        Q_EMIT displayModeChanged();
    }

    const QString dockPosition = value("dockPosition", m_dockPosition).toString();
    if (dockPosition != m_dockPosition) {
        m_dockPosition = dockPosition;
        Q_EMIT dockPositionChanged();
    }

    const QString netInterface = value("netInterface", m_netInterface).toString();
    if (netInterface != m_netInterface) {
        m_netInterface = netInterface;
        Q_EMIT netInterfaceChanged();
    }

    const QString fontFamily = value("fontFamily", m_fontFamily).toString();
    if (fontFamily != m_fontFamily) {
        m_fontFamily = fontFamily;
        Q_EMIT fontFamilyChanged();
    }

    const int fontSize = value("fontSize", m_fontSize).toInt();
    if (fontSize != m_fontSize) {
        m_fontSize = fontSize;
        Q_EMIT fontSizeChanged();
    }

    const bool useCustomColor = value("useCustomColor", m_useCustomColor).toBool();
    if (useCustomColor != m_useCustomColor) {
        m_useCustomColor = useCustomColor;
        Q_EMIT useCustomColorChanged();
    }

    const QString textColorLight = value("textColorLight", m_textColorLight).toString();
    if (textColorLight != m_textColorLight) {
        m_textColorLight = textColorLight;
        Q_EMIT textColorLightChanged();
    }

    const QString textColorDark = value("textColorDark", m_textColorDark).toString();
    if (textColorDark != m_textColorDark) {
        m_textColorDark = textColorDark;
        Q_EMIT textColorDarkChanged();
    }

    const QStringList itemOrder = value("itemOrder", m_itemOrder).toStringList();
    const bool legacyNetItems = itemOrder.contains(QStringLiteral("netspeed"));
    QStringList filtered;
    for (const QString &id : itemOrder) {
        if (id == QLatin1String("netspeed")) {
            if (!filtered.contains(QStringLiteral("netup")))
                filtered.append(QStringLiteral("netup"));
            if (!filtered.contains(QStringLiteral("netdown")))
                filtered.append(QStringLiteral("netdown"));
        } else if (m_itemKeys.contains(id) && !filtered.contains(id)) {
            filtered.append(id);
        }
    }
    for (const QString &id : m_itemKeys) {
        if (!filtered.contains(id))
            filtered.append(id);
    }
    if (filtered != m_itemOrder) {
        m_itemOrder = filtered;
        Q_EMIT itemOrderChanged();
    }

    QVariantMap visible;
    const bool legacyNetVisible = value("visible_netspeed", true).toBool();
    for (const QString &id : m_itemKeys) {
        const bool isNetItem = id == QLatin1String("netup") || id == QLatin1String("netdown");
        const bool fallback = isNetItem ? legacyNetVisible : true;
        const bool visibleValue = legacyNetItems && isNetItem
                ? legacyNetVisible
                : value(("visible_" + id).toUtf8().constData(), fallback).toBool();
        visible.insert(id, visibleValue);
    }
    if (visible != m_itemVisible) {
        m_itemVisible = visible;
        Q_EMIT itemVisibleChanged();
    }

    QVariantMap width;
    const int legacyNetWidth = value("width_netspeed", 0).toInt();
    for (const QString &id : m_itemKeys) {
        const bool isNetItem = id == QLatin1String("netup") || id == QLatin1String("netdown");
        const int fallback = isNetItem ? kDefaultNetworkWidth : kDefaultItemWidth;
        const int widthValue = legacyNetItems && isNetItem
                ? legacyNetWidth
                : value(("width_" + id).toUtf8().constData(), fallback).toInt();
        width.insert(id, widthValue);
    }
    if (width != m_itemWidth) {
        m_itemWidth = width;
        Q_EMIT itemWidthChanged();
    }

    const int pollInterval = value("pollInterval", m_pollInterval).toInt();
    if (pollInterval != m_pollInterval) {
        m_pollInterval = pollInterval;
        Q_EMIT pollIntervalChanged();
    }

    const bool enabled = value("enabled", m_enabled).toBool();
    if (enabled != m_enabled) {
        m_enabled = enabled;
        Q_EMIT enabledChanged();
    }
}

void Settings::setDisplayMode(const QString &mode)
{
    if (mode == m_displayMode)
        return;
    m_displayMode = mode;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("displayMode"), mode);
    Q_EMIT displayModeChanged();
}

void Settings::setDockPosition(const QString &position)
{
    if (position == m_dockPosition)
        return;
    m_dockPosition = position;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("dockPosition"), position);
    Q_EMIT dockPositionChanged();
}

void Settings::setNetInterface(const QString &iface)
{
    if (iface == m_netInterface)
        return;
    m_netInterface = iface;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("netInterface"), iface);
    Q_EMIT netInterfaceChanged();
}

void Settings::setFontFamily(const QString &family)
{
    if (family == m_fontFamily)
        return;
    m_fontFamily = family;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("fontFamily"), family);
    Q_EMIT fontFamilyChanged();
}

void Settings::setFontSize(int size)
{
    size = qBound(6, size, 24);
    if (size == m_fontSize)
        return;
    m_fontSize = size;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("fontSize"), size);
    Q_EMIT fontSizeChanged();
}

void Settings::resetTextColors()
{
    setUseCustomColor(false);
    if (m_textColorLight != QStringLiteral("#262626"))
        setTextColorLight(QStringLiteral("#262626"));
    if (m_textColorDark != QStringLiteral("#E6E6E6"))
        setTextColorDark(QStringLiteral("#E6E6E6"));
}

void Settings::setUseCustomColor(bool on)
{
    if (on == m_useCustomColor)
        return;
    m_useCustomColor = on;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("useCustomColor"), on);
    Q_EMIT useCustomColorChanged();
}

void Settings::setTextColorLight(const QString &color)
{
    if (color == m_textColorLight)
        return;
    m_textColorLight = color;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("textColorLight"), color);
    Q_EMIT textColorLightChanged();
}

void Settings::setTextColorDark(const QString &color)
{
    if (color == m_textColorDark)
        return;
    m_textColorDark = color;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("textColorDark"), color);
    Q_EMIT textColorDarkChanged();
}

void Settings::setPollInterval(int ms)
{
    ms = qBound(200, ms, 10000);
    if (ms == m_pollInterval)
        return;
    m_pollInterval = ms;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("pollInterval"), ms);
    Q_EMIT pollIntervalChanged();
}

void Settings::setEnabled(bool on)
{
    if (on == m_enabled)
        return;
    m_enabled = on;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("enabled"), on);
    Q_EMIT enabledChanged();
}

void Settings::setItemOrder(const QStringList &order)
{
    QStringList filtered;
    for (const QString &id : order) {
        if (id == QLatin1String("netspeed")) {
            if (!filtered.contains(QStringLiteral("netup")))
                filtered.append(QStringLiteral("netup"));
            if (!filtered.contains(QStringLiteral("netdown")))
                filtered.append(QStringLiteral("netdown"));
        } else if (m_itemKeys.contains(id) && !filtered.contains(id)) {
            filtered.append(id);
        }
    }
    for (const QString &id : m_itemKeys) {
        if (!filtered.contains(id))
            filtered.append(id);
    }
    if (filtered == m_itemOrder)
        return;
    m_itemOrder = filtered;
    if (m_config && m_config->isValid())
        m_config->setValue(QStringLiteral("itemOrder"), QVariant::fromValue(filtered));
    Q_EMIT itemOrderChanged();
}

void Settings::setItemVisible(const QString &id, bool visible)
{
    if (!m_itemKeys.contains(id) || m_itemVisible.value(id).toBool() == visible)
        return;
    m_itemVisible.insert(id, visible);
    if (m_config && m_config->isValid())
        m_config->setValue(("visible_" + id), visible);
    Q_EMIT itemVisibleChanged();
}

void Settings::setItemWidth(const QString &id, int chars)
{
    if (!m_itemKeys.contains(id))
        return;
    chars = qBound(0, chars, 20);
    if (m_itemWidth.value(id).toInt() == chars)
        return;
    m_itemWidth.insert(id, chars);
    if (m_config && m_config->isValid())
        m_config->setValue(("width_" + id), chars);
    Q_EMIT itemWidthChanged();
}
