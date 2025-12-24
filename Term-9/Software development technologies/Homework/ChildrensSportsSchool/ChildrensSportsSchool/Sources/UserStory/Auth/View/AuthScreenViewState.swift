//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Observation

@MainActor
@Observable
final class AuthScreenViewState {

    var emailInput = String()
    var passwordInput = String()

    var alertIsPresented: Bool = false
    @ObservationIgnored
    private(set) var errorMessage = String()

    var buttonIsDisabled: Bool {
        emailInput.isEmpty || passwordInput.isEmpty
    }
}

extension AuthScreenViewState {

    func showAlert(with message: String?) {
        errorMessage = message ?? String()
        alertIsPresented = true
    }
}
