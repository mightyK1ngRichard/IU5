import {ProductCardComponent} from "../../components/product-card/index.js";
import {ProductPage} from "../product/index.js";
import {ajax} from "../../modules/ajax.js";
import {urls} from "../../modules/urls.js";
import {groupId} from "../../modules/consts.js";
import {usersData} from "../../js/parcingData.js"

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    renderData(items) {
        items.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot)
            productCard.render(item, this.clickCard.bind(this))
        })
    }

    getData() {
        // MARK: - Lab04
        // ajax.post(urls.getGroupMembers(groupId), (data) => {
        //     usersData.data = data.response.items;
        //     this.renderData(data.response.items);
        // })

        // if else - для сохранения сортировки.
        if (usersData.data.length !== 0) {
            this.parent.innerHTML = ''
            const html = this.getHTML()
            this.parent.insertAdjacentHTML('beforeend', html)
            this.renderData(usersData.data)
        } else {
            // MARK: - Lab05
            ajax.post(urls.getGroupMembers(groupId))
                .then(response => response.json())
                .then(data => {
                    usersData.data = data.response.items
                    this.renderData(data.response.items)
                })
        }
    }

    getSortedVKData(isUp) {
        if (isUp) {
            ajax.post(urls.getSortedInfoUp(groupId))
                .then(response => response.json())
                .then(data => {
                    usersData.data = data.response.items
                    this.parent.innerHTML = ''
                    const html = this.getHTML()
                    this.parent.insertAdjacentHTML('beforeend', html)
                    this.renderData(usersData.data)
                })

        } else {
            ajax.post(urls.getSortedInfoDown(groupId))
                .then(response => response.json())
                .then(data => {
                    usersData.data = data.response.items
                    this.parent.innerHTML = ''
                    const html = this.getHTML()
                    this.parent.insertAdjacentHTML('beforeend', html)
                    this.renderData(usersData.data)
                })
        }
    }
    sortingCards(conditionOfSort) {
        let dataCopy = usersData.data;
        switch (conditionOfSort) {
            case 'возрастание':
                dataCopy.sort(function (a, b) {
                    if (a.first_name < b.first_name) {
                        return -1;
                    } else if (a.first_name > b.first_name) {
                        return 1;
                    } else {
                        if (a.last_name < b.last_name) {
                            return -1;
                        } else if (a.last_name > b.last_name) {
                            return 1;
                        }
                        return 0;
                    }
                })

                dataCopy.forEach((item) => {
                    const productCard = new ProductCardComponent(this.pageRoot)
                    productCard.render(item, this.clickCard.bind(this))
                });
                break;

            case 'убывание':
                dataCopy.sort(function (a, b) {
                    return a.first_name - b.first_name;
                })

                dataCopy.forEach((item) => {
                    const productCard = new ProductCardComponent(this.pageRoot)
                    productCard.render(item, this.clickCard.bind(this))
                })
                break;

            default:
                console.log('лол кек')
        }
        usersData.data = dataCopy
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        this.renderData(dataCopy)
    };

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
        document.getElementById('accordionExample').hidden = false
        document.getElementById('title-site-id').hidden = false
        this.parent.innerHTML = ''
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        this.getData()
    }

    clickCard(e) {
        const cardId = e.target.dataset.id
        const productPage = new ProductPage(this.parent, cardId)
        productPage.render()
    }
}