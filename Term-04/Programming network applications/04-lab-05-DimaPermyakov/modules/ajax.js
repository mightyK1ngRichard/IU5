class Ajax {
    // MARK: - Lab04
    // post(url, callback) {
    //     let xhr = new XMLHttpRequest()
    //     xhr.open('POST', url)
    //     xhr.send()
    //     xhr.onreadystatechange = () => {
    //         if (xhr.readyState === 4) {
    //             const data = JSON.parse(xhr.response)
    //             callback(data)
    //         }
    //     }
    // }

    // MARK: - Lab05
    post(url) {
        const getDataFromServer = async () => {
            try {
                //Делаем GET запрос на указанный урл
                // возвращаем результат в случае успеха
                return await fetch(url);
            } catch (e) {
                console.log(e);
            }
        }
        return getDataFromServer()
    }

}

export const ajax = new Ajax();