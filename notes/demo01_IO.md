核心在这里：

https://github.com/zvictorliu/CoursePrjs/blob/3dc8afb82eae53ac51ec9399b5640a59f3640149/demo/demo01_IO/Source/main.c#L41C1-L44C21

其中 `IO0PIN`是一个指针：

https://github.com/zvictorliu/CoursePrjs/blob/3dc8afb82eae53ac51ec9399b5640a59f3640149/demo/demo01_IO/Source/LPC2294.h#L136C40-L136C40

第一个`*`是引用，第二个`*`表明是指针，这个就相当于地址为`ox0xE0028000`的值

按键输入就会修改这个地址下的内容，从而和定义的几种行为比较

同理`IO0SET`就是修改相应的地址单元，相当于控制寄存器，使得灯亮起来