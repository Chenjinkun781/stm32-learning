# STM32 学习记录

记录 STM32 学习过程中的代码、实验内容和后续改进，每次提交保留一个阶段的进步。

## 项目

| 记录日期 | 项目 | 本次内容 |
| --- | --- | --- |
| 2026-10-13 | [5-2 旋转编码器计数](projects/5-2-rotary-encoder/README.md) | 使用外部中断判断编码器旋转方向，并在 OLED 上显示累计计数 |
| 2026-10-14 | [6-1 TIM2 内部时钟计时](projects/6-1-timer/README.md) | 使用内部时钟产生 1 秒定时中断，并在 OLED 上显示累计数值 |
| 2026-10-14 | [6-2 TIM2 外部时钟计数](projects/6-2-external-clock/README.md) | PA0 输入外部脉冲，每 10 个有效脉冲累计一次更新中断，并显示 Num 与 CNT |
| 2026-10-23 | [6-3 PWM 渐变与 LED 呼吸灯](projects/6-3-pwm-breathing/README.md) | TIM2_CH1 占空比渐变，练习 PWM 输出 |
| 2026-10-23 | [6-4 PWM 舵机角度控制](projects/6-4-servo-control/README.md) | 按键切换角度，PWM 脉宽映射与 OLED 显示 |
| 2026-10-23 | [6-5 PWM 直流电机控制](projects/6-5-pwm-dc-motor/README.md) | 有符号控制命令、方向引脚和 PWM 调速 |
| 2026-10-23 | [6-6 PWM 预分频草稿（未完成）](projects/6-6-pwm-prescaler-draft/README.md) | 保留尚未写完整的调用与函数，记录学习过程 |

日期表示整理记录的日期，不代表代码最初编写的日期。

## 学习记录

- [2026-10-13：整理旋转编码器计数工程](logs/2026-10-13.md)
- [2026-10-14：TIM2 内部时钟计时与外部时钟计数](logs/2026-10-14.md)
- [2026-10-23：整理四个 PWM 学习工程](logs/2026-10-23.md)

## 使用方法

进入对应项目目录，用 Keil µVision 打开 `.uvprojx` 工程文件；具体接线和开发环境见项目说明。

## 目录

- `projects/`：各阶段的代码和工程文件。
- `logs/`：每次学习记录。
- `.gitignore`：排除编译输出和本机编辑器偏好。

工程中附带的 ST、ARM 库文件保留原有版权声明。
