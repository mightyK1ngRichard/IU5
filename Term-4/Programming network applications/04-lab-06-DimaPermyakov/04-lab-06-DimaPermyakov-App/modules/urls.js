class Urls {
    constructor() {
        this.url = 'http://localhost:8010'
    }

    getTypeTrees() {
        return `${this.url}/wood/type-tree`
    }

    getTypeById(id) {
        return `${this.url}/wood/type-tree/${id}`
    }

    deleteTypeTree(id) {
        return `http://localhost:8010/wood/type-tree/${id}`
    }

    addTypeTree() {
        return `http://localhost:8010/wood/type-tree`
    }
}

export const urls = new Urls()