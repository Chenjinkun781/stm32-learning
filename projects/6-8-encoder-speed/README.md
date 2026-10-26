# 6-8 编码器接口测速

用 TIM3 的编码器接口模式读取旋转编码器的 A/B 相脉冲，在 OLED 上显示两次读取之间的计数增量。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

## 功能

- TIM3 配置为编码器接口模式，A/B 相分别接 PA6、PA7（上拉输入）。
- `Encoder_Get()` 读取计数器后清零，返回本次的计数值（`int16_t`，符号表示方向）。
- 主循环在 OLED 第一行显示 `CNT:` 和 5 位带符号数。
- 程序没有速度换算、按键清零或串口输出，只显示原始计数增量。

## 计数原理

`Hardware/Encoder.c`：

- 打开 TIM3 和 GPIOA 时钟，PA6、PA7 配成上拉输入。
- 时基：预分频 `1 - 1`，自动重装 `65536 - 1`，计数器按编码器脉冲自动加/减。
- `TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising)`：使用 TI1、TI2 双通道，按 A/B 相序决定计数方向。
- 读取后 `TIM_SetCounter(TIM3, 0)`，下一次读取到的就是两次读取之间的增量。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| 编码器 A 相 | PA6 |
| 编码器 B 相 | PA7 |
| 编码器电源 | 3.3 V / 5 V（按模块规格） |
| 公共地 | GND |
| OLED SCL | PB8 |
| OLED SDA | PB9 |

编码器 A、B 相不要接反，否则显示的正负方向会相反。

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认编译器、器件包和下载器配置。
3. 编译并下载，旋转编码器观察 OLED 上的计数变化。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | OLED 显示与循环读取 |
| `Hardware/Encoder.c` | TIM3 编码器接口初始化与读取 |
| `Hardware/Encoder.h` | 接口声明 |
| `System/Timer.c` | TIM2 定时中断示例（当前 `main.c` 未使用） |
| `Hardware/OLED.c` | OLED 显示与软件 I²C |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 归档说明

原始工程中 `Encoder.c` 的路径是 `..\6-6\Hardware\Encoder.c`，也就是借用了 6-6 目录下的源文件。为了让仓库中的工程能独立打开和编译，本次归档把 `Encoder.c` 复制到本工程的 `Hardware/`，并把工程引用改为 `.\Hardware\Encoder.c`；本机原始工程没有改动。

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 3060 B。
- 未在开发板上烧录验证，实际计数和方向以实测为准。
- 计数器为 16 位、自动重装 65536，若两次读取之间脉冲数超过 65536 会发生回绕；后续可以做速度换算（计数 / 时间），并配合定时器周期读取。
