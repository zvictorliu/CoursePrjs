# uC/OS-II操作系统

基于优先级的抢占式多任务实时操作系统

- 可以管理多达64个任务。由于它的作者占用和保留了8个任务，所以留给用户应用程序最多可有56个任务

- 为每个任务设置独立的堆栈空间，可以快速实现任务切换
- 每时每刻总是让优先级最高的就绪任务处于运行状态
- 在调用系统API 函数、中断结束、定时中断结束时总是执行调度算法，μC/OS-II通过事先计算好数据简化了运算量，通过精心设计就绪表结构使得延时可预知

一个任务可以理解为一个线程，和创建线程类似，只是需要给出堆栈空间

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L161-L165

这里是创建了一个`TaskStart`任务，用来创建其余任务

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L172

启动操作系统：

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L173

`TaskStart`完成后就退出了，但子任务都是`while(1)`

## 子任务

有四个子任务

- 硬件看门狗
- 键盘处理
- 捕获按键信息
- 屏幕控制

任务之间用信号量传递（更像是消息）

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L26-L29

### 硬件看门狗

消息的创建（赋值）：

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L38

这里是`Sem`消息

每隔一段时间喂狗

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L42

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L50-L51

喂了10次后发送信号量：

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L44-L49

### 捕获按键

忙等待按键事件发生：

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L90-L91

这里负责将消息传入邮箱

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L92

也就没了

### 键盘处理

`Mbox`类型消息（感觉这里没有控制互斥访问）

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L60

捕获按键进程将信息传入邮箱，这里是在等待邮箱消息

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L64

应该是会阻塞的

然后分析，赋值给`strkey`

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L65-L67

### 屏幕控制

等待`Sem`消息

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L124

然后将按键打印出来

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L127

以及一些`Cnt`记录

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L129-L131

## 总结

就是通过四个线程并行，能够实时在屏幕打印按键信息

这个`Sem`和`Mbox`消息，`Mbox`是可以传递信息的，而`Sem`只是信号

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L60

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L38

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L92

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L47

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L64

https://github.com/zvictorliu/CoursePrjs/blob/b91e31335718753fc39c05b0c83dbe509030b096/demo/demo07_uOS/app/main.c#L124