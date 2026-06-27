class Ajax {
    post(url) {
        const getDataFromServer = async () => {
            try {
                return await fetch(url);
            } catch (e) {
                console.log(e);
            }
        }
        return getDataFromServer()
    }

}

export const ajax = new Ajax();