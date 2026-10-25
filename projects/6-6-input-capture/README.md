# 6-6 输入捕获测频率（完成版）

用 PWM 输出一个已知频率的方波，再用输入捕获测量它的频率，并在 OLED 上显示，练习 TIM 的 PWM 输出与输入捕获。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

> 仓库里另有 [6-6 PWM 预分频草稿](../6-6-pwm-prescaler-draft/README.md)（早期未完成版本），本目录是后来完成的版本。

## 功能

- TIM2_CH1（PA0）输出 PWM，初始化参数为 1 kHz、50% 占空比。
- TIM3_CH1（PA6）输入捕获，用从模式复位测量输入方波的周期。
- OLED 第一行显示 `Freq:` 和测得的频率（Hz）。

## 原理

`Hardware/PWM.c`：

- TIM2 时钟 72 MHz，预分频 `720 - 1`，自动重装 `100 - 1`，输出频率为 1 kHz。
- `TIM_OC1Init()` 把 TIM2_CH1 配成 PWM1 输出，PA0 复用推挽。
- `main.c` 中调用 `PWM_SetPrescaler(720 - 1)`、`PWM_SetCompare1(50)`，即 1 kHz、50% 占空比。

`Hardware/IC.c`：

- TIM3 时钟 72 MHz，预分频 `72 - 1`，计数器频率 1 MHz。
- CH1 上升沿捕获，`TIM_SelectInputTrigger(TIM_TS_TI1FP1)` 加从模式复位，每次上升沿后计数器清零。
- 频率计算：`1000000 / (CCR1 + 1)`。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| PWM 输出 | PA0 |
| 捕获输入 | PA6 |
| OLED SCL | PB8 |
| OLED SDA | PB9 |
| 公共地 | GND |

用杜邦线把 PA0 和 PA6 连在一起，PWM 信号直接送入捕获通道。

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认编译器和器件包配置，按开发板配置下载器。
3. 编译并下载，连接 PA0–PA6，观察 OLED 显示的频率。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | PWM/IC 初始化与 OLED 显示 |
| `Hardware/PWM.c` | TIM2_CH1 PWM 输出（PA0） |
| `Hardware/IC.c` | TIM3_CH1 输入捕获与频率计算 |
| `Hardware/OLED.c` | OLED 显示与软件 I²C |
| `System/Delay.c` | 毫秒延时函数 |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 3248 B。
- 未在开发板上烧录验证，实际显示频率以实测为准。
- 本地 6-6 目录里还有一份 `Encoder.c`（后来给 6-8 工程借用），没有加入本工程，也未归档到本目录。
- 可以继续练习：扩大测量范围、增加占空比测量（6-7 的内容）、核对滤波参数和高频误差。
