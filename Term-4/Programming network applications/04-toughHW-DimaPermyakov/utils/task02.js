/*
Задание 13 (2 уровень)
Напишите функцию diff, которая возвращает массив, содержащий все элементы первого, которые не находятся во втором.
 */

function diff(firstArray, secondArray) {
    return firstArray.filter((item) => !secondArray.includes(item))
}

module.exports = diff