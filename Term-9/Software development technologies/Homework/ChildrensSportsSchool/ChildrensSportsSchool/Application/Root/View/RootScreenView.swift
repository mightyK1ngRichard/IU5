//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

struct RootScreenView: View {

    @State
    var state: RootScreenViewState
    let output: RootScreenViewModel

    var body: some View {
        content
            .onAppear(perform: output.onAppear)
    }
}

// MARK: - UI Subviews

private extension RootScreenView {

    @ViewBuilder
    var content: some View {
        switch state.clientZone {
        case .auth:
            AuthScreenAssembly.assemble(output: output)
        case let .client(user):
            ClientZoneScreenAssembly.assemble(user: user, output: output)
        case .launch:
            ProgressView()
        }
    }
}

// MARK: - Preview

#Preview {
    RootScreenAssembly.assemble()
}
