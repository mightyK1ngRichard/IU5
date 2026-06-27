//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Observation

@MainActor
@Observable
final class RootScreenViewState {

    var clientZone = ClientZone.launch
}

extension RootScreenViewState {

    enum ClientZone {

        case auth
        case launch
        case client(User)
    }
}
