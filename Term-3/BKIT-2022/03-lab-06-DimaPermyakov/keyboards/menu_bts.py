# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
from aiogram.types import ReplyKeyboardMarkup, KeyboardButton

start_markup = ReplyKeyboardMarkup(resize_keyboard=True)
buttons = (
    'Заполнить анкету заново',
    'Изменить фото',
    'Изменить текст анкеты',
    'Искать друзей 🤝'
)

start_markup.row(*(el for el in buttons[:2])).row(*(el for el in buttons[2:4]))
