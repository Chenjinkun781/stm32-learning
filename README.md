# STM32 学习记录

记录 STM32 学习过程中的代码、实验内容和后续改进，每次提交保留一个阶段的进步。

## 项目

| 上传日期 | 最后修改 | 项目 | 本次内容 |
| --- | --- | --- | --- |
| 2026-10-13 | 2026-10-12 | [5-2 旋转编码器计数](projects/5-2-rotary-encoder/README.md) | 使用外部中断判断编码器旋转方向，并在 OLED 上显示累计计数 |
| 2026-10-14 | 2026-10-14 | [6-1 TIM2 内部时钟计时](projects/6-1-timer/README.md) | 使用内部时钟产生 1 秒定时中断，并在 OLED 上显示累计数值 |
| 2026-10-14 | 2026-10-14 | [6-2 TIM2 外部时钟计数](projects/6-2-external-clock/README.md) | PA0 输入外部脉冲，每 10 个有效脉冲累计一次更新中断，并显示 Num 与 CNT |
| 2026-10-23 | 2026-10-18 | [6-3 PWM 渐变与 LED 呼吸灯](projects/6-3-pwm-breathing/README.md) | TIM2_CH1 占空比渐变，练习 PWM 输出 |
| 2026-10-23 | 2026-10-18 | [6-4 PWM 舵机角度控制](projects/6-4-servo-control/README.md) | 按键切换角度，PWM 脉宽映射与 OLED 显示 |
| 2026-10-23 | 2026-10-18 | [6-5 PWM 直流电机控制](projects/6-5-pwm-dc-motor/README.md) | 有符号控制命令、方向引脚和 PWM 调速 |
| 2026-10-23 | — | [6-6 PWM 预分频草稿（未完成）](projects/6-6-pwm-prescaler-draft/README.md) | 保留尚未写完整的调用与函数，记录学习过程 |
| 2026-10-26 | 2026-10-25 | [6-7 PWMI 测频率与占空比](projects/6-7-input-capture-pwmi/README.md) | PWM 输出 + 输入捕获双通道，OLED 显示频率与占空比 |
| 2026-10-26 | 2026-10-26 | [6-8 编码器接口测速](projects/6-8-encoder-speed/README.md) | TIM3 编码器接口计数，OLED 显示 CNT 增量 |
| 2026-10-26 | 2026-10-09 | [3-2 LED 流水灯](projects/3-2-led-water-light/README.md) | 使用 GPIOA 的 PA0–PA7 依次输出低电平，形成流水灯 |
| 2026-10-26 | 2026-10-09 | [3-3 蜂鸣器](projects/3-3-buzzer/README.md) | 有源蜂鸣器按短鸣与长停的节奏发声 |
| 2026-10-26 | 2026-10-11 | [3-4 按键控制 LED](projects/3-4-key-led/README.md) | 两个按键分别翻转两个 LED，包含 20 ms 软件消抖 |
| 2026-10-26 | 2026-10-11 | [3-5 光敏传感器控制蜂鸣器](projects/3-5-light-sensor-buzzer/README.md) | 读取光敏传感器数字输出，控制蜂鸣器开关 |
| 2026-10-26 | 2026-10-11 | [4-1 OLED 显示屏](projects/4-1-oled/README.md) | 软件 I²C 驱动 OLED，显示字符、数字、十六进制和二进制示例 |
| 2026-10-26 | 2026-10-12 | [5-1 对射式红外传感器计次](projects/5-1-ir-counter/README.md) | PB14 外部中断计数，OLED 显示遮挡次数 |
| 2026-10-26 | 2026-10-25 | [6-6 输入捕获测频率（完成版）](projects/6-6-input-capture/README.md) | PWM 输出 + 输入捕获测频率，OLED 显示频率 |

上传日期表示整理上传的日期；最后修改为对应工程 `User`、`Hardware`、`System` 源文件的最后修改日期，与代码实际编写顺序可能略有出入。

## 学习记录

- [2026-10-13：整理旋转编码器计数工程](logs/2026-10-13.md)
- [2026-10-14：TIM2 内部时钟计时与外部时钟计数](logs/2026-10-14.md)
- [2026-10-23：整理四个 PWM 学习工程](logs/2026-10-23.md)
- [2026-10-26：归档 6-7、6-8 并补档 3-2 至 6-6（完成版）](logs/2026-10-26.md)

## 使用方法

进入对应项目目录，用 Keil µVision 打开 `.uvprojx` 工程文件；具体接线和开发环境见项目说明。

`projects/6-6-input-capture` 是 6-6 的完成版；`projects/6-6-pwm-prescaler-draft` 保留早期未完成草稿。

## 目录

- `projects/`：各阶段的代码和工程文件。
- `logs/`：每次学习记录。
- `.gitignore`：排除编译输出和本机编辑器偏好。

工程中附带的 ST、ARM 库文件保留原有版权声明。
