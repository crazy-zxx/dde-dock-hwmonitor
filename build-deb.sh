#!/usr/bin/env bash
# 构建 dde-dock-hwmonitor 的 .deb 安装包
# 用法: ./build-deb.sh [版本号，默认 1.0.0]
set -euo pipefail

cd "$(dirname "$0")"
VERSION="${1:-1.0.0}"
PLUGIN_ID="org.deepin.ds.dock.hwmonitor"
ARCH="amd64"
OUT="dde-dock-hwmonitor_${VERSION}_${ARCH}.deb"

echo "==> 1/3 构建插件库与翻译 (cmake -B build -G Ninja)"
cmake -B build -G Ninja -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release >/dev/null
cmake --build build >/dev/null

echo "==> 2/3 组装安装目录"
STAGE="$(mktemp -d)"
trap 'rm -rf "$STAGE"' EXIT
ROOT="$STAGE/root"

# 注意：dde-shell 的插件库必须直接放在 dde-shell/ 目录下（与其他插件一致），
# 不能放在以插件 ID 命名的子目录里，否则 dde-shell 无法加载。
LIBDIR="usr/lib/x86_64-linux-gnu/dde-shell"
SHAREDIR="usr/share/dde-shell/${PLUGIN_ID}"
CONFDIR="usr/share/dsg/configs/org.deepin.dde.shell"
DEBIAN="DEBIAN"

mkdir -p "$ROOT/$LIBDIR" "$ROOT/$SHAREDIR/translations" "$ROOT/$CONFDIR" "$ROOT/$DEBIAN" \
         "$ROOT/usr/share/applications" "$ROOT/usr/share/icons/hicolor/scalable/apps" "$ROOT/usr/bin"
for SIZE in 16 24 32 48 64 128 256; do
    mkdir -p "$ROOT/usr/share/icons/hicolor/${SIZE}x${SIZE}/apps"
done

install -m 0644 "build/plugins/${PLUGIN_ID}.so" "$ROOT/$LIBDIR/${PLUGIN_ID}.so"
install -m 0644 package/main.qml package/SettingsPanel.qml package/metadata.json "$ROOT/$SHAREDIR/"
install -m 0644 build/org.deepin.ds.dock.hwmonitor*.qm "$ROOT/$SHAREDIR/translations/"
install -m 0644 "configs/${PLUGIN_ID}.json" "$ROOT/$CONFDIR/"
# 开始菜单启动图标
install -m 0644 "data/${PLUGIN_ID}.desktop" "$ROOT/usr/share/applications/"
install -m 0644 "data/icons/${PLUGIN_ID}.svg" "$ROOT/usr/share/icons/hicolor/scalable/apps/"
# 多尺寸 PNG 图标（开始菜单对各尺寸 PNG 兼容性最好）
for SIZE in 16 24 32 48 64 128 256; do
    install -m 0644 "data/icons/hicolor/${SIZE}x${SIZE}/apps/${PLUGIN_ID}.png" \
        "$ROOT/usr/share/icons/hicolor/${SIZE}x${SIZE}/apps/"
done
install -m 0755 data/hwmonitor-launcher.sh "$ROOT/usr/bin/hwmonitor-launcher"

# 生成 DEBIAN/control（取 debian/control 中的 Package 段并替换版本号）
awk 'BEGIN{p=0} /^Package:/{p=1} p{print}' debian/control | \
    sed "s/^Version: .*/Version: ${VERSION}/" > "$ROOT/$DEBIAN/control"
install -m 0755 debian/postinst "$ROOT/$DEBIAN/postinst"
install -m 0755 debian/postrm   "$ROOT/$DEBIAN/postrm"

echo "==> 3/3 打包 $OUT"
dpkg-deb --build --root-owner-group "$ROOT" "$OUT" >/dev/null

echo "完成: $(pwd)/$OUT"
echo
echo "安装方式:"
echo "  sudo apt install ./$OUT    # 或双击 .deb 用图形安装器安装"
echo "卸载方式:"
echo "  sudo apt remove dde-dock-hwmonitor"
