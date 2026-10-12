# 5-1 对射式红外传感器计次

用外部中断统计对射式红外传感器被遮挡的次数，并在 OLED 上显示，练习 EXTI 和 NVIC 配置。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

## 功能

- 传感器数字输出 DO 接 PB14，上拉输入。
- PB14 配置为 EXTI14 上升沿触发，中断服务函数中计数加 1。
- OLED 第 1 行以十六进制、5 位宽度显示计数。

## 原理

- `GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14)` 把 PB14 映射到 EXTI14。
- EXTI14 配置为中断模式、上升沿触发；NVIC 使用优先级分组 2，抢占优先级 1、子优先级 1。
- 中断服务函数 `EXTI15_10_IRQHandler()` 中判断 EXTI_Line14 标志，计数后清除标志。
- `CountSensor_Get()` 返回当前计数值。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| 传感器 DO | PB14 |
| 电源 / 公共地 | 按模块规格接 |

对射式传感器用槽型光耦判断遮挡，遮挡/松开时输出电平变化；触发边沿按模块实际输出选择。

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认编译器和器件包配置，按开发板配置下载器。
3. 编译并下载，用手在传感器槽中遮挡几次，观察 OLED 计数变化。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | OLED 显示与主循环 |
| `Hardware/CountSensor.c` | EXTI14 初始化、计数与中断服务函数 |
| `Hardware/OLED.c` | OLED 显示与软件 I²C |
| `System/Delay.c` | 毫秒延时函数 |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 2376 B。
- 未在开发板上烧录验证。
- 计数变量 `CountSensor_Count` 是普通 `uint16_t`，在主循环和中断之间共享，可以练习 `volatile` 声明和临界区保护；还可以加消抖、掉电保存和溢出处理。
