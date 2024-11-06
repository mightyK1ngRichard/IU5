export class AddendumCard {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML() {
        return (
            `
            <div id="addendum-page">
                <div style="width: 900px; border: 1px solid #ccc; padding: 20px;">
                  <form>
                    <label for="name">Имя:</label><br>
                    <input type="text" id="name" name="name" required><br>
                    <label for="link">Ссылка:</label><br>
                    <input type="text" id="link" name="link"><br>
                    <label for="note">Заметки:</label><br>
                    <textarea id="note" name="note"></textarea><br>
                    <input type="submit" value="Сохранить">
                  </form>
                </div>
              </div>
			`
        )
    }

    addListeners(data, listener) {
        document
            .getElementById(`type-card-img-${data.type_id}`)
            .addEventListener("click", listener)
    }

    render(data, listener) {
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)

    }
}