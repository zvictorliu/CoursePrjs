基于I2C通信控制LCD模块（C 系列中文液晶显示模块）

这里的`include`包含了其它头文件，声明在`config.h`

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L10

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/config.h#L24-L25

就利用好`myLCD`提供好的函数接口就行了

先切换模式再配置显示的东西

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L23-L26

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L27-L29



------



# More...

## Init

### LCD_Init:

配置仍然是选择端口，配置输入输出

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L11-L13

剩余部分是一个同步串行通信，进行复位和片选

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L14-L19

### I2C_Init

同样是配置输出

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myI2C.c#L37-L38

## 主要函数

### LCD_SetMode：

分层设计：SetMode -> SendData -> SendByte

到最低层就是寄存器的操作了，采用同步串行通信

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L32-L33

依次取byte的最高位，为1则输出高，为0则输出低，同时有时钟同步信号

https://github.com/zvictorliu/CoursePrjs/blob/3b9c5f26a814c7b7af79c3bbcc471ef4d29ee73d/demo/demo02_LCD/Source/myLCD.c#L35-L38

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231008104522197.png" alt="image-20231008104522197" style="zoom:67%;" />

这里应该是向LCD串行发送控制命令

### LCD_DrawOUT：

这里面已经把图片数据集放进去了

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L120-L122

所以如果想修改图片的话就需要替换：

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L125

### LCD_TextOut

输入参数说明：

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L84

应该是自己编码好中文的

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L101

`*p++`和`*(p++)`效果没有区别，先取`*p`修改后，再`p++`，所以这里应该是逐个字符的意思

反正不管咋做到的吧，是能支持中文的

同样也是通过`LCD_SDA`串行同步发送