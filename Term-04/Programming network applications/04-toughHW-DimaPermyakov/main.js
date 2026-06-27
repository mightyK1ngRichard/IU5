const isPalindrome1 = require('./utils/task01')
const isPalindrome2 = require('./utils/task01')
const diff = require('./utils/task02')

console.log('===== 1 =====');
let data;
data = 122;
console.log(`isPalindrome1 for "${data}" - `, isPalindrome1(data));
console.log(`isPalindrome2 for "${data}" - `, isPalindrome2(data));
data = "А роза упала на лапу Азора"
console.log(`isPalindrome1 for "${data}" - `, isPalindrome1(data));
console.log(`isPalindrome2 for "${data}" - `, isPalindrome2(data));
data = '1221'
console.log(`isPalindrome1 for "${data}" - `, isPalindrome1(data));
console.log(`isPalindrome2 for "${data}" - `, isPalindrome2(data));
data = ' 1221  '
console.log(`isPalindrome1 for "${data}" - `, isPalindrome1(data));
console.log(`isPalindrome2 for "${data}" - `, isPalindrome2(data));

console.log('===== 2 =====');
let arr1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
let arr2 = [1, 2, 3, 4, 5];
console.log(`diff for \nARR1 = [${arr1}]\nARR2 = [${arr2}]\nRESULT: `, diff(arr1, arr2));
