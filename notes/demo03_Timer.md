## IRQ_Timer0

定义了一个定时中断服务程序（`IRQ`中断）

https://github.com/zvictorliu/CoursePrjs/blob/c8b20397e387a15506e48874d00e3fd21c1ed188/demo/demo03_Timer/Source/main.c#L20

作用就是记录当前时分秒

清除中断标志是为了避免中断嵌套，按理说应该放在开头的

https://github.com/zvictorliu/CoursePrjs/blob/c8b20397e387a15506e48874d00e3fd21c1ed188/demo/demo03_Timer/Source/main.c#L31

`T0IR`即 Timer0's Interupt Register

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928130803685.png" alt="image-20230928130803685" style="zoom:50%;" />

所以这里是写1就将其初始化？

竟然需要设置中断返回的地址，设置为`0x00`不知道是何意，想干什么

https://github.com/zvictorliu/CoursePrjs/blob/c8b20397e387a15506e48874d00e3fd21c1ed188/demo/demo03_Timer/Source/main.c#L32

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928132943345.png" alt="image-20230928132943345" style="zoom:50%;" />

## main

### 中断配置

这里的中断居然需要手动配置

https://github.com/zvictorliu/CoursePrjs/blob/c8b20397e387a15506e48874d00e3fd21c1ed188/demo/demo03_Timer/Source/main.c#L51-L55

- 中断选择寄存器

  <img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928132849614.png" alt="image-20230928132849614" style="zoom:50%;" />

- 向量控制寄存器

  <img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928132701028.png" alt="image-20230928132701028" style="zoom:50%;" />

  0x20 | 0x04 就是 100100

- 中断服务程序的地址，就是`IRQ_Timer0`的地址

  

  <img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928133404977.png" alt="image-20230928133404977" style="zoom: 67%;" />

- VICIntEnable 允许中断

  <img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928133043735.png" alt="image-20230928133043735" style="zoom:50%;" />

  Timer0就是位4，置1允许中断

要配置为IRQ同时还要使能

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928135932372.png" alt="image-20230928135932372" style="zoom:67%;" />

### 定时器配置

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928134031897.png" alt="image-20230928134031897" style="zoom:67%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928134130349.png" alt="image-20230928134130349" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928134254166.png" alt="image-20230928134254166" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928134717961.png" alt="image-20230928134717961" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928135314047.png" alt="image-20230928135314047" style="zoom:50%;" />

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20230928140319016.png" alt="image-20230928140319016" style="zoom:50%;" />

`Fpclk`预分频时钟频率，由系统时钟分频而来

就是计数器值达到`Fpclk`时就触发中断，此时为1秒

需要使能计数（TCR），设置阈值（MR0），控制匹配时干啥（MCR），设置每多少个pclk加1（PR）

## user

之后LCD的操作和上一个同理

然后是循环显示时间

https://github.com/zvictorliu/CoursePrjs/blob/c8b20397e387a15506e48874d00e3fd21c1ed188/demo/demo03_Timer/Source/main.c#L67-L71

