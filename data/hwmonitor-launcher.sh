#!/bin/sh
# 启动/重新启用 DDE Dock 硬件监控插件（带单实例保护）
#
# 行为：
#   1. 单实例锁：防止快速重复点击/双击导致并发执行、重复重启任务栏；
#      拿不到锁说明已有实例在处理，直接退出。
#   2. 运行检查：插件已启用（enabled=true，正在任务栏显示）时不再做任何事；
#      仅当插件被“退出程序”隐藏（enabled=false）时才重新启用并刷新任务栏。
set -e

APP="org.deepin.dde.shell"
KEY="org.deepin.ds.dock.hwmonitor"
LOCK="${XDG_RUNTIME_DIR:-/tmp}/dde-dock-hwmonitor.lock"

# 非阻塞获取单实例锁：已有实例在运行则直接退出，避免重复启动
exec 9>"$LOCK"
if ! flock -n 9; then
    exit 0
fi

CURRENT="$(dde-dconfig get -a "$APP" -r "$KEY" -k enabled 2>/dev/null | tr -d '"')"
if [ "$CURRENT" != "true" ]; then
    # 插件处于退出状态：重新启用并刷新任务栏
    dde-dconfig set -a "$APP" -r "$KEY" -k enabled -v true
    systemctl --user restart dde-shell@DDE.service 2>/dev/null || true
fi
exit 0
