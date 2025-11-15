## STM32 TIM (定时器) 常用缩写汇总

### 1. 基础与通用 (General)

| 缩写          | 英文全称                    | 中文含义       | 备注                 |
| :------------ | :-------------------------- | :------------- | :------------------- |
| **TIM**       | Timer                       | 定时器         |                      |
| **ADV TIM**   | Advanced-Control Timer      | 高级控制定时器 | 如图所示             |
| **GP TIM**    | General-Purpose Timer       | 通用定时器     |                      |
| **BASIC TIM** | Basic Timer                 | 基本定时器     |                      |
| **RCC**       | Reset and Clock Control     | 复位和时钟控制 | (图中) 为TIM提供时钟 |
| **PWM**       | Pulse Width Modulation      | 脉冲宽度调制   | TIM的常用功能        |
| **ADC**       | Analog-to-Digital Converter | 模数转换器     | (图中) TIM可触发ADC  |
| **DAC**       | Digital-to-Analog Converter | 数模转换器     | (图中) TIM可触发DAC  |

### 2. 时钟、触发与主从模式 (Clock, Trigger & Master/Slave)

| 缩写       | 英文全称                    | 中文含义         | 备注                 |
| :--------- | :-------------------------- | :--------------- | :------------------- |
| **CK_INT** | Clock Internal              | 内部时钟         | (图中) 来自RCC       |
| **CK_PSC** | Clock for Prescaler         | 预分频器时钟     |                      |
| **CK_CNT** | Clock for Counter           | 计数器时钟       |                      |
| **ETR**    | External Trigger            | 外部触发         | (图中)               |
| **ETRP**   | ETR Prescaler               | 外部触发预分频器 | (图中)               |
| **ETRF**   | ETR Filter                  | 外部触发滤波器   | (图中)               |
| **ITR**    | Internal Trigger            | 内部触发         | (图中)               |
| **TRC**    | Trigger Controller          | 触发控制器       | (图中)               |
| **TRGI**   | Trigger Input               | 触发输入         | (图中) `TRG`=Trigger |
| **TRGO**   | Trigger Output              | 触发输出         | (图中)               |
| **SMS**    | Slave Mode Selection        | 从模式选择       |                      |
| **MMS**    | Master Mode Selection       | 主模式选择       |                      |
| **SMCR**   | Slave Mode Control Register | 从模式控制寄存器 |                      |

### 3. 核心寄存器与计数器 (Core Registers & Counter)

| 缩写     | 英文全称                      | 中文含义           | 备注                  |
| :------- | :---------------------------- | :----------------- | :-------------------- |
| **CNT**  | Counter                       | 计数器             | (图中) 核心计数单元   |
| **PSC**  | Prescaler                     | 预分频器           | (图中)                |
| **ARR**  | Auto-Reload Register          | 自动重装载寄存器   | (图中)                |
| **RCR**  | Repetition Counter Register   | 重复次数计数器     | (图中) 高级定时器特有 |
| **UI**   | Update Interrupt              | 更新中断           |                       |
| **UG**   | Update Generation             | 更新事件生成       |                       |
| **DIER** | DMA/Interrupt Enable Register | DMA/中断使能寄存器 |                       |
| **SR**   | Status Register               | 状态寄存器         |                       |
| **EGR**  | Event Generation Register     | 事件生成寄存器     |                       |

### 4. 输入/输出通道 (Input/Output Channels)

| 缩写       | 英文全称                        | 中文含义                | 备注                |
| :--------- | :------------------------------ | :---------------------- | :------------------ |
| **CHx**    | Channel (1, 2, 3, 4)            | 通道 (1, 2, 3, 4)       | (图中) 如 TIMx_CH1  |
| **CHxN**   | Complementary Channel           | 互补通道                | (图中) 如 TIMx_CH1N |
| **TIx**    | Timer Input (1, 2, 3, 4)        | 定时器输入 (1, 2, 3, 4) | (图中)              |
| **ICx**    | Input Capture                   | 输入捕获                | (图中)              |
| **ICxPS**  | Input Capture Prescaler         | 输入捕获预分频器        | (图中)              |
| **TIxFPx** | Filtered Timer Input            | 滤波器定时器输入        | (图中)              |
| **OCx**    | Output Compare                  | 输出比较                | (图中)              |
| **OCxREF** | Output Compare Reference        | 输出比较参考信号        | (图中)              |
| **OCxN**   | Output Compare Complementary    | 输出比较互补            | (图中)              |
| **CCRx**   | Capture/Compare Register        | 捕获/比较寄存器         | (图中)              |
| **CCMRx**  | Capture/Compare Mode Register   | 捕获/比较模式寄存器     |                     |
| **CCER**   | Capture/Compare Enable Register | 捕获/比较使能寄存器     |                     |

### 5. 刹车与死区 (Break & Dead-Time)

* *此部分是高级定时器 (ADV TIM) 的关键功能*

| 缩写     | 英文全称                     | 中文含义         | 备注   |
| :------- | :--------------------------- | :--------------- | :----- |
| **BKIN** | Break Input                  | 刹车输入         | (图中) |
| **BRK**  | Break                        | 刹车             | (图中) |
| **DTG**  | Dead-Time Generator          | 死区发生器       | (图中) |
| **BDTR** | Break and Dead-Time Register | 刹车和死区寄存器 |        |
| **MOE**  | Main Output Enable           | 主输出使能       |        |
| **AOE**  | Automatic Output Enable      | 自动输出使能     |        |
| **CSS**  | Clock Security System        | 时钟安全系统     | (图中) |
