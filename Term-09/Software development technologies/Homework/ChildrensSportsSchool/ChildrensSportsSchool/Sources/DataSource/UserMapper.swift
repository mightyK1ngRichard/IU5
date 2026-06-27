//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

// MARK: - AnyUserMapper

protocol AnyUserMapper {

    func getUser(by name: String) -> User?
    func fetchUserInfo(by id: UUID) -> User?
    func createUser(user: User)
}

// MARK: - UserMapper

struct UserMapper {

    let db: AnyUserDataBase
}

// MARK: - AnyUserMapper

extension UserMapper: AnyUserMapper {

    func getUser(by name: String) -> User? {
        db.fetchUser(name: name)?.asUser
    }

    func fetchUserInfo(by id: UUID) -> User? {
        db.fetchUser(id: id)?.asUser
    }

    func createUser(user: User) {
        db.createUser(user: UserRecord(from: user))
    }
}
