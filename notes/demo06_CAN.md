## 关于CAN

控制器局域网（CAN），就类似局域网的效果

广播放送，接收方硬件过滤选择是否响应

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

所以这句话就是看读写指针是否指向同一个位置，不同说明未满

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L103

`%08X`表示以8位16进制输出，输出的是读指针指向的一个字

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo06_CAN/Source/main.c#L104-L105

还是看不懂在干什么