//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
enum ClientZoneScreenAssembly {

    static func assemble(user: User, output: ClientZoneOutput) -> some View {
        let state = ClientZoneScreenViewState()
        let viewModel = ClientZoneScreenViewModel(state: state, output: output)
        let profileView = ProfileScreenAssembly.assemble(user: user, output: viewModel)

        let view = ClientZoneScreenView(
            state: state,
            profileView: profileView,
            output: viewModel
        )

        return view
    }
}
