import {accessToken, version} from "./consts.js";

class Urls {
    constructor() {
        // lcp --proxyUrl https://api.vk.com
        this.url = 'http://localhost:8010/proxy/method'
        this.commonInfo = `access_token=${accessToken}&v=${version}`
    }

    getUserInfo(userId) {
        return `${this.url}/users.get?user_ids=${userId}&fields=photo_400_orig,screen_name,universities,about,sex,followers_count,friend_status,contacts&${this.commonInfo}`
    }

    getSortedInfoUp(groupId) {
        return `${this.url}/groups.getMembers?group_id=${groupId}&sort=id_asc&fields=photo_400_orig&${this.commonInfo}`
    }

    getSortedInfoDown(groupId) {
        return `${this.url}/groups.getMembers?group_id=${groupId}&sort=id_desc&fields=photo_400_orig&${this.commonInfo}`

    }

    getGroupMembers(groupId) {
        return `${this.url}/groups.getMembers?group_id=${groupId}&fields=photo_400_orig&${this.commonInfo}`
    }
}

export const urls = new Urls()