import streamlit as st
import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import GridSearchCV
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
import seaborn as sns

# Функция для загрузки данных
@st.cache
def load_data():
    data = pd.read_csv('heart.csv')  # Укажите путь к вашему датасету
    return data

# Функция для предобработки данных
@st.cache
def preprocess_data(data_in):
    data_out = data_in.copy()
    
    # Масштабирование признаков
    scaler = MinMaxScaler()
    scaled_data = scaler.fit_transform(data_out[['age', 'chol', 'thalachh']])
    data_out[['age', 'chol', 'thalachh']] = scaled_data
    
    return data_out, data_out['output']  # Предположим, что 'output' - целевая переменная

# Загрузка и предварительная обработка данных
data = load_data()
data_X, data_y = preprocess_data(data)

st.subheader('Датасет')
st.write(data.head())  # Добавление data.head()

# Вычисление матрицы корреляций
corr_matrix = data.corr()

# Визуализация матрицы корреляций с помощью тепловой карты
st.subheader('Матрица корреляций')
fig, ax = plt.subplots(figsize=(10, 8))
sns.heatmap(corr_matrix, annot=True, fmt='.2f', linewidths=.5, ax=ax)
st.pyplot(fig)  # Добавление матрицы корреляци

# Интерфейс пользователя
st.sidebar.header('Метод ближайших соседей (KNN)')
cv_slider = st.sidebar.slider('Количество фолдов:', min_value=3, max_value=10, value=3, step=1)
neighbor_slider = st.sidebar.slider('Число соседей (K):', min_value=1, max_value=20, value=5, step=1)

# Подбор гиперпараметра
n_range_list = list(range(1, 100, neighbor_slider))  # Установите максимальное значение в соответствии с вашими данными
n_range = np.array(n_range_list)
tuned_parameters = [{'n_neighbors': n_range}]

clf_gs = GridSearchCV(KNeighborsClassifier(), tuned_parameters, cv=cv_slider, scoring='accuracy')
clf_gs.fit(data_X, data_y)

st.subheader('Оценка качества модели')
st.write('Лучшее значение параметра - Число соседей (K): {}'.format(clf_gs.best_params_['n_neighbors']))

# Изменение качества на тестовой выборке в зависимости от числа соседей
fig1 = plt.figure(figsize=(7,5))
plt.plot(n_range, clf_gs.cv_results_['mean_test_score'])
plt.xlabel('Число соседей (K)')
plt.ylabel('Средняя точность (accuracy)')
plt.title('Зависимость точности от числа соседей')
st.pyplot(fig1)