# test-IR-16F690

Проект для тестування Інфрачервоних датчиків на відзеркалення від обєкту.

- Використовується аналоговий вхід для підключення інфрачервного приймача.
- Для виводу результату використовується ввімкнення сигнального світлодіоду.
- Для виводу результату ADC можливо використати RS232 (TX) Speed 57600 bod, 8N1, uint16.
- Використанно чип PIC 16F690. Internal oscillator Fosc=4Mhz.
 
Значення ADC від 0-1023 (10 біт), але якщо у приміщщені гоярть лампи рожарювання 220В, то вони заповнюють 
іфрачервний фон і данною схемою не визначити наявність об'єкту, так як значененя ADC при цьому є 25-35.

У приміщенні з осівітленням зі звичайними "економками", визачив наявність об'єкут на відстанні до 0,9м-1.0м. При цьому поріг визнаяененя об'єкту становив ADC=1010.



![Shema](https://github.com/lexxai/test-IR-16F690/raw/master/shema/shema.png "Shema")
