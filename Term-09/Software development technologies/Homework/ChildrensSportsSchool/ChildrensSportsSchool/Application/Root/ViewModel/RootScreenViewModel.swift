//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

final class RootScreenViewModel: Sendable {

    private let state: RootScreenViewState

    init(state: RootScreenViewState) {
        self.state = state
    }
}

// MARK: - RootScreenViewOutput

extension RootScreenViewModel {

    func onAppear() {
        withAnimation {
            state.clientZone = .auth
        }
    }
}

// MARK: - AuthScreenOutput

extension RootScreenViewModel: AuthScreenOutput {

    func authScreenDidLogin(user: User) {
        withAnimation {
            state.clientZone = .client(user)
        }
    }
}

// MARK: - ClientZoneOutput

extension RootScreenViewModel: ClientZoneOutput {

    func clientZoneDidLogout() {
        withAnimation {
            state.clientZone = .auth
        }
    }
}
