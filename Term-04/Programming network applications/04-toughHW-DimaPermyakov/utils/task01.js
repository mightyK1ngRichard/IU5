/*
Задание 12 (3 уровень)
Проверить что строка является палиндромом. Палиндромом называется строка, которая пишется одинаково слева направо и
справа налево. Написать 2 решения.
isPalindrome('А роза упала на лапу Азора') // true isPalindrome(121) // true isPalindrome(1890) // false
 */

function isPalindrome1(dataString) {
    const correctedString = String(dataString).replace(/\s+/g, '')
    const reversedString = String(dataString).replace(/\s+/g, '').split('').reverse().join('')
    return correctedString === reversedString
}

function isPalindrome2(dataString) {
    let correctData;
    if (!isNaN(dataString)) {
        correctData = dataString.toString().replace(/\s+/g, '')
    } else {
        correctData = dataString.replace(/\s+/g, '').toLowerCase();
    }
    let start = 0;
    let end = correctData.length - 1;
    while (start < end) {
        if (correctData[start] !== correctData[end]) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}

module.exports = isPalindrome1;
module.exports = isPalindrome2;