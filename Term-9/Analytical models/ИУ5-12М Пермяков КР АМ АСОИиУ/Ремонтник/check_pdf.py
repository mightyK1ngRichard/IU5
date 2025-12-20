#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Скрипт для проверки содержимого PDF файлов
"""
import sys
import os

pdf_files = [
    "КР АМ АСОИУ титулы.pdf",
    "КР АМ АСОИУ титулы модель_АСОИУ.pdf",
    "КР АМ АСОИУ титул ремонтник.pdf"
]

print("Проверка PDF файлов на наличие текста 'Мамоу' или 'ИУ5-11М'...")
print("=" * 60)

for pdf_file in pdf_files:
    if os.path.exists(pdf_file):
        print(f"\nФайл: {pdf_file}")
        print(f"Размер: {os.path.getsize(pdf_file)} байт")
        # Попробуем прочитать как бинарный файл и найти текст
        try:
            with open(pdf_file, 'rb') as f:
                content = f.read()
                # Ищем текст в UTF-8 кодировке
                text_mamou = 'Мамоу'.encode('utf-8')
                text_group = 'ИУ5-11М'.encode('utf-8')
                text_perm = 'Пермяков'.encode('utf-8')
                text_group_new = 'ИУ5-12М'.encode('utf-8')
                
                if text_mamou in content:
                    print("  ✓ Найдено 'Мамоу' в бинарном содержимом")
                if text_group in content:
                    print("  ✓ Найдено 'ИУ5-11М' в бинарном содержимом")
                if text_perm in content:
                    print("  ✓ Найдено 'Пермяков' в бинарном содержимом")
                if text_group_new in content:
                    print("  ✓ Найдено 'ИУ5-12М' в бинарном содержимом")
        except Exception as e:
            print(f"  ✗ Ошибка при чтении: {e}")
    else:
        print(f"\nФайл не найден: {pdf_file}")

print("\n" + "=" * 60)
print("\nПримечание: Редактирование PDF файлов напрямую очень сложно.")
print("Рекомендуется использовать PDF редакторы (Adobe Acrobat, Foxit и т.д.)")
print("или создать новые PDF файлы с правильными данными.")

