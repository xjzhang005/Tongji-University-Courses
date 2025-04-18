# Final Assignment: Development of Virtual Engine Performance Monitor 虚拟发动机性能监控模块开发

[**Report**](https://) |  [**Poster**](https://) |  [**Video**](https://) | [**Project Page**](https://github.com/xjzhang005/Tongji-University-Courses/tree/main/Advanced-Language-Programming%E9%AB%98%E7%BA%A7%E8%AF%AD%E8%A8%80%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1/Project/Final-term-Engine-Simulation%E5%8F%91%E5%8A%A8%E6%9C%BA%E6%A8%A1%E6%8B%9F)



> If you find our work useful, please star this project and follow us: [**Personal Page**](https://github.com/xjzhang005)


# 📋 Demand 
## 题目描述
虚拟发动机模拟测试界面脱胎于发动机指示和机组警告系统（EICAS），EICAS则是用于飞机的发动机指示和告警显示画面。

## 要求说明
### 概述
本次作业需要你完成发动机转速动态变化的界面显示。你的程序应当分为两部分：

- 数据模拟生成：按照固定时间间隔（$5ms$）生成数据，模拟传感器的输入。
- 数据处理显示：接收模拟数据的输入，根据一定的规则显示在界面上。

数据生成和状态判断的规则详见下文。

### 数据类别说明
需要模拟生成的数据包括四个部分。假设飞机左右各一个发动机，仅一个油箱。

- 转速传感器：检测发动机转速 $N$，每台发动机有两个转速传感器。
- EGT (Exhaust Gas Temperature) 传感器：检测排气温度 $T$，每台发动机两个 EGT 传感器。
- 燃油余量传感器：生成油箱的燃油余量 $C$ 。每个油箱仅一个余量传感器。
- 燃油流速传感器：检测燃油的流速 $V$（即上一时刻燃油余量减去当前燃油余量的差值并除以时间）。

**注意：在单油箱的正常条件下，燃油的余量 $C$ 和燃油流速 $V$ 应当是相关的，不能随意生成。**

### 数据规则说明
下面所有函数参数可微调

发动机阶段主要分为三部分：启动阶段、稳定阶段和停车阶段。假定飞机一开始尚未启动，正常情况下，你的数据生成模块应当按照以下规则进行数据的生成。

- 启动阶段

  - 各个发动机转速以每秒 $10^4$ 转的速度线性增加，燃油流速以每秒 $5$ 单位的速度线性增加。该过程持续两秒。
  - 此后，燃油流速c按照对数函数速度增加，大致为 $V=42lg(t−1)+10$ ；同时，转速 $N$ 按照对数函数速度增加，大致为 $N=23000lg(t−1)+20000$ ；温度从 $T_0$ （本题规定为 $20℃$ ）开始按照对数速度增加，大致为 $T=900lg(t−1)+T_0$ 。该过程一直持续到转速达到额定转速的 $95\%$ 。

- 稳定阶段
  - 用户若无操作，则 $N,T,V$ 均动态平稳。（可在 $±3\%$ 波动）

- 停车阶段
  - 燃油流速 $V$ 直接归零，转速 $N$ 和温度 $T$ 以对数方式下降（自行设计对数函数模拟，底数 $0<a<1$ ，在十秒内停止）。

以上所有数据在变化时均可以小幅加减随机值，增强真实性。

### 有效值范围说明
- 燃油余量 $C$ 有效值范围： $0∼20000$ 单位，假定满油时为 $20000$ 单位。
- 燃油变化率 $V$ 有效值范围： $0∼50$ 单位每秒。
- 转速百分比 $N1$ 有效值范围： $0∼125$（也就是说当前转速 $N$ 不能超过额定转速的 $25\%$ ）
  > $N1$ 为当前转速 $N$ 与额定转速（本题假定为 $40000$ 转）的百分比值。
- 排气温度 $T$ 有效值范围： $−5∼1200℃$ ，排气温度初始值 $T_0$ 是室温，本题规定在 $20℃$ 。

## 任务划分
### 基础项（70分）
**表格文件记录10分，数据模拟生成模块30分，数据处理展示模块30分。**
- 按照上述规则，在有效值范围内生成合理的数据。

- 程序每次运行时，新建表格文件保存数据。界面每 $5ms$ 进行一次数据刷新，且将数据添加至表格文件中。表格文件格式自定，但需要包括**运行时间 + 所有生成的数据**，方便后续批阅。

- 你的表盘需要包括以下内容：
  - $N_1$ 发动机转速表
    - 数字指示：直接显示数字。
    - 表盘指示：使用扇形指示数据变化，正常数据的角度显示范围为 $0°∼210°$ 。
  - EGT发动机排气温度
    - 数字指示：直接显示数字。
    - 表盘指示：使用扇形指示数据变化，正常数据的角度显示范围为 $0°∼210°$ 。
  - 两大按钮
    - ```Start``` 按钮（开始起动程序）：按下后，将按照上述的启动规则进行数据生成。
    - ```Stop``` 按钮（开始停车程序）：按下后，将按照上述的停车规则进行数据生成。
      > ```Stop``` 按钮优先级高于其他所有按钮（包括加分项的按钮）

- 燃油流速
  - 数字指示：直接显示数字。

- 状态显示框
  - 包括启动 ```start``` 和 稳态 ```run``` ，亮暗规则如下：
    - ```Start``` 按钮按下后，程序正常启动，```start``` 窗口亮起。
    - 到达稳态后，```start``` 窗口变暗，```run``` 窗口亮起。
    - 此后，若 $N_1$ 下降至 $95$ 以下，则 ```run``` 窗口变暗。回升后则再次亮起。

### 进阶项（30分）
- 添加“增加推力”和“减小推力”按钮（10分）
  - 用户此时可以增加或降低推力，每增加 / 降低一次推力，则燃油流速 $V$ 增加/减少 $1$ 单位每秒，$N, T$ 在 $3\%∼5\%$ 的范围内随机加 / 减。

- 添加异常测试功能（20分）
  - 设计异常测试情况，程序可以产生 14 种异常情况的数据，且能够检测出这些异常情况。（见下文）
  - 使用其他颜色突出异常值 / 扇形，并添加文字警示。告警文字显示持续 $5s$ ，描述方式可自定义，但需英文。
  - 如果存在异常，应当将**运行时间 + 文字警示信息**保存至 log 文件。记录时，$5s$ 内同一种告警只记录一次。
> 界面上使用三种颜色表述四种状态，即 ```正常值（白色）``` 、 ```警戒值（琥珀色）``` 、 ```警告值（红色）``` 和 ```无效值（--）``` ，数字、表盘和告警均服从此规则。

-------------

以下是十四种异常情况的说明：
- 传感器异常
  - 单个转速传感器故障（无效值）：一切指示正常，只发一个传感器故障告警，白色警告
  - 单发转速传感器故障（无效值）：转速告警，其他正常工作，琥珀色警告
  - 单个EGT传感器故障（无效值）：一切指示正常，只发一个传感器故障告警，白色警告
  - 单发EGT传感器故障（无效值）：EGT告警，其他正常工作，琥珀色警告
  - 双发转速或EGT传感器故障（无效值）：发动机停车，红色警告

- 燃油异常
  - 燃油余量低于 $1000$ ，其他数据正常（除了停车和未启动）：燃油余量低告警，琥珀色警告
  - 燃油余量故障（无效值）：传感器故障告警，红色警告
  - 燃油流速超过 $50$ 单位每秒：燃油指示告警，琥珀色警告

- 转速异常
  - 超转1：发动机转速 $N_1>105$ ，琥珀色警告
  - 超转2：发动机转速 $N_1>120$ ，红色警告，**发动机停车**

- 温度异常
  - 超温1：启动过程中，EGT温度 $T>850℃$ ，琥珀色警告
  - 超温2：启动过程中，EGT温度 $T>1000℃$ ，红色警告，**发动机停车**
  - 超温3：稳态时，EGT温度 $T>950℃$ ，琥珀色警告
  - 超温4：稳态时，EGT温度 $T>1100℃$ ，红色警告，**发动机停车**

----------

## 产业提示
### 关于EICAS  
EICAS用于飞机的发动机指示和告警显示画面，它用于飞机的发动机指示和告警显示画面，用于显示飞机发动机的状态参数和襟翼与起落架的位置。主要包括以下功能：发动机指示、增压系统指示、燃油量指示、CAS信息指示、副翼/水平安定面/方向舵配平指示等。我们相当于进行了其中一小部分的开发，其界面如下：  
![Demo](./assets/demo.png)
> 但这也不是他的完整界面...

### 产业的代码要求  
该领域专家指出，在进行相关开发时，注重以下几点，供大家参考（不作为打分依据）：
- 编写程序时，不能有任何一行代码是测不到的
- 任何情况下，程序出现错误必须处理和上报
- 代码必须考虑多故障情况下的处理优先级和组合
- **适航领域特别强调安全性，不能使用任何一行没有验证和评审分析过的代码，也就是说不能随意调库（在实际开发中，甚至STL库可能也不允许使用），要么就用适航认证过没问题的工具**

----------

补充说明：

- 稳态时的 $3\%$ 波动，如果不希望状态显示框闪烁，可以只考虑燃油流速 $V$ 的波动，其他保持恒定。
- 实际情况下，转速如果在短时间内从 $95.5\%$ 下降至 $94.5\%$ 以下，会直接触发停车。



# 🪧 Overview

![Interface](./assets/示例界面.png)


# 🏗️️ Setup

### 🐍 Environment

We use **EasyX** to complete the UI design: [**EasyX**](https://easyx.cn/)

### 💾 Files

**structure**

```bash
engine-system
    ├── assets
      ├── demo.png
      ├── 示例界面.png
    ├── README.md
    ├── xjzhang005
      ├── engine-system.sln
      ├── main.cpp
      ├── engine.cpp
      ├── engine.h
      ├── gas.cpp
      ├── gas.h
      ├── mydefine.h
      ├── plane.cpp
      ├── plane.h
      ├── sensor.cpp
      ├── sensor.h
      ├── warnings.log
    ├── Lingzixuehan
      ├── FileName.cpp
      ├── 2353721贾博睿高程期末报告.docx
      ├── README.md

```

**Data and Log**






# 🗣️ Acknowledgements
If you find our work useful, please star this project and follow us:
[**Personal Page**](https://github.com/xjzhang005)


