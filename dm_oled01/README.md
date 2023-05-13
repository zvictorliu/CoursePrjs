移植一个基于HAL的例程到自己工程即可

把引脚全部设置为和示例一样的，如果不一样那么在oled.h里面的重新define部分和OLED_Init函数定义部分都要修改，比较麻烦，还是直接设置为一样的就好

`NSS`要不要设置按理论来讲应该没这必要，CS接地就好，实际没试过，但应该是可以不用管的？



如果不是基于HAL的而是基于标准库的，那么需要改的地方就更多了，且我也没成功过（~~但我现在怀疑是我当时没有按RESET键？~~）总的来说不建议移植这种（但这种应该也挺常见，一般是F系列的，而我们L4系列是HAL库的），此处感谢群里发的资料，例程里面有HAL库的，否则就不知道还要debug多久了



如果一直放在while循环里循环显示，则会阻塞到其它功能

其实只需要show一次即可

```c
HAL_Delay(500);
OLED_Clear();
OLED_ShowNum(103,48,24,3,16); // show num 24
OLED_Refresh();
```

103,48 是坐标；3是位数，表示显示的是`024`；16是字号大小

注意，字号只有16，24，32，64，分别对应于`oledfont.h`的Hzk1~4



CLK(SCK): PA5

DIN(SDA): PA7

RST: PD2

DC: PB5

CS(NSS): PA4

没看懂其中配置的：

PC12 PB6 好像没意义？



GPIO

```c
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_PULLUP;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
```



OLED_init有对SPI引脚的配置，而GPIO没有，应该在SPI

看来重新配置是不可避免的了
