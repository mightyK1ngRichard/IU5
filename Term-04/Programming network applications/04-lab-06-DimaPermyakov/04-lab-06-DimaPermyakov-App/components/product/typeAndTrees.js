
export class typeAndTrees {
    constructor(parent) {
        this.parent = parent
    }


    getHTML(data) {
        return (
            `
                <div class="type-card">
                  <img id="type-card-img-${data.type_id}" class="photo-of-type-tree-alone" data-id=${data.type_id} src="${data.photo}" alt="машина">
                    <h1 class="type-tree-title">${data.name_type}</h1>
                    <div class="type-tree-body">
                        <p><b>Удобрение: </b>${data.fertilizer_name}</p>
                        <p><b>Участок: </b>${data.plot_name == null ? "Не задан" : data.plot_name}</p>
                        <p><b>Кол-во деревьев: </b> ${data.count_trees} шт.</p>
                        <b><b>Описание: </b></p>
                        <p>${data.notes}</p>
                    </div>
                </div>
            `
        )
    }

    render(data) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
    }
}