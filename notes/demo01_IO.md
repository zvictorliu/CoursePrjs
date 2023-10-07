核心在这里：

https://github.com/zvictorliu/CoursePrjs/blob/a193287216f559953ddd916c9567eff5661d7fd0/demo/demo01_IO/Source/main.c#L41-L44

其中 `IO0PIN`是一个指针：

https://github.com/zvictorliu/CoursePrjs/blob/3dc8afb82eae53ac51ec9399b5640a59f3640149/demo/demo01_IO/Source/LPC2294.h#L136-L139

第一个`*`是引用，第二个`*`表明是指针，这个就相当于地址为`ox0xE0028000`的值

也就是寄存器的地址

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007220245865.png" alt="image-20231007220245865" style="zoom:67%;" />

按键输入将修改寄存器对应位

所以通过`&`操作看是否相等来判断是否按下，若按下则点亮，没按下则是每次循环重复设置为关闭LED

## 控制原理

`IO0SET`寄存器的每个引脚对应了一个GPIO口（P0.0-P0.31)

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007215124539.png" alt="image-20231007215124539" style="zoom:80%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007215209490.png" alt="image-20231007215209490" style="zoom:67%;" />

所以`LED_AUTO`就是一个32位数据，中间一位为1

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo01_IO/Source/main.c#L26

赋给IO0SET，对应引脚为SET，赋给IO0CLR，对应引脚为IO0CLR

## 配置GPIO

选择相应的端口

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo01_IO/Source/main.c#L33-L35

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007215614834.png" alt="image-20231007215614834" style="zoom:67%;" />

至于为什么要`Capture`这也不是很清楚

然后配置输入输出模式，通过`IO0DIR`寄存器来实现

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo01_IO/Source/main.c#L35-L37

`KEY`是输入，取0，LED是输出，取1

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007215851864.png" alt="image-20231007215851864" style="zoom:67%;" />

## 喂狗

https://github.com/zvictorliu/CoursePrjs/blob/b34df340aaecf56bfbb25b61fcf426b153aacc71/demo/demo01_IO/Source/myI2C.c#L49-L53

也是控制输出引脚，一次喂狗操作为一次 高-低 输入，推测可能是通过下降沿来实现喂狗的吧，至于为什么要下降沿这个得结合WatchDog的电路了

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231007220109070.png" alt="image-20231007220109070" style="zoom:67%;" />
