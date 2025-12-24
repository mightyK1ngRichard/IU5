//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

/// Пользователь
struct UserRecord {

    let id: UUID
    let name: String
    let password: String
    let role: String
}

extension UserRecord {

    init(from user: User) {
        self = .init(
            id: user.id,
            name: user.name,
            password: user.password,
            role: user.role.rawValue
        )
    }

    var asUser: User? {
        guard let role = User.UserRole(rawValue: role) else {
            return nil
        }

        return User(
            id: id,
            name: name,
            password: password,
            role: role
        )
    }
}
