//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
enum CoachListScreenAssembly {

    static func assemble(child: Child, output: CoachListScreenOutput) -> some View {
        let state = CoachListScreenViewState(childName: child.baseInfo?.name ?? "Ошибка")
        let service = CoachListService(
            coachMapper: CoachMapper(db: DataBase.shared),
            addRequestMapper: AddRequestMapper(db: DataBase.shared),
            userMapper: UserMapper(db: DataBase.shared)
        )
        let viewModel = CoachListScreenViewModel(
            child: child,
            state: state,
            coachListService: service,
            output: output
        )
        let view = CoachListScreenView(state: state, output: viewModel)

        return view
    }
}
