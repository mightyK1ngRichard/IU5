# Лабораторная работа №2

## Задание 1.
Заданы три независимые целочисленные неотрицательные случайные величины $X_1, X_2, X_3$, необходимо найти математическое ожидание, дисперсию, среднее квадратическое отклонение и коэффициент вариации случайной величины $X_1+X_2+X_3$ численно и теоретически (из определения и с использованием производящей функции).
В таблице ниже по вариантам представлены соответствия значений случайной величины и их вероятности.

```R
Variant<-13
set.seed(Variant)
X1<-sample(c(1:20),5)
X2<-sample(c(3:100),5)
X3<-sample(c(0:40),5)
pp1<-runif(5)
p1<-pp1/sum(pp1)
pp2<-runif(5)
p2<-pp2/sum(pp2)
pp3<-runif(5)
p3<-pp3/sum(pp3)
```
