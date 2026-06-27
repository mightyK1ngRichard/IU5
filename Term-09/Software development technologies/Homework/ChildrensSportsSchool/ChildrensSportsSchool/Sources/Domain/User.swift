//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

struct User: Hashable {

    let id: UUID
    let name: String
    let password: String
    let role: UserRole
}

// MARK: - UserRole

extension User {

    enum UserRole: String {

        case child
        case parent
        case coach
    }
}

// MARK: - Business Logic

extension User {

    static func isValid(email: String, password: String) -> Bool {
        !email.isEmpty && !password.isEmpty
    }

    func passwordMatches(_ password: String) -> Bool {
        self.password == password
    }

    init(name: String, password: String) {
        self = .init(id: UUID(), name: name, password: password, role: .parent)
    }
}
