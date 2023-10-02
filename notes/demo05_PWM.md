## main

由按键检测进行调节

<img src="https://cdn.jsdelivr.net/gh/zvictorliu/typoraPics@main/img/image-20231002134727407.png" alt="image-20231002134727407" style="zoom:50%;" />

- 加减速，速度范围 $1 \sim 99$

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L76-L79

- 反向

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L82-L83

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L45

- run/stop

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L84

并实时显示速度信息和状态信息

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L87-L88

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L90

通过`PWM_OUT`实现驱动

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L98-L102

## PWM_OUT

通过PWM波驱动电机速度和方向

驱动函数：`PWM_OUT`

https://github.com/zvictorliu/CoursePrjs/blob/92319dd6d86760cde4d6ed5cf9897c88dfd6fce3/demo/demo05_PWM/Source/main.c#L23

具体原理也不必细探究了