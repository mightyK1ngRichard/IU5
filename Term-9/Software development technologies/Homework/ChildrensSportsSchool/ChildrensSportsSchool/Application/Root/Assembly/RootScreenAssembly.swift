//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
enum RootScreenAssembly {

    static func assemble() -> some View {
        let state = RootScreenViewState()
        let viewModel = RootScreenViewModel(state: state)
        let view = RootScreenView(
            state: state,
            output: viewModel
        )

        return view
    }
}
