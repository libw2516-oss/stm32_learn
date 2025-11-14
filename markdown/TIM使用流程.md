# STM32 定时器使用流程总结
(基于 `Timer.c` 和 `main.c` 文件的分析)

## 一、 定时器初始化 (在 `Timer_Init` 中)
这是配置定时器的核心步骤。

### 1. 开启时钟
* **开启TIM时钟**：为所用的定时器开启时钟。TIM2 挂载在 APB1 总线上。
    ```c
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    ```
* **开启GPIO时钟**：如果使用了定时器的外部引脚 (如ETR、PWM、输入捕获等)，必须开启对应GPIO端口时钟。此例中为 PA0（GPIOA）。
    ```c
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    ```

### 2. 配置GPIO口
* 如果用到了定时器的引脚功能（如此处的ETR），需配置GPIO模式。此例中 PA0 配置为上拉输入 `GPIO_Mode_IPU`。
    ```c
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    // ...
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    ```

### 3. 配置定时器时钟源 (根据应用选择)
* 定时器可以选择内部时钟、外部时钟等。
* 此案例中，选择了**外部时钟模式2**，时钟源来自 ETR 引脚。
    ```c
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x06);
    ```
* *(注：若使用最常见的**内部时钟**，此步省略，定时器默认使用内部时钟)*

### 4. 配置时基单元 (Time Base)
* 定义 `TIM_TimeBaseInitTypeDef` 结构体，设置定时器核心计数参数。
* **`TIM_Period`** (周期/自动重装载值)：计数器溢出值 (此例为 `10 - 1`，表示0-9计数)。
* **`TIM_Prescaler`** (预分频器)：对时钟源分频 (此例为 `1 - 1`，表示不分频)。
* **`TIM_CounterMode`** (计数模式)：如 `TIM_CounterMode_Up` (向上计数)。
* **`TIM_ClockDivision`** (时钟分频)：主要用于滤波器采样。
* 调用 `TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);` 使配置生效。

### 5. 配置中断 (可选)
* 如果需要在定时器溢出（更新）时执行代码，则需配置中断。
* **清除标志位**：`TIM_TimeBaseInit` 会在最后触发一次更新事件以加载寄存器，建议手动清除此标志位，避免启动时立即进中断。
    ```c
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    ```
* **使能TIM中断**：允许定时器在发生“更新事件”时产生中断信号。
    ```c
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    ```
* **配置NVIC** (中断控制器)：
    * 设置中断优先级分组 `NVIC_PriorityGroupConfig(...)`。
    * 初始化 `NVIC_InitTypeDef` 结构体，指定中断通道 (如 `TIM2_IRQn`)、抢占优先级和响应优先级。
    * 调用 `NVIC_Init(...)` 使能该中断通道。

### 6. 启动定时器
* 调用 `TIM_Cmd(TIM2, ENABLE);` 启动定时器，它正式开始按配置计数。

## 二、 在主函数中调用 (在 `main.c` 中)

1.  **调用初始化**：在 `main` 函数的开头，执行一次 `Timer_Init();`。
2.  **获取计数值 (可选)**：在 `while(1)` 循环中，可随时调用 `Timer_GetCount()` (它内部调用 `TIM_GetCounter(TIM2)`) 来读取定时器当前计数值（CNT寄存器的值）。

## 三、 编写中断服务函数 (在 `main.c` 中)

1.  **定义中断函数**：你需要实现一个特定名称的函数。对于TIM2，这个函数名固定为 `TIM2_IRQHandler(void)`。
2.  **检查中断标志**：在函数内部，**必须**先用 `if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)` 来判断是否真的是“更新中断”触发了。
3.  **执行中断任务**：在 `if` 语句块中，执行你希望的操作，例如 `Num++`。
4.  **清除中断标志**：在任务执行完毕后，**必须**调用 `TIM_ClearITPendingBit(TIM2, TIM_IT_Update);` 来清除标志位。
    * **警告：如果忘了这一步，中断会无限次触发，导致程序卡死在中断里。**

```c
// 中断服务函数示例 (位于 main.c)
void TIM2_IRQHandler(void){
    // 2. 检查标志
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
        
        // 3. 执行任务
        Num++;
        
        // 4. 清除标志
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}