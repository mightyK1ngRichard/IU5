import {ProductComponent} from "../../components/product/index.js";
import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";
import {urls} from "../../modules/urls.js"
import {ajax} from "../../modules/ajax.js"

export class ProductPage {
    constructor(parent, id) {
        this.parent = parent
        this.id = id
    }

    renderData(item) {
        const product = new ProductComponent(this.pageRoot)
        product.render(item[0])
    }

    getData() {
        // MARK: - Lab04
        // ajax.post(urls.getUserInfo(this.id), (data) => {
        //         this.renderData(data.response)
        //     })

        // MARK: - Lab05
        ajax.post(urls.getUserInfo(this.id))
            .then(response => response.json())
            .then(data => {
                this.renderData(data.response)
            })
            .catch(error => console.error(error))
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <style>
                    @import url('https://fonts.googleapis.com/css2?family=Poppins:wght@200;300;400;500&display=swap');
                    body {
                        background-image: url(../../images/back.jpg);
                    }
                    * {
                        margin: 0;
                        padding: 0;
                        box-sizing: border-box;
                        font-family: 'Poppins', sans-serif;
                    }
                    
                    .main {
                        width: 100%;
                        height: 100vh;
                        display: flex;
                        align-items: center;
                        justify-content: center;
                        background-image: url(../../images/back.jpg);
                        background-position: center;
                        background-size: cover;
                    }
                    
                    .profile-card {
                        display: flex;
                        flex-direction: column;
                        align-items: center;
                        max-width: 600px;
                        width: 100%;
                        border-radius: 25px;
                        padding: 30px;
                        border: 1px solid #ffffff40;
                        box-shadow: 0 5px 20px rgba(0, 0, 0, 0.4);
                    }
                    
                    .image {
                        position: relative;
                        height: 150px;
                        width: 150px;
                    }
                    
                    .image .profile-pic {
                        width: 100%;
                        height: 100%;
                        object-fit: cover;
                        border-radius: 50%;
                        box-shadow: 0 5px 20px rgba(0, 0, 0, 0.4);
                    }
                    
                    .data {
                        display: flex;
                        flex-direction: column;
                        align-items: center;
                        margin-top: 15px;
                    }
                    
                    .data h2 {
                        font-size: 33px;
                        font-weight: 600;
                    }
                    
                    span {
                        font-size: 18px;
                    }
                    
                    .row {
                        display: flex;
                        align-items: center;
                        margin-top: 10px;
                    }
                    
                    .row .info {
                        text-align: center;
                        padding: 0 20px;
                    }
                    
                    .buttons {
                        display: flex;
                        align-items: center;
                        margin-top: 30px;
                    }
                    
                    .buttons .btn {
                        color: #fff;
                        text-decoration: none;
                        margin: 0 20px;
                        padding: 8px 25px;
                        border-radius: 25px;
                        font-size: 18px;
                        white-space: nowrap;
                        background: linear-gradient(to left, #33ccff 0%, #ff99cc 100%);
                    }
                    
                    .buttons .btn:hover {
                        box-shadow: inset 0 5px 20px rgba(0, 0, 0, 0.4);
                    }

                </style>
                <div id="product-page"></div>
            `
        )
    }


    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }

    render() {
        this.parent.innerHTML = ''
        document.getElementById('accordionExample').hidden = true
        document.getElementById('title-site-id').hidden = true
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)

        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
        this.getData()
    }

    м
}