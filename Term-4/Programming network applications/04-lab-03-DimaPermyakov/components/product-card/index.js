export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
	            <div class="card" style="width: 300px;">
	                <img class="card-img-top" src="${data.src}" alt="картинка" height="200px">
	                <div class="card-body">
	                    <h5 class="card-title">${data.title}</h5>
	                    <p class="card-text">${data.description}</p>
	                    <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Прочитать</button>
	                </div>
	            </div>
	        `
        )
    }

    addListeners(data, listener) {
        document.getElementById(`click-card-${data.id}`).addEventListener("click", listener)
    }

    render(data, listener) {
        this.parent.insertAdjacentHTML('beforeend', this.getHTML(data))
        this.addListeners(data, listener)
    }
}
