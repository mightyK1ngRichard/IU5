export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
				<div class="card" style="width: 300px; height: 400px; margin: 20px"> 
					<img class="card-img-top" src="${data.photo_400_orig}" style="object-fit: cover; height: 300px" alt="машина"> 
						<div class="card-body" style="height: 100px"> 
							<h5 class="card-title">${data.first_name} ${data.last_name}</h5> 
							<button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Открыть профиль</button> 
						</div> 
				</div>
			`
        )
    }

    addListeners(data, listener) {
        document
            .getElementById(`click-card-${data.id}`)
            .addEventListener("click", listener)
    }

    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }
}