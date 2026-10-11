# 4-1 OLED 显示屏

用软件 I²C 驱动 0.96 寸 OLED，练习字符、字符串、无符号数、有符号数、十六进制和二进制显示函数。工程基于 STM32F103C8 和 STM32F10x 标准外设库。

## 功能

- 上电后初始化 OLED，依次显示多种格式的示例内容。
- 第 1 行：字符 A、字符串 HelloWorld!。
- 第 2 行：无符号数 12345、有符号数 -66。
- 第 3 行：十六进制数 AA55。
- 第 4 行：二进制数。
- 显示完成后进入空循环，画面保持不变。

## 原理

- `OLED.c` 用 PB8 作 SCL、PB9 作 SDA，软件模拟 I²C 时序。
- `OLED_Init()` 发送初始化命令并清屏。
- `OLED_ShowChar/ShowString/ShowNum/ShowSignedNum/ShowHexNum/ShowBinNum` 在指定行、列显示对应格式，其中行从上到下为 1–4。

## 接线

| 功能 | STM32 引脚 |
| --- | --- |
| SCL | PB8 |
| SDA | PB9 |
| 电源 | 3.3 V（按模块规格） |
| 公共地 | GND |

## 开发环境

- 芯片：STM32F103C8。
- 工具：Keil µVision / MDK-ARM。
- 编译器：ARM Compiler 6.24（ARMCLANG）。
- 器件包：`Keil.STM32F1xx_DFP.2.4.1`。
- 外设库：STM32F10x 标准外设库。

## 打开工程

1. 用 Keil µVision 打开当前目录的 `Poject.uvprojx`。
2. 确认编译器和器件包配置，按开发板配置下载器。
3. 编译并下载，观察 OLED 上的示例内容。

## 主要文件

| 文件或目录 | 内容 |
| --- | --- |
| `User/main.c` | OLED 初始化与显示示例 |
| `Hardware/OLED.c` | OLED 驱动与软件 I²C |
| `Hardware/OLED_Font.h` | 字模数据 |
| `System/Delay.c` | 毫秒延时函数 |
| `Start/` | 启动文件、系统时钟与 CMSIS |
| `Library/` | STM32 标准外设库 |

## 当前状态与后续

- 本次整理时用 Keil 命令行全量编译通过：0 Error / 0 Warning，Code 2288 B。
- 未在开发板上烧录验证。
- 可以继续练习：动态刷新变量、局部清屏、显示中文（模块资料里有中文字库版本）。
