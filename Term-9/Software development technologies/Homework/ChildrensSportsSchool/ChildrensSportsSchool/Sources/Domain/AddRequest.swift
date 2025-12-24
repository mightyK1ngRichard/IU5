//
//  Created by Dmitriy Permyakov on 24.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

struct AddRequest {

    let coachID: UUID
    let childID: UUID
    let child: Child?
    let status: RequestStatus
}

// MARK: - RequestStatus

extension AddRequest {

    enum RequestStatus: String {

        case waiting
        case accepted
        case rejected
    }
}
