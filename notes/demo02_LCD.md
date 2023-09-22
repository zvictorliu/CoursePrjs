基于I2C通信控制LCD模块（C 系列中文液晶显示模块）

这里的`include`包含了其它头文件，声明在`config.h`

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L10

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/config.h#L24-L25

就利用好`myLCD`提供好的函数接口就行了，不用多想

先切换模式再配置显示的东西

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L23-L26

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/main.c#L27-L29



------



# More...

## Init

### LCD_Init:

这里的配置真是看不懂什么意思

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L11-L13

剩余部分，先关CLK RST的LCD，再打开RST和CS的

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L14-L19

### I2C_Init

甚至只有配置

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myI2C.c#L37-L38

## 主要函数

### LCD_SetMode：

分层设计：SetMode -> SendData -> SendByte

到最低层就是寄存器的操作了，不必了解这么多

https://github.com/zvictorliu/CoursePrjs/blob/c56f974c1d6d1d86017f2047bb4e0fa72f0a470c/demo/demo02_LCD/Source/myLCD.c#L32-L33

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