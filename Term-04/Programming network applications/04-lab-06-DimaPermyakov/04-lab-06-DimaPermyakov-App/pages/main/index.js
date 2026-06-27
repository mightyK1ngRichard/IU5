import {ProductPage} from "../product/index.js";
import {ajax} from "../../modules/ajax.js";
import {urls} from "../../modules/urls.js";
import {usersData} from "../../js/parcingData.js"
import {ProductCardTypeTree} from "../../components/product-card/typeTreeCard.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    renderData(items) {
        items.forEach((item) => {
            const productCard = new ProductCardTypeTree(this.pageRoot)
            productCard.render(item, this.clickCard.bind(this))
        })
    }

    getData() {
        ajax.post(urls.getTypeTrees())
            .then(response => response.json())
            .then(data => {
                usersData.data = data
                this.renderData(data)
            })
    }

    get pageRoot() {
        return document.getElementById('main-page')
    }

    getHTML() {
        return (
            `
	            <div id="main-page" class="d-flex flex-wrap"><div/>  
	        `
        )
    }

    render() {
        // document.getElementById('title-site-id').hidden = false
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        this.getData()
    }

    clickCard(e) {
        const target = e.target;
        // Проверяем, на какой элемент было нажато
        if (target.classList.contains('photo-of-type-tree')) {
            // Было нажато на изображение
            const cardId = target.dataset.id;
            const productPage = new ProductPage(this.parent, cardId, usersData);
            productPage.render();

        } else if (target.classList.contains('delete-type')) {
            const cardId = target.dataset.id;
            if (showPasswordPrompt()) {
                fetch(urls.deleteTypeTree(cardId), {
                    method: 'DELETE',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({id: `${cardId}`})
                })
                    .then(response => {
                        if (!response.ok) {
                            throw new Error('Network response was not ok');
                        }
                        return response.json();
                    })
                    .then(data => {
                        console.log(data);
                        this.render()
                    })
                    .catch(error => {
                        console.error('Error:', error);
                    });
            }
        }
    }

}

function showPasswordPrompt() {
    const password = prompt("Введите пароль:");
    if (password === "430133") {
        return true

    } else if (password == null) {
        return false

    } else {
        alert("Неверный пароль!");
        return false
    }
}

// fetch('https://example.com/api/items/1', {
//   method: 'DELETE',
//   headers: {
//     'Content-Type': 'application/json'
//   },
//   body: JSON.stringify({id: 1})
// })
// .then(response => {
//   if (!response.ok) {
//     throw new Error('Network response was not ok');
//   }
//   return response.json();
// })
// .then(data => {
//   console.log(data);
// })
// .catch(error => {
//   console.error('Error:', error);
// });