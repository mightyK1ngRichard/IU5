import {MainPage} from "/pages/main/index.js";

const root = document.getElementById('root');
const btn1 = document.getElementById('sort-buttons-1');
const btn2 = document.getElementById('sort-buttons-2');
const btn3 = document.getElementById('sort-buttons-up-id');
const btn4 = document.getElementById('sort-buttons-down-id');

const linkToVK = document.getElementById('vk-link');
linkToVK.addEventListener('click', function () {
    window.open('https://vk.com/kak_delaut_dvoeshniki')
});

btn1.addEventListener('click', function () {
    mainPage.sortingCards('возрастание')
});

btn2.addEventListener('click', function () {
    mainPage.sortingCards('убывание')
});

btn3.addEventListener('click', function () {
    mainPage.getSortedVKData(true)
});

btn4.addEventListener('click', function () {
    mainPage.getSortedVKData(false)
});

const mainPage = new MainPage(root);
mainPage.render();
