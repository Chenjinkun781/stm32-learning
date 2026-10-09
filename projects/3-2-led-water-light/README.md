# 3-2 LED 流水灯

用 GPIOA 的 PA0–PA7 依次点亮 LED，形成流水灯效果。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

## 功能

- 上电后把 GPIOA 配置为推挽输出，所有引脚先输出高电平。
- 主循环依次输出 `~0x0001` 到 `~0x0080`，每次间隔 100 ms。
- 代码对数据取反后写入，同一时刻只有一个引脚输出低电平；按低电平点亮 LED 的接法，看起来就是单个 LED 依次移动。
- 没有按键、暂停或方向切换。

## 原理

- 打开 GPIOA 时钟，`GPIO_Pin_All` 配置为 50 MHz 推挽输出。
- `GPIO_Write(GPIOA, value)` 一次写整个端口；`~0x0001` 表示 PA0 低电平、其余引脚高电平。
- `Delay_ms(100)` 控制每步之间的间隔，延时函数在 `System/Delay.c` 中基于 SysTick 实现。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| LED1–LED8 信号 | PA0–PA7 |
| 电源 / 公共地 | 按 LED 模块规格接 |

代码按低电平点亮 LED 编写；如果实际模块是高电平点亮，现象会反过来。

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认已安装 ARM Compiler 6 和 STM32F1 器件包，按开发板配置下载器。
3. 编译并下载，观察 LED 是否依次点亮。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | GPIO 初始化与流水灯循环 |
| `System/Delay.c` | 毫秒延时函数 |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 1160 B。
- 未在开发板上烧录验证。
- 可以继续练习：往返流水、调节速度、按键切换方向，或改成移位运算实现。
