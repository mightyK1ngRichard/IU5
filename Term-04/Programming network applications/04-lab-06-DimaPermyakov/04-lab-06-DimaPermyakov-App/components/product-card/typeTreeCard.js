export class ProductCardTypeTree {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
				<div class="type-card">
                    <div class="photo-container">
                        <img id="type-card-img-${data.type_id}" class="photo-of-type-tree" data-id=${data.type_id} src="${data.photo}" alt="машина">
                        <button id="delete-btn-${data.type_id}" class="delete-type" data-id=${data.type_id}></button>
                    </div>
                    <h1 class="type-tree-title">${data.name_type}</h1>
                    <div class="type-tree-body">
                        <p><b>Удобрение: </b>${data.fertilizer_name == null ? "Не задано" : data.fertilizer_name}</p>
                        <p><b>Участок: </b>${data.plot_name == null ? "Не задан" : data.plot_name}</p>
                        <p><b>Кол-во деревьев: </b> ${data.count_trees} шт.</p>
                        <h6><b>Описание: </b></h6>
                        <p>${data.notes == null ? "Описание не добавлено :(" : data.notes}</p>
                    </div>
                </div>
			`
        )
    }

    addListeners(data, listener) {
        document
            .getElementById(`type-card-img-${data.type_id}`)
            .addEventListener("click", listener)

        document
            .getElementById(`delete-btn-${data.type_id}`)
            .addEventListener("click", listener);
    }

    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)

    }
}