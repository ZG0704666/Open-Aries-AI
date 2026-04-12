# 架构说明

## 总体流程

`用户目标 -> 截图 -> 模型推理 -> 动作解析 -> 动作执行 -> 结果反馈 -> 下一轮`

## 核心模块

- `aries_agent.cpp`：主循环与流程编排
- `ai_provider.hpp`：Provider 抽象接口
- `openai_compatible_provider.hpp`：OpenAI 兼容实现（含图像输入）
- `provider_manager.hpp`：多提供商管理与切换
- `action_parser.hpp`：动作解析与 schema 校验
- `action_executor.hpp`：动作执行与能力开关控制
- `file_manager.hpp`：文件系统操作
- `secure_storage.hpp`：API Key/Provider 配置安全存储（DPAPI）
- `security_config.hpp`：安全开关配置（文件+环境变量）
- `update_checker.hpp`：版本检查

## 当前边界

- 平台：Windows
- 依赖：Win32/GDI+/WinINet/WinHTTP/DPAPI
- 运行形态：本地单进程 Agent

## 未来抽象方向（建议）

- 抽象平台层（屏幕、输入、进程、网络）
- 抽象执行层（本地执行/远端执行）
- 抽象日志层（文本日志 -> JSON Lines + 追踪字段）
