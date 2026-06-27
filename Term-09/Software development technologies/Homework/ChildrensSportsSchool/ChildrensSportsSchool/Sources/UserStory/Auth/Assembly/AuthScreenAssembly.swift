//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
enum AuthScreenAssembly {

    static func assemble(output: AuthScreenOutput?) -> some View {
        let state = AuthScreenViewState()
        let mapper = UserMapper(db: DataBase.shared)
        let service = AuthService(userMapper: mapper)
        let viewModel = AuthScreenViewModel(
            state: state,
            authService: service,
            output: output
        )
        let view = AuthScreenView(state: state, output: viewModel)

        return view
    }
}
