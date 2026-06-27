# Copyright © 2022 mightyK1ngRichard <dimapermyakov55@gmail.com>

from flask import Flask
from src.functions import fibonacci

app = Flask(__name__)


@app.route('/')
def index():
    return 'Hello World'


@app.route('/num/<number>')
def num(number):
    return str(list(fibonacci(int(number))))[1:-1]
