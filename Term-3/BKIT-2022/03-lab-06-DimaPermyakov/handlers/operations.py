# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>
from aiogram import Dispatcher, types
from aiogram.dispatcher.filters.state import State, StatesGroup
from aiogram.dispatcher import FSMContext
import aiogram.utils.markdown as md
from keyboards.menu_bts import start_markup
from keyboards.search_ib import search_markup
from utils.db_management import *
from create_bot import dp


class FSMUsers(StatesGroup):
    id_user = State()
    photo = State()
    name = State()
    age = State()
    place = State()
    university = State()
    department = State()
    description = State()


class FSMChangeUserData(StatesGroup):
    photo = State()


async def handler_start(message: types.Message):
    # Если пользователь уже зарегистрирован.
    user_data = get_user_data(message.chat.id)
    if user_data is not None:
        text = "Класс! Вы уже зарегистрированы!"
        await message.answer(text=text)
        await message.answer_photo(
            photo=user_data[7],
            caption=md.text(
                md.text('Так выглядит Ваша анкета:\n'),
                md.text(f'{user_data[1]}, {user_data[2]}, {user_data[3]}'),
                md.text(f'{user_data[4]}, {user_data[5]}'),
                md.text('О себе:'),
                md.text(user_data[6]),
                sep='\n',
            )
        )
        await message.answer('Выберите дальнейший сценарий:', reply_markup=start_markup)

    else:
        await message.answer("О, новичок!\nДавайте Вас зарегистрируем!")
        await FSMUsers.photo.set()
        await message.answer("Отправьте ваше фото:")


async def catch_photo(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['photo'] = message.photo[0].file_id

    # print(len(data))
    await FSMUsers.next()
    await message.reply('Теперь введите Ваше имя:')
    # TODO: Поменять на новую машину состояний.
    # else:
    #     temp_id = message.chat.id
    #     update_user_photo(temp_id, data['photo'])
    #     new_data = get_user_data(temp_id)
    #     await message.answer_photo(
    #         photo=new_data[7],
    #         caption=md.text(
    #             md.text('Так выглядит Ваша анкета:\n'),
    #             md.text(f'{new_data[1]}, {new_data[2]}, {new_data[3]}'),
    #             md.text(f'{new_data[4]}, {new_data[5]}'),
    #             md.text('О себе:'),
    #             md.text(new_data[6]),
    #             sep='\n',
    #         )
    #     )
    #     await message.answer('Выберите новый сценарий:', reply_markup=start_markup)


async def catch_name(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['name'] = message.text
    await FSMUsers.next()
    await message.reply('Введите ваш возраст:')


async def catch_age(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['age'] = message.text
    await FSMUsers.next()
    await message.reply('Введите ваш город:')


async def catch_place(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['place'] = message.text
    await FSMUsers.next()
    await message.reply('Введите название вашего университета:')


async def catch_university(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['university'] = message.text
    await FSMUsers.next()
    await message.reply('Введите название вашего факультета:')


async def catch_department(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['department'] = message.text
    await FSMUsers.next()
    await message.reply('Расскажите что-то о себе:')


async def catch_description(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['description'] = message.text
    async with state.proxy() as data:
        try:
            await message.answer_photo(
                photo=data['photo'],
                caption=md.text(
                    md.text('Так выглядит Ваша анкета:\n'),
                    md.text(f"{data['name']}, {data['age']}, {data['place']}"),
                    md.text(f"{data['university']}, {data['department']}"),
                    md.text('О себе:'),
                    md.text(data['description']),
                    sep='\n',
                )
            )
            # Добавляет в SQL таблицу.
            if user_presents(message.chat.id):
                update_user_data(message.chat.id, dict(data))
            else:
                set_user_date(message.chat.id, dict(data))
        except KeyError:
            temp_id = message.chat.id
            update_user_description(temp_id, message.text)
            new_data = get_user_data(temp_id)
            await message.answer_photo(
                photo=new_data[7],
                caption=md.text(
                    md.text('Так выглядит Ваша анкета:\n'),
                    md.text(f'{new_data[1]}, {new_data[2]}, {new_data[3]}'),
                    md.text(f'{new_data[4]}, {new_data[5]}'),
                    md.text('О себе:'),
                    md.text(new_data[6]),
                    sep='\n',
                )
            )
    await state.finish()
    await message.answer('Выберите новый сценарий:', reply_markup=start_markup)


async def all_msg_handler(message: types.Message):
    button_text = message.text

    if button_text == 'Заполнить анкету заново':
        await FSMUsers.photo.set()
        await message.answer("Отправьте ваше фото:", reply_markup=types.ReplyKeyboardRemove())

    elif button_text == 'Изменить фото':
        await FSMChangeUserData.photo.set()
        await message.reply("Отправьте ваше новое фото:", reply_markup=types.ReplyKeyboardRemove())

    elif button_text == 'Изменить текст анкеты':
        await FSMUsers.description.set()
        await message.reply("Расскажите что-то о себе:", reply_markup=types.ReplyKeyboardRemove())

    elif button_text == 'Искать друзей 🤝':
        user_data = get_random_user_form(message.chat.id)
        await message.answer('Поиск друзей!', reply_markup=types.ReplyKeyboardRemove())
        await message.delete()
        await message.answer_photo(
            photo=user_data[7],
            caption=md.text(
                md.text(f"{user_data[1]}, {user_data[2]}, {user_data[3]}"),
                md.text(f"{user_data[4]}, {user_data[5]}"),
                md.text('О себе:'),
                md.text(user_data[6]),
                sep='\n',
            ),
            reply_markup=search_markup
        )
        # await message.reply(reply_text)

    else:
        reply_text = "Keep calm... Everything is fine, you just a silly"
        await message.reply(reply_text)
        await message.delete()


async def update_user_photo_fsm(message: types.Message, state: FSMContext):
    async with state.proxy() as data:
        data['photo'] = message.photo[0].file_id
    temp_id = message.chat.id
    update_user_photo(temp_id, data['photo'])
    new_data = get_user_data(temp_id)
    await message.answer_photo(
        photo=new_data[7],
        caption=md.text(
            md.text('Так выглядит Ваша анкета:\n'),
            md.text(f'{new_data[1]}, {new_data[2]}, {new_data[3]}'),
            md.text(f'{new_data[4]}, {new_data[5]}'),
            md.text('О себе:'),
            md.text(new_data[6]),
            sep='\n',
        )
    )
    await state.finish()
    await message.answer('Выберите новый сценарий:', reply_markup=start_markup)


@dp.callback_query_handler(text=['like', 'write', 'dislike', 'info'])
async def inline_kb_answer_callback_handler(query: types.CallbackQuery):
    answer_data = query.data

    if answer_data == 'like':
        text = 'В разработке!'
        await query.message.answer(text)

    elif answer_data == 'write':
        text = 'В разработке!'
        await query.message.answer(text)

    elif answer_data == 'dislike':
        user_data = get_random_user_form(query.message.chat.id)
        await query.message.answer_photo(
            photo=user_data[7],
            caption=md.text(
                md.text(f"{user_data[1]}, {user_data[2]}, {user_data[3]}"),
                md.text(f"{user_data[4]}, {user_data[5]}"),
                md.text('О себе:'),
                md.text(user_data[6]),
                sep='\n',
            ),
            reply_markup=search_markup
        )

    elif answer_data == 'info':
        user_data = get_user_data(query.message.chat.id)
        await query.message.answer_photo(
            photo=user_data[7],
            caption=md.text(
                md.text('Так выглядит Ваша анкета:\n'),
                md.text(f'{user_data[1]}, {user_data[2]}, {user_data[3]}'),
                md.text(f'{user_data[4]}, {user_data[5]}'),
                md.text('О себе:'),
                md.text(user_data[6]),
                sep='\n',
            )
        )
        await query.message.answer('Выберите дальнейший сценарий:', reply_markup=start_markup)

    else:
        text = f'Unexpected callback data {answer_data!r}!'
        await query.message.answer(text)


def register_handlers(dp_main: Dispatcher):
    dp_main.register_message_handler(handler_start, commands=['start'])
    dp_main.register_message_handler(catch_photo, content_types=['photo'], state=FSMUsers.photo)
    dp_main.register_message_handler(update_user_photo_fsm, content_types=['photo'], state=FSMChangeUserData.photo)
    dp_main.register_message_handler(catch_name, state=FSMUsers.name)
    dp_main.register_message_handler(catch_age, lambda message: message.text.isdigit(), state=FSMUsers.age)
    dp_main.register_message_handler(catch_place, state=FSMUsers.place)
    dp_main.register_message_handler(catch_university, state=FSMUsers.university)
    dp_main.register_message_handler(catch_department, state=FSMUsers.department)
    dp_main.register_message_handler(catch_description, state=FSMUsers.description)
    # dp_main.register_message_handler(inline_kb_answer_callback_handler, text=['like', 'write', 'dislike', 'info'])
    # Last point!! Important!
    dp_main.register_message_handler(all_msg_handler)
