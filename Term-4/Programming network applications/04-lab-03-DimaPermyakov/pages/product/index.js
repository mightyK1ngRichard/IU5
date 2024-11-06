import {ProductComponent} from "../../components/product/index.js";
import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";

export class ProductPage {
    constructor(parent, id, infoAboutProduct) {
        this.parent = parent
        this.id = id
        this.info = infoAboutProduct
    }

    getData() {
        return {
            id: 1,
            src: this.info.src,
            title: this.info.title,
            description: this.info.description,
            text: this.info.text,
            linkToTheSource: this.info.linkToTheSource
        }
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <div id="product-page"></div>
            `
        )
    }

    getMyTitle() {
        return(
            `
            <div id="strong">
                <h3>Дизайн - великий дар.</h3>
                <p>В свои 19 я владею искусством стиля. Я познал дизайн за какие-то 2 часа. Теперь мой долг - научить вас.</p>
            </div>
            `
        )
    }

    clickBack() {
        const mainPage = new MainPage(this.parent)
        document.getElementById('strong').insertAdjacentHTML('beforebegin', this.getMyTitle())
        mainPage.render()
    }

    render() {
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)

        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))

        const data = this.getData()
        const stock = new ProductComponent(this.pageRoot)
        stock.render(data)
    }
}