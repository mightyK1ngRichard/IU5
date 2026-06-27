import {ProductCardComponent} from "../../components/product-card/index.js";
import {ProductPage} from "../product/index.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    getData() {
        return [
            {
                id: 1,
                src: "https://doka-stroi.ru/upload/iblock/6cc/e9fd32e64490498b7fcec3c0129dbd62.jpg",
                title: "Барная стойка - скажи стенам нет",
                description: "Великий дизайне рассказал всю правду о стиле.",
                text: "Портфолио — это не только демонстрация ваших профессиональных навыков, но и способ показать клиенту, что вы ориентированы на решение конкретных задач. Важно, чтобы проекты выглядели реалистично — даже если они вымышленные. Для этого нужно чётко представить портрет потенциального заказчика, понять, какие у него проблемы в бизнесе и как вы сможете помочь их решить. Как-то так закончил свою речь великий дизайнер.",
                linkToTheSource: "https://github.com/mightyK1ngRichard"
            },
            {
                id: 2,
                src: "https://www.mirlandshaft.ru/wp-content/uploads/2017/04/dizajn-interera-odnokomnatnoj-kvartiry7.jpg",
                title: "Стиль лофт",
                description: "Ещё более великий дизайнер рассказал тому дизайнеру о стиле.",
                text: "Даже если вам интересна работа в разных областях дизайна, для начала лучше сосредоточиться на чём-то одном. Среди востребованных направлений: дизайн сайтов, рекламы и айдентики. Вот так сказал ещё более велкий дизайнер.",
                linkToTheSource: "https://github.com/mightyK1ngRichard"
            },
            {
                id: 3,
                src: "https://loftecomarket.ru/wp-content/uploads/d/2/a/d2a386f9adb8bfa731354d314bd8738d.jpeg",
                title: "Дорого - значит хорошо. Хорошо - значит сделал я",
                description: "Вот самый великий дизайнер показал уровень",
                text: "Задача такого дизайна — привлечь внимание зрителя к рекламному сообщению. Обычно этого добиваются с помощью креативных идей, необычной композиции и ярких цветов. Для презентации digital-рекламы можно просто показать сам баннер или пост. А если вы делаете наружную или печатную рекламу, лучше показать, как она будет выглядеть в контексте: на улице, в магазине, внутри сайта. Проще всего это сделать с помощью мокапов. Вот так начал свою речь вот самый велкий дизайнер.",
                linkToTheSource: "https://github.com/mightyK1ngRichard"
            },
            {
                id: 4,
                src: "https://dizainexpert.ru/wp-content/uploads/2019/09/kvartira-v-svetlyx-tonax-i-sovremennom-stile-49.jpg",
                title: "Гостинная хорошо, но гостинная и кухня лучше",
                description: "Всё ерунда, сказал ещё более великий дизайнер",
                text: "Скучно, но полезно. Более великий дизайнер расставил приоритеты. Логотип — надпись или символ, который будет ассоциироваться с компанией. Он должен быть запоминающимся и хорошо смотреться на разных носителях — от огромного билборда до маленькой визитки. Помимо логотипа у многих компаний есть ещё и полноценная айдентика — набор шрифтов, цветов и паттернов в единой стилистике. Логотип и элементы айдентики нужны, чтобы брендировать всё, что принадлежит компании, — товары, буклеты, торговые точки, униформу сотрудников. В презентации логотипа стоит показать, как он построен, как смотрится в разных цветах и размерах.",
                linkToTheSource: "https://github.com/mightyK1ngRichard"
            },
            {
                id: 5,
                src: "https://www.topdom.ru/uploaded/article/beautiful-interior-apartments/28.jpg",
                title: "Камин - лучшее решение для гостинной",
                description: "\"Пока кто-то спорит, я показываю уровень\" - сказал Гуру дизайны",
                text: "ИИИИИИИУУУУ, сказал легенда и начал поучительную речь, уровня бог. Возможно, вы хотите специализироваться в более узких областях дизайна. Например, заниматься упаковкой, оформлением презентаций или делать исключительно обложки роликов для YouTube. Если для вас приоритетна эта работа, именно такие проекты нужно делать для портфолио. Главное, показывайте любой дизайн на тех носителях, для которых он сделан, — заказчику это важно.",
                linkToTheSource: "https://github.com/mightyK1ngRichard"
            }
        ]
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

    clickCard(e) {
        const cardId = e.target.dataset.id

        // -- Пытаюсь узнать, какую карточку нажали.
        let current_card;
        for (const el of this.getData()) {
            if (el.id.toString() === cardId) {
                current_card = el
            }
        }
        // -- узнал.

        const productPage = new ProductPage(this.parent, cardId, current_card)
        productPage.render()
    }

    render() {
        this.parent.innerHTML = ''
        this.parent.insertAdjacentHTML('beforeend', this.getHTML())
        const data = this.getData()
        data.forEach((item) => {
            const productCard = new ProductCardComponent(this.pageRoot)
            productCard.render(item, this.clickCard.bind(this))
        })
    }
}