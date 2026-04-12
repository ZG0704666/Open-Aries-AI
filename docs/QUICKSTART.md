# 快速开始（Windows）

## 1. 运行方式

### 方式 A：直接运行二进制

```powershell
aries_agent.exe
```

### 方式 B：从源码构建（推荐开发者）

#### CMake（推荐）

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

构建产物：`build/Release/aries_agent.exe`

#### 传统命令（兼容）

```powershell
g++ -std=c++17 aries_agent.cpp -o aries_agent.exe ^
    -lgdiplus -lgdi32 -lws2_32 -lcrypt32 -lwininet -lwinhttp
```

## 2. 首次配置

启动后会引导：

1. 配置 API Key（可选默认提供商或自定义 OpenAI 兼容提供商）
2. 配置高危能力开关（Execute / FileWrite / FileDelete / FileRun）
3. 输入任务目标

## 3. 推荐安全配置

默认建议：

- 高危能力全部关闭；
- 仅在明确任务需要时临时开启；
- 保持高危动作二次确认为开启。

也可以通过 `aries_config.json` 进行固定配置，参考根目录 `aries_config.example.json`。

## 4. 常用命令

- `quit` / `exit`：退出
- `clear`：清除已保存密钥与自定义提供商
- `provider`：切换提供商

## 5. 常见问题

### Q1：程序启动就退出？

请在命令行中运行并检查输出，确认 Windows 版本、网络和依赖库是否满足要求。

### Q2：模型请求失败？

优先检查：

- API Key 是否有效；
- base URL 是否为 OpenAI 兼容接口；
- 模型是否支持图像输入。
