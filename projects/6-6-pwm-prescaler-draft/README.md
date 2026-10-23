# 6-6 PWM 输出与预分频练习草稿

**状态：未完成草稿。当前源码有语法不完整的地方，不能作为已成功编译或运行的项目使用。** 本次保留学习过程中的原始代码。

## 已写出的内容

- PA0 / TIM2_CH1 配置为 PWM 输出，GPIO 为复用推挽。
- TIM2 使用内部时钟、向上计数、PWM1 模式和高电平有效输出。
- 初始化参数为 `PSC=719`、`ARR=99`、`CCR1=0`。按设计的 72 MHz TIM2 时钟，理论 PWM 频率为 1 kHz；初始比较值对应 0% 占空比。
- `PWM_SetCompare1(uint16_t Compare)` 已实现，通过 `TIM_SetCompare1()` 修改 CCR1。
- `PWM.h` 已声明 `PWM_SetPrescaler(uint16_t Prescaler)`，但函数实现还没有写完整；主函数中的 `PWM_SetCompare1` 调用也尚未完成。
- OLED 只初始化，主循环没有显示文字、数值或测量结果。

以上描述的是已经写入源码的配置与接口，并不表示这份草稿当前能运行输出。当前 `User/`、`Hardware/`、`System/` 中没有完成输入捕获或测频功能。

## 尚未完成的位置

1. `User/main.c` 中只有一行 `PWM_SetCompare1`，缺少函数调用的参数、括号和分号。
2. `Hardware/PWM.c` 末尾只有独立的 `{ ... }` 代码块，缺少 `PWM_SetPrescaler` 的函数头，并引用了没有声明的 `Prescaler`。

本次归档没有代替作者补写参数或修复这两处代码。后续可以先完善预分频接口和比较值设置，再重新编译、测量输出波形。

## 代码中的引脚配置

| 功能 | STM32 引脚 |
| --- | --- |
| PWM 输出 | PA0 / TIM2_CH1 |
| OLED SCL、SDA | PB8、PB9 |
| 波形观察设备公共地 | GND |

完成代码后，可使用示波器或逻辑分析仪观察 PA0；当前主程序没有指定受控负载。

## 主要文件与环境

- `User/main.c`：尚未完成的主程序。
- `Hardware/PWM.c`、`PWM.h`：PWM 初始化、比较值接口和未完成的预分频接口。
- `Hardware/OLED.c`：OLED 驱动。
- `Poject.uvprojx`：原始 Keil 工程，目标 STM32F103C8，ARM Compiler 6.24，`Keil.STM32F1xx_DFP.2.4.1`。

## 本次归档状态

2026-10-23 为整理日期。仅做源码和工程结构检查，保留原文件并核对一致性；没有重新编译、下载或上板测试。旧编译日志和其他生成文件未上传，也没有将旧日志当成本次验证结果。
