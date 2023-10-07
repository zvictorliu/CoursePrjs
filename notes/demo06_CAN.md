## 关于CAN

控制器局域网（CAN），就类似局域网的效果

广播发送，接收方硬件过滤选择是否响应

CAN总线使用双绞线进行差分电压传输，两条信号线被称为CAN高（CAN_H)和CAN低(CAN_L）

两条线静态时表示为逻辑1，也被称作隐性；当两条线电压值出现差异时表示为逻辑0，也称作显性

配置上感觉很复杂

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L86

## main

CAN初始化

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L90-L91

环形缓冲区：

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/can/CanApp.h#L37

读写指针：表示分配了8位，用于指向一个`INT32U`的数据

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/can/CanApp.h#L28

所以这句话就是看读写指针是否指向不同位置：是则说明有数据在缓冲区，不是可能满可能为空，用`FullFlag`是否为1来看是不是满

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L103

`%08X`表示以8位16进制输出，输出的是读指针指向的一个字

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L104-L105

所以是将`RDB`和`RDA`打印出来

打印次数，4位显示：

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/main.c#L111-L113

如果读指针超出范围则从头开始：

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/main.c#L114-L116

并将`FullFlag`归零

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/main.c#L116

### 中断处理函数

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L42-L45

收到输入，调用：

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L56-L60

即写入缓冲区

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L158-L162

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L167

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L172-L174

同样，如果过皆从0开始，与读指针相遇说明满了，需修改标志

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo06_CAN/Source/can/CanApp.c#L174-L178