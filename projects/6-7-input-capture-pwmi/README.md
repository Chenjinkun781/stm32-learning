# 6-7 PWMI 模式测频率与占空比

用 TIM2 的 CH1（PA0）输出 PWM 作为被测信号，再用 TIM3 的 CH1（PA6）以 PWMI 模式做输入捕获，测量信号的频率和占空比，并在 OLED 上显示。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

## 功能

- 上电后初始化 OLED、PWM 输出和输入捕获。
- TIM2_CH1 输出 PWM，初始化参数为 1 kHz；`main.c` 中又把预分频器改为 `7200 - 1`，实际演示频率约 100 Hz，占空比约 80%。
- TIM3_CH1 用 PWMI 模式（双通道捕获）测量输入信号的周期和高电平时间。
- OLED 第一行显示 `Freq:` 和频率（Hz），第二行显示 `Duty:` 和占空比（%）。
- 程序只做显示，没有按键、串口输出或参数调节。

## 测量原理

`Hardware/IC.c`：

- TIM3 时钟 72 MHz，预分频 `72 - 1`，计数器频率为 1 MHz。
- `TIM_PWMIConfig()` 把 CH1 配成直接捕获（TI1FP1），CH2 配成间接捕获（TI1FP2），一次捕获同时得到周期和高电平时间。
- 从模式设为复位模式：每次捕获到上升沿后计数器自动清零。
- 频率：`1000000 / (CCR1 + 1)`；占空比：`(CCR2 + 1) × 100 / (CCR1 + 1)`。

`Hardware/PWM.c`：

- TIM2 时钟 72 MHz，预分频 `720 - 1`，自动重装 `100 - 1`，初始化后 PWM 频率为 1 kHz。
- `TIM_OC1Init()` 把 TIM2_CH1 配成 PWM1 输出，PA0 复用推挽输出。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| PWM 输出 | PA0 |
| 捕获输入 | PA6 |
| OLED SCL | PB8 |
| OLED SDA | PB9 |
| 公共地 | GND |

用杜邦线把 PA0 和 PA6 连在一起，PWM 信号直接送入捕获通道；OLED 供电按模块规格接。

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认已安装 ARM Compiler 6 和 STM32F1 器件包，按开发板配置下载器。
3. 编译并下载，观察 OLED 显示；需要把 PA0 与 PA6 用杜邦线连接。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | 初始化、OLED 显示与循环刷新 |
| `Hardware/PWM.c` | TIM2_CH1 PWM 输出（PA0） |
| `Hardware/IC.c` | TIM3_CH1 输入捕获与 PWMI 测频率/占空比 |
| `Hardware/OLED.c` | OLED 显示与软件 I²C |
| `System/Delay.c` | 延时函数 |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 3936 B。
- 未在开发板上烧录验证，实际显示的频率、占空比以实测为准。
- `main.c` 在初始化后又调用了 `PWM_SetPrescaler(7200 - 1)`，会把 PWM 频率从初始化的 1 kHz 改为约 100 Hz；如果按视频里的 1 kHz 现象核对，需要先确认这一行是否保留。
- 计数器为 16 位，测量高频时注意 ARR 回绕；公式中的 1 MHz 计数基准和滤波参数也要一起核对。
