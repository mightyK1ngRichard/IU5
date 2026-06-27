import { Informer} from "../informer/index.js";

export class ProductComponent {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        return (
            `
                <div class="card mb-3" style="height: 380px; width: 1400px">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${data.src}" style="height: 380px" class="img-fluid" alt="картинка">
                        </div>
                        <div class="col-md-8" id="divForInformer">
                            <div class="card-body">
                                <h5 class="card-title">${data.title}</h5>
                                <h6 class="card-description">${data.description}</h6>
                                <p class="card-text">${data.text}</p>
                            </div>
                            
                        
                        </div>
                    </div>
                </div>
            `
        )
    }

    render(data) {
        document.getElementById('strong').innerHTML = ''
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        // инициализирую popover
        // const myPopoverTrigger = document.querySelector('.popover-dismiss')
        // new bootstrap.Popover(myPopoverTrigger, {trigger: "focus", html: true})
        // myPopoverTrigger.addEventListener('shown.bs.popover', () => {
        //     const readFull = document.getElementById('read-full')
        //     readFull.onclick = function() {
        //     }
        // })

        const informerRoot = document.getElementById('divForInformer')
        const informer = new Informer(informerRoot)
        informer.render(data)
    }
}