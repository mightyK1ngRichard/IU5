//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
enum ProfileScreenAssembly {

    static func assemble(user: User, output: ProfileScreenOuput) -> some View {
        let state = ProfileScreenViewState(user: user)
        let db = DataBase.shared
        let service = ProfileService(
            userMapper: UserMapper(db: db),
            childMapper: ChildMapper(db: db),
            requestMapper: AddRequestMapper(db: db),
            groupMapper: GroupMapper(db: db)
        )
        let viewModel = ProfileScreenViewModel(
            userID: user.id,
            profileService: service,
            state: state,
            output: output
        )
        let view = ProfileScreenView(state: state, output: viewModel)

        return view
    }
}
