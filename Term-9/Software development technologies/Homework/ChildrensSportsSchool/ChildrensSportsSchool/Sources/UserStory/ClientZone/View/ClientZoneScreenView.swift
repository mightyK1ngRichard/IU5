//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

struct ClientZoneScreenView<
    ProfileView: View
>: View {

    @State
    var state: ClientZoneScreenViewState
    let profileView: ProfileView
    let output: ClientZoneScreenViewModel

    var body: some View {
        NavigationStack(path: $state.path) {
            profileView
                .navigationDestination(for: ClientZoneRoute.self) { route in
                    switch route {
                    case let .coachList(child):
                        CoachListScreenAssembly.assemble(child: child, output: output)
                    }
                }
        }
    }
}
