// файл script .js
window.onload = function () {

    let a = ''
    let b = ''
    let expressionResult = ''
    let selectedOperation = null

// окно вывода результата
    let outputElement = document.getElementById("result")

// список объектов кнопок циферблата (id которых начинается с btn_digit_)
    let digitButtons = document.querySelectorAll('[id ^= "btn_digit_"]')

    function onDigitButtonClicked(digit) {
        if (!selectedOperation) {
            if ((digit !== '.') || (digit === '.' && !a.includes(digit))) {
                a += digit
            }
            outputElement.innerHTML = a
        } else {
            if ((digit !== '.') || (digit === '.' && !b.includes(digit))) {
                b += digit
                outputElement.innerHTML = b
            }
        }
    }

// устанавка колбек-функций на кнопки циферблата по событию нажатия
    digitButtons.forEach(button => {
        button.onclick = function () {
            const digitValue = button.innerHTML
            onDigitButtonClicked(digitValue)
        }
    });

// установка колбек-функций для кнопок операций
    document.getElementById("btn_op_mult").onclick = function () {
        if (a === '') return
        selectedOperation = 'x'
    }
    document.getElementById("btn_op_plus").onclick = function () {
        if (a === '') return
        selectedOperation = '+'
    }
    document.getElementById("btn_op_minus").onclick = function () {
        if (a === '') return
        selectedOperation = '-'
    }
    document.getElementById("btn_op_div").onclick = function () {
        if (a === '') return
        selectedOperation = '/'
    }

// кнопка очищения
    document.getElementById("btn_op_clear").onclick = function () {
        a = ''
        b = ''
        selectedOperation = ''
        expressionResult = ''
        outputElement.innerHTML = '0'
    }

// кнопка расчёта результата
    document.getElementById("btn_op_equal").onclick = function () {
        if (a === '' || b === '' || !selectedOperation)
            return

        switch (selectedOperation) {
            case 'x':
                expressionResult = (+a) * (+b)
                break;
            case '+':
                expressionResult = (+a) + (+b)
                break;
            case '-':
                expressionResult = (+a) - (+b)
                break;
            case '/':
                expressionResult = (+a) / (+b)
                break;
        }

        a = expressionResult.toString()
        b = ''
        selectedOperation = null

        outputElement.innerHTML = a
    }

// Backspace.
    document.getElementById('backspace_id').onclick = function () {
        if (a === '' || (selectedOperation && b === '')) return

        if (b === '') {
            if (a.length === 1) {
                a = ''
                outputElement.innerHTML = '0'
                return
            }

            a = a.slice(0, -1)
            outputElement.innerHTML = outputElement.innerHTML.slice(0, -1)
        } else {
            if (b.length === 1) {
                b = '0'
                outputElement.innerHTML = '0'
                return
            }

            b = b.slice(0, -1)
            outputElement.innerHTML = outputElement.innerHTML.slice(0, -1)
        }
    }
// Возведение в стень.
    document.getElementById('btn_op_degree').onclick = function () {
        if (a === '' || b !== '' || selectedOperation) return

        a = ((+a) * (+a)).toString()
        outputElement.innerHTML = a
    }
};
