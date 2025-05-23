# Лабораторная работа №8

## Задание 1.

В автоматизированной системе управления технологическим процессом (АСУТП) обрабатываются сообщения трех типов (сообщения A,B,C), поступающие от производственного оборудования. Сообщения типа A поступают в среднем через каждые $t_1$ секунды. Сообщения типа B поступают в среднем через $t_2$ секунд, сообщения типа C – через $t_3$ c. Обработка одного сообщения типа A занимает в среднем $t_4$ мс, сообщения типа B – $t_5$ мс, сообщения типа C – $t_6$ мс. Интервалы времени между сообщениями и время обработки сообщений можно считать случайными величинами, распределенными по экспоненциальному закону. Под каждое сообщение имеется очередь в $m_A, m_B, m_C$ мест.

Предлагаются два варианта дисциплины обслуживания сообщений: а) с относительными приоритетами; б) с абсолютными приоритетами (возобновление обслуживания). При обслуживании с приоритетами более высокий приоритет должны иметь сообщения, требующие меньшего среднего времени обработки.

Требуется выбрать дисциплину обслуживания, обеспечивающую минимальное среднее время обработки всех сообщений (выполнить теоретический расчет и экспериментальный расчет).

```R
Variant<-13
set.seed(Variant+535)
t<-rexp(3, 0.5)
tt<-rexp(3,0.05)
ma<-sample(c(1,2,3),1)
mb<-sample(c(1,2,3),1)
mc<-sample(c(1,2,3),1)
D <- data.frame(t[1],t[2],t[3],tt[1],tt[2],tt[3], ma, mb, mc)
colnames(D)<-c('t1','t2','t3','t4','t5','t6', 'ma', 'mb', 'mc')
View(D)
```

## Задание 2.

Система электронного документооборота с автоматическим классификатором поступающей корреспонденции должна учитывать различную важность документов, количество типов документов $P$, средняя интенсивность поступления заявок $\lambda_1, \lambda_2, \ldots, \lambda_P$, средняя интенсивность обслуживания $\mu_1, \mu_2, \ldots, \mu_P$ соответственно, очередь неограничена. Приоритеты заявок $p_1<p_2<\ldots<p_P$.

Оценить среднее время нахождения каждого типа заявки в очереди (теоретически и экспериментально) для одного из 4 случаев:
- относительный фиксированный приоритет (V1);
- абсолютный фиксированный приоритет (V2);
- приоритет с зависимой задержкой без прерывания (V3);
- приоритет с зависимой задержкой с прерываниями (V4);

в соответствии с вариантом.

```R
Variant<-13
set.seed(Variant)
P<-sample(c(4, 6),1)
V<-sample(c("V1", "V2", "V3", "V4"),1)
if ((V=="V3") | (V=="V4")){
    b<-sort(sample(c(1:10),P))
    }
lambda<-runif(P)
mu<-runif(P,1,3)
View(data.frame(P,V))
if ((V=="V3") | (V=="V4")) {View(data.frame(lambda,mu, b))}
if ((V=="V1") | (V=="V2")) {View(data.frame(lambda,mu))}
```
