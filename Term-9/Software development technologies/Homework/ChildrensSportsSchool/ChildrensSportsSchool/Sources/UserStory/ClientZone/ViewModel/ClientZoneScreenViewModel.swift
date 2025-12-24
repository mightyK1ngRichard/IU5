//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

final class ClientZoneScreenViewModel {

    private let state: ClientZoneScreenViewState
    private weak var output: ClientZoneOutput?

    init(
        state: ClientZoneScreenViewState,
        output: ClientZoneOutput
    ) {
        self.state = state
        self.output = output
    }
}

// MARK: - ProfileScreenOuput

extension ClientZoneScreenViewModel: ProfileScreenOuput {

    func profileScreenDidOpenCoachList(with child: Child) {
        state.path.append(ClientZoneRoute.coachList(child: child))
    }

    func profileScreenDidLogout() {
        output?.clientZoneDidLogout()
    }
}

// MARK: - CoachListScreenOutput

extension ClientZoneScreenViewModel: CoachListScreenOutput {

    func coachListScreenDidClose() {
        state.path.removeLast()
    }
}
