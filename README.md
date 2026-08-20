# DDE Shell Dock 硬件监控插件（org.deepin.ds.dock.hwmonitor）

一个运行在 deepin/UOS v25（dde-shell 2.x）任务栏（Dock）上的硬件监控插件，
直接以文字形式在 Dock 中显示：

- CPU 使用率
- 内存使用率
- GPU 使用率（AMD amdgpu / NVIDIA nvidia-smi）
- 显存占用（AMD amdgpu / NVIDIA nvidia-smi）
- CPU 温度（k10temp / coretemp 等）
- GPU 温度（amdgpu / nvidia-smi）
- 上传 / 下载速度（可分别配置）

点击 Dock 中的监控文字会弹出设置面板，可配置显示项显隐、排序、单行/双行显示、
文字颜色。主题始终自动跟随系统。

<img width="40%"  alt="image" src="https://github.com/user-attachments/assets/96ac4bcd-47d7-4e75-9c3f-f7ac4b7ab238" />   &nbsp; &nbsp; &nbsp; &nbsp; <img width="40%"  alt="image" src="https://github.com/user-attachments/assets/fcf64592-ceb3-4dac-8906-eb83dbb9a919" />

## 特性

| 功能 | 说明 |
|------|------|
| 监控项显隐 | 设置面板中勾选/取消勾选每个监控项（上传、下载独立） |
| 监控项排序 | 每个监控项右侧 ↑ / ↓ 按钮调整显示顺序 |
| 单行/双行显示 | `displayMode`：`single` 单行 / `double` 双行 |
| 文字颜色 | 支持「跟随主题」或自定义颜色，可分别设置亮色/暗色主题下的颜色 |
| 主题模式 | 自动跟随系统主题 |
| 刷新间隔 | `pollInterval`，默认 1000ms（200~10000ms） |
| 显示位置 | `dockPosition`：`left` 任务栏左侧 / `right` 任务栏右侧 |
| 监视网卡 | `netInterface`：留空统计全部非回环网卡，或指定单个网卡（如 `wlp3s0`） |
| 条目占位宽度 | `width_cpu` / `width_memory` / `width_gpu` / `width_gpumem` / `width_cputemp` / `width_gputemp` 默认 3，`width_netup` / `width_netdown` 默认 5；设置为 0 可恢复自动宽度，避免数值位数变化引起 Dock 宽度抖动 |
| 等宽字体 | Dock 中标签与数值统一使用等宽字体，保证相同字符数的条目占位宽度一致（% 与 ° 等字形笔画宽度略有差异属正常现象） |
| 文字字体/大小 | `fontFamily`（默认 Source Han Mono SC）与 `fontSize`（默认 10px）：优先使用中英文等宽字体，设置面板也可切换 Noto Sans Mono CJK SC、DejaVu Sans Mono、Noto Mono、Source Code Pro、Liberation Mono 或系统默认，并调整大小（6~24px） |
| 多语言对齐 | 每个条目使用统一行高并垂直居中，避免中文字体回退后与拉丁字母出现基线/高度偏移；需要严格中英文等宽时选择 CJK 等宽字体 |
| 文字颜色还原 | 设置面板「文字颜色」旁提供还原默认按钮（`resetTextColors`），一键恢复默认颜色与关闭自定义颜色 |
| 设置持久化 | 全部设置通过 DConfig 保存，重启后自动恢复 |
| 开始菜单图标 | 安装后自动在开始菜单添加「硬件监控」图标（`data/` 下的 .desktop + SVG 图标 + 启动脚本），点击图标可重新启用已退出的插件并刷新任务栏 |

## 目录结构

```
hwmonitor/
├── CMakeLists.txt                  # 构建脚本（ds_install_package）
├── build-deb.sh                    # 一键打包 .deb 分享脚本
├── debian/                         # .deb 打包元数据（control/postinst/postrm）
├── configs/
│   └── org.deepin.ds.dock.hwmonitor.json   # DConfig 元数据
├── data/
│   ├── org.deepin.ds.dock.hwmonitor.desktop # 开始菜单启动图标入口
│   ├── hwmonitor-launcher.sh               # 启动脚本（重新启用插件）
│   └── icons/org.deepin.ds.dock.hwmonitor.svg # 应用图标
├── package/
│   ├── metadata.json               # 插件元数据（Parent: org.deepin.ds.dock）
│   ├── main.qml                    # Dock 显示 + 设置弹窗
│   └── SettingsPanel.qml           # 设置面板
├── hwmonitorapplet.h / .cpp        # DApplet 主类（桥接后端与 QML）
├── monitorbackend.h / .cpp         # 硬件信息采集（/proc、/sys、nvidia-smi）
├── settings.h / .cpp               # DConfig 设置封装
├── translations/                   # lupdate 自动生成的 23 语言翻译
└── README.md
```

## 依赖

构建依赖：

- `libdde-shell-dev`（>= 2.0.x）
- `cmake`、`ninja-build`
- `qt6-base-dev`、`qt6-declarative-dev`、`qt6-tools-dev`（LinguistTools）
- `libdtk6core-dev`、`libdtk6gui-dev`

运行时依赖：

- `dde-shell`（>= 2.0）
- `libdtk6core`、`libdtk6gui`

## 分享与安装（推荐 .deb 包）

项目自带一键打包脚本，可生成 `.deb` 安装包：

```bash
# 生成 dde-dock-hwmonitor_1.0.0_amd64.deb
./build-deb.sh              

# 指定版本号
./build-deb.sh 1.1.0        
```

**安装：**

```bash
sudo apt install ./dde-dock-hwmonitor_1.0.0_amd64.deb
```

或在文件管理器中双击 `.deb` 用图形安装器安装。安装后：

- 会自动重启 `dde-dconfig-daemon` 刷新配置元数据；
- 若 Dock 没有立即出现监控文字，手动重启一下 Dock：
  ```bash
  systemctl --user restart dde-shell@DDE.service
  ```

**卸载：**

```bash
sudo apt remove dde-dock-hwmonitor
```

> 适用范围：Deepin 25 / UOS 25（dde-shell 2.x，amd64）。包内 Depends 已声明
> `dde-shell (>= 2.0)`、`libdde-shell`、`libdtk6core`、`libdtk6gui`，
> 缺失时会提示先安装依赖。

## 源码构建（开发/尝鲜）

## 构建与安装

```bash
cmake -B build -G Ninja -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release

cmake --build build

sudo cmake --install build
```

安装内容：

- 插件库：`/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so`
- QML 包：`/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/`
- DConfig 元数据：`/usr/share/dsg/configs/org.deepin.dde.shell/org.deepin.ds.dock.hwmonitor.json`
- 翻译：`/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/`
- 开始菜单图标：`/usr/share/applications/org.deepin.ds.dock.hwmonitor.desktop`、`/usr/share/icons/hicolor/scalable/apps/org.deepin.ds.dock.hwmonitor.svg`
- 启动脚本：`/usr/bin/hwmonitor-launcher`

安装后重启 Dock 生效：

```bash
systemctl --user restart dde-shell@DDE.service
```

> 若 DConfig 元数据未生效（`dde-dconfig get` 报错），重启配置守护进程：
> `sudo systemctl restart dde-dconfig-daemon.service`

## 使用

- 安装并重启 Dock 后，插件默认显示在任务栏右侧（托盘附近，`dockOrder = 21`）。
- 左键点击监控文字 → 打开设置面板。
- “退出监控”只禁用并隐藏本插件，不会退出或重启 dde-shell，因此不会影响系统主题切换和其他 Dock 插件。
- 设置面板中可勾选显示项、用 ↑ / ↓ 排序、切换单行/双行、
  启用自定义颜色并分别设置亮/暗主题下的文字颜色，主题自动跟随系统。

## 硬件信息来源

> 注意：`/proc` 下的虚拟文件（`/proc/meminfo`、`/proc/net/dev` 等）大小为 0，
> 不能使用 `while (!file.atEnd())` 循环读取，必须用 `readAll()` 后按行解析，
> 否则循环体不会执行、数值恒为 0。早期版本曾因此导致内存与网速显示 0，已修复。

| 数据 | 来源 |
|------|------|
| CPU 使用率 | `/proc/stat`（两次采样差值） |
| 内存使用率 | `/proc/meminfo`（MemTotal / MemAvailable） |
| GPU 使用率 | AMD：`/sys/class/drm/card*/device/gpu_busy_percent`；NVIDIA：`nvidia-smi` |
| CPU 温度 | `/sys/class/hwmon/*/temp*_input`（k10temp/coretemp/zenpower 等，优先 Tctl/Tdie/Package） |
| GPU 温度 | `/sys/class/hwmon/*/temp*_input`（amdgpu）或 `nvidia-smi` |
| 上传/下载速度 | `/proc/net/dev`（排除 lo，按刷新间隔计算速率，上传/下载独立显示） |

## 测试验证

已在 Deepin 25（dde-shell 2.0.52，X11，AMD Ryzen 8845HS + Radeon 780M）上验证：

- 插件被 dde-shell 发现并加载（`dde-shell --list` 可见）
- Dock 中正常显示 CPU/内存/GPU/温度/网速
- 左键点击打开设置面板
- 单行/双行切换生效
- 监控项显隐、排序生效
- 主题自动跟随系统，自定义文字颜色生效
- 设置通过 DConfig 持久化，重启后保留

## 国际化说明

界面文案以中文作为源字符串（`qsTr("...")`）。`translations/` 下由
`update_translations` 目标生成 23 种语言的 `.ts` 模板；其中 `zh_CN` 已填充，
其余语言为未翻译状态，运行时回退到中文源文案。如需补充某语言，编辑对应
`.ts` 后执行：

```bash
# 更新 .ts 模板
cmake --build build --target update_translations  

# 编译 .qm 
lrelease translations/org.deepin.ds.dock.hwmonitor_<lang>.ts   

sudo cmake --install build
```
