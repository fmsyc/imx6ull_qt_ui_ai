# TerminalApp

正点原子 **i.MX6ULL**（Qt 5.12.9，1024×576，Cortex-A7 无 GPU）上的平板 / 车载风格
桌面外壳，使用 **Qt Widgets + .ui + QSS** 实现。

- 界面用 `.ui` 文件搭建，Designer 可视化拖拽，改样式只动 QSS
- **换图片、加图标、加/减 App 条目都不用重新编译**（运行时读 `config/` 与 `resources/`）
- 内嵌 App（`IAppPage`）与外挂进程（`QProcess`）都支持
- CMake 构建，**本机 Qt6 与板端 Qt5.15 同一套代码**

---

## 1. 目录结构

```
terminalApp/
├── CMakeLists.txt            顶层构建（自动适配 Qt5 / Qt6）
├── Makefile                  封装 CMake，`make` 即可
├── config/
│   └── apps.json             ★ 桌面显示什么、Dock 有什么，全在这里
├── resources/                ★ 运行时资源（可整体替换，无需重编译）
│   ├── background/desktop.png    壁纸
│   ├── icons/                    应用 / Dock / 状态栏图标
│   ├── ui/style.qss              全局样式表
│   ├── tools/external_demo.sh    外挂 App 示例
│   └── resources.qrc             兜底资源（文件缺失时使用）
├── src/
│   ├── main.cpp
│   ├── core/                 Compat / ResourceLocator / AppRegistry / AppLauncher / IconUtil
│   ├── apps/                 IAppPage + AppFactory + 各内嵌页面
│   └── shell/                DesktopWindow / PagerWidget / AppPage / AppTile
│                             / StatusBar / DockBar / PageIndicator
├── tools/gen_assets.py       用 PIL 生成全部占位素材
├── cmake/toolchain-board.cmake   ★ 板端交叉编译工具链（唯一入口，SDK 路径可覆盖）
├── cmake/toolchain-fsl-imx.cmake  兼容别名，内部 include 上面这个
└── deploy/                   run.sh / sync_board.sh / terminalApp.service
```

---

## 2. 本机编译与运行（已验证）

```bash
cd terminalApp
make                 # 配置 + 编译 -> build/TerminalApp
./build/TerminalApp  # 直接运行
```

`make` 会自动用 `qmake -query QT_INSTALL_PREFIX` 找到本机 Qt；
若 Qt 不在 PATH 里，可显式指定：

```bash
make QT_PREFIX=/home/ccking/QT/QT6/6.11.2/gcc_64
```

`config/` 与 `resources/` 每次构建都会同步到可执行文件旁边，
所以 `build/TerminalApp` 是**自包含**的，可以从任意目录启动。

常用目标：

| 命令 | 作用 |
| --- | --- |
| `make` | 配置 + 编译 |
| `make run` | 编译后运行 |
| `make assets` | 重新生成占位素材 |
| `make clean` | 删除 `build/` |

### 开发 / 预览开关

```bash
./build/TerminalApp --fullscreen          # 全屏（板上效果）
./build/TerminalApp --page 1              # 直接打开第 2 页（0 基）
./build/TerminalApp --open camera         # 直接打开某个 App
QT_QPA_PLATFORM=offscreen ./build/TerminalApp --screenshot out.png   # 无显示环境出图
```

---

## 3. 板端交叉编译

板端 SDK 是 Yocto/FSL 的 `fsl-imx-x11 4.1.15-2.1.0`（自带 Qt 5.12.9）。
**不需要 source 任何环境**，直接：

```bash
make board            # 配置 + 编译 -> build-board/TerminalApp（ARM，已 strip）
```

等价的显式写法：

```bash
cmake -S . -B build-board \
      -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-board.cmake \
      -DSDK_ROOT=/opt/fsl-imx-x11/4.1.15-2.1.0
cmake --build build-board -j
```

工具链文件会自动识别 SDK，并处理 Yocto 那套坑（`CMAKE_SYSROOT`、
`OE_QMAKE_PATH_EXTERNAL_HOST_BINS` 等），所以不会再出现
`Could not find moc executable target Qt5::moc` 或 `cannot find crt1.o`。

换成别的 SDK / 板子时，只需改 `-DSDK_ROOT=...`（或 `make board SDK_ROOT=...`）；
没有 Yocto SDK 而用普通 Linaro 工具链时：

```bash
cmake -S . -B build-board \
      -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-board.cmake \
      -DSDK_ROOT= \
      -DCROSS_PREFIX=arm-linux-gnueabihf- \
      -DBOARD_SYSROOT=/path/to/rootfs \
      -DBOARD_QT_ROOT=/path/to/rootfs/usr/lib/cmake
```

> 注意：`make`（本机构建）会拒绝使用 PATH 里的交叉 qmake，避免误用板端 Qt；
> 而 `make board` 不受影响，即使 shell 里 source 过 `environment-setup-*` 也能正常编译。

## 4. 部署到板子

```bash
deploy/sync_board.sh root@192.168.1.20:/opt/terminalApp   # 同步可执行 + config + resources
ssh root@192.168.1.20 '/opt/terminalApp/run.sh'           # 启动
```

`run.sh` 默认使用 `QT_QPA_PLATFORM=eglfs`（Vivante 集成），出错可退到软件帧缓冲：

```bash
QT_QPA_PLATFORM=linuxfb /opt/terminalApp/run.sh
```

开机自启：把 `deploy/terminalApp.service` 放到 `/lib/systemd/system/`，
改成自己的路径后 `systemctl enable --now terminalApp`。

---

## 5. 三件日常事

### 5.1 换背景图 / 图标

直接把同名文件覆盖到板子的 `resources/background/desktop.png`、`resources/icons/*.png`，重启程序即可。
尺寸不必严格匹配：壁纸按 **cover** 比例缩放并缓存，图标按需缩放。

占位素材是脚本生成的，想批量改配色就改 `tools/gen_assets.py` 再 `make assets`。

### 5.2 增加一个 App

**内嵌（推荐，页面是 C++ + .ui）**

1. 新建 `src/apps/<name>/XxxPage.ui/.h/.cpp`，继承 `IAppPage`；
2. 在 `src/apps/AppFactory.cpp` 加一行：`REGISTER_APP("xxx", XxxPage)`；
3. 在 `config/apps.json` 的某个 `pages[].apps[]` 里加：

```json
{ "id": "xxx", "name": "显示名", "icon": "resources/icons/app_xxx.png", "type": "embedded" }
```

**内嵌 MQTT 页面**

`src/apps/mqtt/` 是一个内嵌页面（连接 / 发布 / 订阅三个页签），已注册为 app id `mqtt`：

```json
{ "id": "mqtt", "name": "MQTT", "icon": "resources/icons/app_settings.png", "type": "embedded" }
```

它依赖 Qt Mqtt 模块：

- **板端**：FSL/Yocto SDK 自带 Qt5Mqtt，`make board` 会自动编入。
- **桌面端**：Qt6 在线安装器默认**不含** Qt Mqtt 附加模块。没装时会退化成
  `src/apps/mqtt/MqttUnavailablePage.cpp`（提示装模块），`make` 不会因为缺模块而失败。
  想要本机也能用：Qt Maintenance Tool → Additional Libraries → 勾选 **Qt Mqtt**，再重新 `make`。

CMake 通过 `HAVE_QT_MQTT` 开关自动切换，不要手动往 `CMakeLists.txt` 里写 SDK 的头文件/库路径。

**外挂进程（接入已有 demo 最省事）**

```json
{ "id": "mqtt", "name": "MQTT", "icon": "resources/icons/app_network.png",
  "type": "external", "exec": "/opt/mqtt_client/mqtt_client", "args": [], "daemon": false }
```

`exec` 写绝对路径，或者写相对 `resources/` 的路径（会自动解析到可执行文件旁）。
`daemon: true` 表示常驻、不随桌面切换而杀。

### 5.3 调整 Dock / 分页

`config/apps.json` 里 `pages` 是数组，多一页就多一屏，底部指示点自动跟随；
`dock` 是 Dock 按钮列表，`"app": "settings"` 表示点它直接打开某个 App，去掉则只做占位。

---

## 6. 兼容性说明（重要）

代码与 CMake 同时兼容 **Qt 5.12.9（板端 SDK）** 与 **Qt 6.x（本机）**：

- API 差异（如鼠标事件坐标）统一收口在 `src/core/Compat.h`；
- CMake 用 `find_package(QT NAMES Qt6 Qt5 ...)` + `QT_VERSION_MAJOR` 分支；
- 新增代码请勿直接使用两版行为不同的 API，先往 `Compat.h` 里加封装。

## 7. 流畅度取舍

无 GPU 的 i.MX6ULL 上不用 `QGraphicsView` / 着色器：
翻页是纯控件位移动画（`QPropertyAnimation`，约 220ms，OutCubic）+ 速度判断翻页；
壁纸只做一次 cover 缩放并缓存；图标预缩放缓存。整体以 CPU 友好的方式换取顺滑手感。
