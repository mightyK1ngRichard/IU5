import {MainPage} from "../pages/main/index.js";
import {urls} from "../modules/urls.js";

const root = document.getElementById('root');

const linkToVK = document.getElementById('vk-link');
linkToVK.addEventListener('click', function () {
    window.open('https://vk.com/kak_delaut_dvoeshniki')
});

const addButton = document.getElementById('button_plus')
addButton.addEventListener('click', function () {
    const root = document.getElementById('root')
    root.innerHTML = `
    <link rel="stylesheet" href="../CSS/AddendumStyle.css">
    <div class="login-box">
    <h2>Создание нового вида</h2>
    <form>
      <div class="user-box">
        <input type="text" name="" id="name-type" required="">
        <label>Имя вида</label>
      </div>
      <div class="user-box">
        <input type="text" name="" id="link-to-photo" required="">
        <label>URL на фото</label>
      </div>
      <div class="user-box">
        <input type="text" name="" id="notes-of-type" required="">
        <label>Описание</label>
      </div>
      <a href="#" id="save">
        <span></span>
        <span></span>
        <span></span>
        <span></span>
        Сохранить
      </a>
      <a id="cancel">
      Назад
      </a>
    </form>
    </div>
    `
    const save = document.getElementById('save')
    const cancel = document.getElementById('cancel')
    const input1 = document.getElementById('name-type')
    const input2 = document.getElementById('link-to-photo')
    const input3 = document.getElementById('notes-of-type')

    save.addEventListener('click', function () {
        if (input1.value === "" || input2.value === "") {
            alert("Заполните имя и ссылку!")
            return
        }

        fetch(urls.addTypeTree(), {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                name: `${input1.value}`,
                photoURL: `${input2.value}`,
                notes: `${input3.value}`
            })
        })
            .then(response => response.json())
            .then(() => {
                const mainPage = new MainPage(root)
                mainPage.render()
            })
            .catch(error => console.error(error));

    })
    cancel.addEventListener('click', function () {
        const mainPage = new MainPage(root)
        mainPage.render()
    })
})

const mainPage = new MainPage(root);

mainPage.render();
