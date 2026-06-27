# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
from aiogram.types import InlineKeyboardButton, InlineKeyboardMarkup

search_markup = InlineKeyboardMarkup(resize_keyboard=True)
buttons = (
    ('👍', 'like'),
    ('📝', 'write'),
    ('👎', 'dislike'),
    ('💤', 'info')
)
search_markup.row(*(InlineKeyboardButton(text, callback_data=data) for text, data in buttons))
