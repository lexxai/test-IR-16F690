# test-IR-16F690

Проект для тестування Інфрачервоних датчиків на відзеркалення від обєкту.

- Використовується аналоговий вхід для підключення інфрачервного приймача.
- Для виводу результату використовується ввімкнення сигнального світлодіоду.
- Для виводу результату ADC можливо використати RS232 (TX) Speed 57600 bod, 8N1, uint16.
- Використанно чіп Microchip PIC16F690. Internal oscillator Fosc=4Mhz.
- Мова програмування - C. Компілятор - Microchip XC8. Середа розробки - MPLAB X IDE.
 
Значення ADC від 0-1023 (10 біт), але якщо у приміщщені гоярть лампи рожарювання 220В, то вони заповнюють 
іфрачервний фон і данною схемою не визначити наявність об'єкту, так як значененя ADC при цьому є 25-35.

У приміщенні з осівітленням зі звичайними "економками", визачив наявність об'єкут на відстанні до 0,9м-1.0м. При цьому поріг визнаяененя об'єкту становив ADC=1010.

Наступний етап, використання TSSP ...

Спробував TSSP 4838, але зрозумів що це те те що потрбіно, з'ясував що є:
TSSP 4038 presencre sensor http://www.vishay.com/docs/82458/tssp40.pdf

http://www.vishay.com/ir-receiver-modules/presence-sensor/



![Shema](https://github.com/lexxai/test-IR-16F690/blob/TSOP/shema/shema.png "Shema")

![prototype 1](https://lh6.googleusercontent.com/1Tlwczcu5GIQi1g7NO9YDvpfdIDF0RYjtWxJO4FzAxI=w958-h546 "prototype 1")
![prototype 1](https://lh6.googleusercontent.com/-xx-TiCHkMM8/Vj_PRcAvU5I/AAAAAAAAJHw/4qjTbIQ568E/w958-h488-no/IMG_1351.JPG "prototype 1")
![prototype 1](https://lh6.googleusercontent.com/-oHt2x21S00U/Vj_PQP8Z2ZI/AAAAAAAAJHk/5vHUPwWIsPo/w958-h815-no/IMG_1349.JPG "prototype 1")
