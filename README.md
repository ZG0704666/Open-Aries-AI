# Open-Aries-AI

> Windows 桌面智能自动化 Agent（截图感知 + LLM 决策 + 动作执行）

[![Platform](https://img.shields.io/badge/Platform-Windows-blue)](https://www.microsoft.com/windows)
[![Language](https://img.shields.io/badge/C%2B%2B-17-orange)](https://isocpp.org/)
[![API](https://img.shields.io/badge/API-OpenAI%20Compatible-green)](https://platform.openai.com/docs/api-reference)

---

## 这是什么项目？

Open-Aries-AI 是一个可运行的 **Windows 本地执行程序**，用于把自然语言任务转换为桌面自动化动作：

1. 截图理解当前界面；
2. 把目标 + 截图发给模型；
3. 解析模型动作；
4. 执行点击、输入、应用启动、文件操作、命令执行；
5. 将反馈再发给模型迭代。

可直接运行 `aries_agent.exe`，也可从源码构建。

---

## 文档入口（先看这里）

- 📚 [文档中心](docs/README.md)
- ⚡ [快速开始](docs/QUICKSTART.md)
- 🧠 [架构说明](docs/ARCHITECTURE.md)
- 🔐 [安全边界](docs/SECURITY_BOUNDARY.md)
- 🛠️ [安全开发实现记录](docs/SECURITY_DEVELOPMENT.md)

---

## 核心特性

- OpenAI 兼容接口，多提供商切换；
- 支持视觉输入（截图）；
- 支持 Windows 桌面动作执行（Tap/Type/Swipe/Launch 等）；
- 支持文件管理动作（读写/搜索/目录树等）；
- 支持安全能力开关 + 高危动作二次确认；
- API Key 与自定义提供商配置采用 DPAPI 存储。

---

## 快速开始

### 运行二进制

```powershell
aries_agent.exe
```

### CMake 构建

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

构建产物：`build/Release/aries_agent.exe`

---

## 安全能力配置

高危能力默认关闭：

- `Execute`
- `FileWrite` / `FileAppend`
- `FileDelete`
- `FileRun`

你可以通过以下方式配置：

1. 启动时交互配置；
2. `aries_config.json`（可复制 `aries_config.example.json`）；
3. 环境变量覆盖：
   - `ARIES_ALLOW_EXECUTE`
   - `ARIES_ALLOW_FILE_WRITE`
   - `ARIES_ALLOW_FILE_DELETE`
   - `ARIES_ALLOW_FILE_RUN`
   - `ARIES_REQUIRE_HIGH_RISK_CONFIRMATION`

支持值：`1/0`、`true/false`、`yes/no`、`on/off`。

---

## 项目结构

```text
Open-Aries-AI/
├── aries_agent.cpp                # 主程序入口
├── action_parser.hpp              # 动作解析 + schema校验
├── action_executor.hpp            # 动作执行 + 安全开关
├── security_config.hpp            # 安全配置读取（文件+环境变量）
├── secure_storage.hpp             # DPAPI密钥/配置存储
├── ai_provider.hpp                # Provider接口
├── openai_compatible_provider.hpp # OpenAI兼容Provider
├── provider_manager.hpp           # 提供商管理
├── file_manager.hpp               # 文件能力
├── app_manager.hpp                # 应用发现/启动
├── update_checker.hpp             # 更新检查
├── aries_config.example.json      # 安全配置模板
├── CMakeLists.txt                 # CMake构建
└── docs/                          # 文档中心
```

---

## CI

已提供 GitHub Actions Windows 构建流水线：`.github/workflows/ci.yml`。

---

## 当前状态与路线图

- ✅ 4.1（安全与稳定先行）核心项已落地：能力开关、二次确认、DPAPI、schema 校验；
- 🚧 4.2（工程化）进行中：需要补齐单测矩阵、lint、发布流程；
- 🧭 4.3（产品化）计划中：安全模式/开发者模式、dry-run、更细粒度可靠性策略。

---

## 许可证

[MIT](LICENSE)
