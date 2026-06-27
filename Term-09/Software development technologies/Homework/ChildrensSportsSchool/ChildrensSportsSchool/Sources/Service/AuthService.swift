//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

protocol AnyAuthService {

    func login(email: String, password: String) throws(AuthError) -> User
    func register(email: String, password: String) throws(AuthError) -> User
}

// MARK: - AuthError

enum AuthError: Error, LocalizedError {

    case userAlreadyExists
    case invalidCredentials
    case emptyFields

    var errorDescription: String? {
        switch self {
        case .userAlreadyExists:
            "Пользователь с таким логином уже существует"
        case .invalidCredentials:
            "Неверный логин или пароль"
        case .emptyFields:
            "Все поля должны быть заполнены"
        }
    }
}

// MARK: - AuthService

struct AuthService {

    let userMapper: AnyUserMapper
}

// MARK: - AnyAuthService

extension AuthService: AnyAuthService {

    func login(email: String, password: String) throws(AuthError) -> User {
        // Валидация
        guard User.isValid(email: email, password: password) else {
            throw .emptyFields
        }

        // Проверка логин пароль
        guard let user = userMapper.getUser(by: email),
              user.passwordMatches(password) else {
            throw .invalidCredentials
        }

        return user
    }

    func register(email: String, password: String) throws(AuthError) -> User {
        guard User.isValid(email: email, password: password) else {
            throw .emptyFields
        }

        guard userMapper.getUser(by: email) == nil else {
            throw .userAlreadyExists
        }

        let user = User(name: email, password: password)
        userMapper.createUser(user: user)

        return user
    }
}
