实现掉电记忆

I2C_ReadUint8: 读取某地址下的8bit数据

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/myI2C.c#L146-L148

所以这里是是先读取`ox01`为`No.1`

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/main.c#L54

再读取`0x00`为`No.02`

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/main.c#L58

打印在屏幕上之后，将`0x00`的数据写到`0x01`上去

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/main.c#L61

## while循环：

读取出来的数据递增并打印

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/main.c#L65-L67

并将其写入`0x00`

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo04_I2C/Source/main.c#L67

------

屏幕之上会有三个：`0x01` `0x00`  `i`

也没啥特别的，就是通过`I2C`协议进行访存读写

没必要去看Read和Write的具体实现

