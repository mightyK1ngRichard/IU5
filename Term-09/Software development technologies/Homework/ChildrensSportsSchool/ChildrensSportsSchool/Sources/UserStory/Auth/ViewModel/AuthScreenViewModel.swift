//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

final class AuthScreenViewModel: Sendable {

    private let state: AuthScreenViewState
    private let authService: AuthService

    @MainActor
    private weak var output: AuthScreenOutput?

    init(
        state: AuthScreenViewState,
        authService: AuthService,
        output: AuthScreenOutput?
    ) {
        self.state = state
        self.authService = authService
        self.output = output
    }
}

// MARK: - AuthScreenViewOutput

extension AuthScreenViewModel {

    func onTapLogin() {
        do {
            let user = try authService.login(email: state.emailInput, password: state.passwordInput)
            output?.authScreenDidLogin(user: user)
        } catch {
            state.showAlert(with: error.errorDescription)
        }
    }

    func onTapRegister() {
        do {
            let user = try authService.register(email: state.emailInput, password: state.passwordInput)
            output?.authScreenDidLogin(user: user)
        } catch {
            state.showAlert(with: error.errorDescription)
        }
    }
}
