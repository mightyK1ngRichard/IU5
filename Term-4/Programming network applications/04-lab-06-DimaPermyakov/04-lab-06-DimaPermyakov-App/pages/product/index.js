import {BackButtonComponent} from "../../components/back-button/index.js";
import {MainPage} from "../main/index.js";
import {typeAndTrees} from "../../components/product/typeAndTrees.js";

export class ProductPage {
    constructor(parent, id, data) {
        this.parent = parent
        this.id = id
        this.typeTreeData = data
    }

    renderData(item) {
        const product = new typeAndTrees(this.pageRoot)
        product.render(item[0])
    }

    getData() {
        const lookedID = this.id
        const foundData = this.typeTreeData.data.filter(function (d) {
            return d.type_id === lookedID;
        })
        this.renderData(foundData)
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

    clickBack() {
        const mainPage = new MainPage(this.parent)
        mainPage.render()
    }

    render() {
        this.parent.innerHTML = ''
        // document.getElementById('accordionExample').hidden = true
        // document.getElementById('title-site-id').hidden = true
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        const backButton = new BackButtonComponent(this.pageRoot)
        backButton.render(this.clickBack.bind(this))
        this.getData()
    }
}