//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Observation

@MainActor
@Observable
final class CoachListScreenViewState {

    var coaches: [Coach] = []

    @ObservationIgnored
    var childName: String

    init(childName: String) {
        self.childName = childName
    }
}
