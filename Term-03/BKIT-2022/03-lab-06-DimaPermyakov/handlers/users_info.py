# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
from aiogram import Dispatcher, types
from aiogram.dispatcher.filters.state import State, StatesGroup
from aiogram.dispatcher import FSMContext
from create_bot import dp, bot


async def func():
    pass


async def register_handlers(dp_main: Dispatcher):
    dp_main.register_message_handler(func, text='')
