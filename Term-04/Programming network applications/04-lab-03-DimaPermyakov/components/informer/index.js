export class Informer {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        return (
            `
            <button 
            style="margin-left: 15px;"
            type="button" 
            class="btn btn-primary popover-dismiss" 
            data-bs-container="body"
            data-bs-toggle="popover" 
            data-bs-placement="left"  
            data-bs-title="Здесь могла быть ваша реклама" 
            data-bs-content="${data.text.substring(0, 120).concat("...")}
            <br><br>
            <a href='${data.linkToTheSource}' id='read-full'>Читать полностью</a>">
            Узнать источник
            </button>
            `
        )
    }

    render(data) {
        // инициализирую popover
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)

        const myPopoverTrigger = document.querySelector('.popover-dismiss')
        new bootstrap.Popover(myPopoverTrigger, {trigger: "focus", html: true})

    }

}
