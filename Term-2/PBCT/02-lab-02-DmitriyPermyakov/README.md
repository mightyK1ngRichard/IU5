# Laboratory work 2.
<img src="https://img.shields.io/github/license/mightyK1ngRichard/IU5?color=brightgreen" alt="MIT License"> <img src="https://img.shields.io/badge/language-C++-purple.svg" alt="Python C++">

# Задание.
1.1.
1.	Ознакомиться с приведенным ниже материалом (Введение и Пример 1). Перейти в примере 1 от структуры к классу.
2.	Разработать класс «Планета» для планет солнечной системы (4 характеристики планет разного типа приведены в Приложении 1). Имя планеты должно иметь тип char*.
3.	Создать много-файловый проект и отладить программу, которая создает один объект класса «Планета» и выводит значения его полей на экран. (Пример программы приведен в Приложении 3).
4.	 Организовать интерфейс пользователя с программой в виде меню, позволяющий выполнять следующие действия: 
- чтение БД  «Солнечная система» из файла;
- запись БД  «Солнечная система» в файл;
- сортировка БД;
- добавление новой планеты в БД;
- удаление планеты из БД;
- редактирование БД;
- вывод БД на экран.
5.	Создать текстовый файл (в блокноте) с данными о планетах солнечной системы и сохранить его в папке проекта. Первоначально, для отладки, введите две записи.
6.	Добавить в программу ввод – вывод объекта класса «Планета» в текстовый файл. 

1.2.
1. Ознакомиться с содержанием раздела «Перегрузка операций» и выполнить приведенный в нем пример 2.
2. Перегрузить конструктор копирования, деструктор и оператор присваивания.
3. Вставьте в конструкторы и деструктор печать типа «Создание (Удаление) ID n » , где  n - номер объекта, для которого они вызываются. (Для реализации этого пункта задания разберите и выполните пример из Приложения 2.). 
4. Перегрузить операцию “ >> “ для класса «Планета»  и ifstream и прочитать данные о планетах из файла в массив «Солнечная система» из объектов класса «Планета».
5. Перегрузить операцию “ << “ для классов «Планета»  и ofstream и вывести на экран данные из массива.

1.3.
1. Перегрузить операции сравнения “ <  и ==” для класса «Планета», использовав для этого значение одного из полей.
2. Отсортировать массив планет солнечной системы, хранящийся в файле, с использованием перегруженных операций.

1.4. 
1. На основе разработанного класса Планета выполнить задание по варианту (не менее 4 характеристик в классе разного типа).
