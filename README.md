---
title: RC522+STM32硬件自助结算模块
date: 2018-04-15 18:57:45
tags: 
- 硬件
- 射频
---
Github代码仓库
--
https://github.com/Meow-starone/Settlement-module-BC
<br>

产品逻辑说明
----

用户通过带有电子标签的产品接触射频模块时，读取标签码并匹配对应商品信息，设置sum函数记录总价并实时显示，刷支付卡扣款完成一次完整逻辑，每次刷卡有对于蜂鸣器提示信息。<br>

电路设计原理图
--
<div align="center">![电路原理](http://i1.bvimg.com/641583/aa387cc05961657a.png)</div>
包括：RC522射频模块、MINISTM32F103、0.96存OLED、S50卡、低电平触发的蜂鸣器。<br>

实物测试效果
---
<div align="center">![实物测试](http://i1.bvimg.com/641583/ae5fcf179e37c1cct.jpg)</div>
