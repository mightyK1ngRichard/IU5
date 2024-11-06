export class ProductComponent {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        let university;
        try {
            university = data.universities[0].name
        } catch {
            university = 'МГТУ им. Н.Э.Баумана'
        }
        const ava = data.photo_400_orig === 'https://vk.com/images/camera_400.png' ? 'https://www.meme-arsenal.com/memes/31d486b8ad6c827bbeeefe92d63ace71.jpg' : data.photo_400_orig
        return (
            `
                <div class="profile-card">
                    <div class="image">
                      <img src="${ava}" alt="" class="profile-pic">
                    </div>
                    <div class="data">
                      <h2>${data.first_name} ${data.last_name}</h2>
                      <span>${data.about === undefined || data.about === '' ? 'Статуса нет, но вы держитесь' : data.about}</span>
                    </div>
                    <div class="row">
                      <div class="info">
                        <h3>Университет</h3>
                        <span>${university}</span>
                      </div>
                      <div class="info">
                        <h3>Followers</h3>
                        <span>${data.followers_count === undefined ? 'Жадина' : data.followers_count}</span>
                      </div>
                      <div class="info">
                        <h3>Posts</h3>
                        <span>12</span>
                      </div>
                    </div>
                    <div class="buttons">
                      <a href="#" class="btn">Message</a>
                      <a href="https://vk.com/${data.screen_name}" class="btn">Follow Me</a>
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