## STM32F10x TIM 库函数总结

这两个文件 (`stm32f10x_tim.c` 和 `stm32f10x_tim.h`) 是 ST 为 STM32F10x 系列芯片提供的**标准外设库 (Standard Peripheral Library, SPL)** 中关于定时器 (TIM) 的驱动文件。

---

## 常用函数 (Commonly Used)

这些是配置和使用TIM时最常接触的函数，涵盖了基本的定时、PWM输出、输入捕获等核心功能。

| 函数名                      | 主要功能                                                     |
| :-------------------------- | :----------------------------------------------------------- |
| **`TIM_TimeBaseInit`**      | **[核心]** 初始化TIM的时间基准单元。设置预分频器(PSC)、计数模式、周期(ARR)、时钟分频(CKD)等。 |
| **`TIM_Cmd`**               | **[核心]** 启用或禁用指定的TIM。**（即启动/停止计数器）**    |
| **`TIM_ITConfig`**          | **[核心]** 启用或禁用指定的TIM中断（如更新中断、捕获/比较中断）。 |
| **`TIM_OCInit`**            | **[核心-PWM/OC]** 初始化TIM的输出比较 (Output Compare) 通道。用于配置PWM模式、输出极性等。 |
| **`TIM_ICInit`**            | **[核心-IC]** 初始化TIM的输入捕获 (Input Capture) 通道。用于配置捕获的极性、分频、滤波等。 |
| **`TIM_SetComparex`**       | **[核心-PWM/OC]** 设置指定通道 (x=1,2,3,4) 的捕获/比较寄存器 (CCR) 的值。**（动态修改PWM占空比或比较值）** |
| **`TIM_GetFlagStatus`**     | 检查指定的TIM标志位（Flag）是否被置位。                      |
| **`TIM_ClearFlag`**         | 清除TIM的标志位。                                            |
| **`TIM_GetITStatus`**       | 检查指定的TIM中断是否发生（检查中断挂起位）。                |
| **`TIM_ClearITPendingBit`** | 清除TIM的中断挂起位。**（必须在中断服务函数中调用）**        |
| **`TIM_OCxPreloadConfig`**  | 启用或禁用指定输出比较通道 (OCx) 的预装载功能。**（对平滑的PWM输出很关键）** |
| **`TIM_ARRPreloadConfig`**  | 启用或禁用自动重装载寄存器 (ARR) 的预装载功能。              |
| **`TIM_GetCounter`**        | 获取TIM当前计数器 (CNT) 的值。                               |
| **`TIM_GetCapturex`**       | 获取指定输入捕获通道 (x=1,2,3,4) 捕获到的值 (CCRx 的值)。    |
| **`TIM_SetCounter`**        | 手动设置TIM计数器 (CNT) 的值。                               |

---

## 不常用/特定功能函数 (Less Common / Specific Functions)

这些函数通常用于更高级、更特定的应用场景，如多定时器同步、高级电机控制、特殊模式配置等。

| 函数名                           | 主要功能                                                     |
| :------------------------------- | :----------------------------------------------------------- |
| **`TIM_DeInit`**                 | 将指定的TIM外设寄存器重置为其默认值。                        |
| **`TIM_TimeBaseStructInit`**     | 用默认值填充 `TIM_TimeBaseInitTypeDef` 结构体。              |
| **`TIM_OCStructInit`**           | 用默认值填充 `TIM_OCInitTypeDef` 结构体。                    |
| **`TIM_ICStructInit`**           | 用默认值填充 `TIM_ICInitTypeDef` 结构体。                    |
| **`TIM_BDTRConfig`**             | **[高级定时器]** 配置刹车(Break)和死区(Dead-Time)功能。主要用于 TIM1 和 TIM8。 |
| **`TIM_BDTRStructInit`**         | 用默认值填充 `TIM_BDTRInitTypeDef` 结构体。                  |
| **`TIM_CtrlPWMOutputs`**         | **[高级定时器]** 使能或失能主输出 (Main Output Enable - MOE)。用于 TIM1 和 TIM8。 |
| **`TIM_EncoderInterfaceConfig`** | 配置TIM为编码器接口模式。                                    |
| **`TIM_SelectEncoderMode`**      | (已合并到 `TIM_EncoderInterfaceConfig`) 选择编码器模式。     |
| **`TIM_OnePulseModeConfig`**     | 配置TIM为单脉冲 (One-Pulse) 模式。                           |
| **`TIM_SelectInputTrigger`**     | 选择TIM的触发输入源 (TRGI)。用于主从模式。                   |
| **`TIM_SelectOutputTrigger`**    | 选择TIM的触发输出源 (TRGO)。用于主从模式。                   |
| **`TIM_SelectMasterSlaveMode`**  | 选择TIM的主/从模式。                                         |
| **`TIM_SelectHallSensor`**       | 配置TIM为霍尔传感器 (Hall Sensor) 接口模式。                 |
| **`TIM_ETRConfig`**              | 配置外部触发 (ETR) 的分频、极性和滤波器。                    |
| **`TIM_InternalClockConfig`**    | 选择TIM的内部时钟源 (CK_INT)。                               |
| **`TIM_DMACmd`**                 | 启用或禁用指定的TIM DMA请求。                                |
| **`TIM_SelectCOM`**              | **[高级定时器]** 配置当COM (Capture/Output Mode) 事件发生时，CC (Capture/Compare) 寄存器如何更新。 |
| **`TIM_ForcedOCxConfig`**        | 强制将指定的输出比较通道 (OCx) 设置为高电平或低电平。        |
| **`TIM_SetICxPrescaler`**        | (已合并到 `TIM_ICInit`) 设置输入捕获 (ICx) 的预分频器。      |
| **`TIM_OCxNPolarityConfig`**     | **[高级定时器]** 配置互补输出通道 (OCxN) 的极性。            |