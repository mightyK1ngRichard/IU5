//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

struct CoachGroup: Identifiable, Hashable {

    let id: UUID
    let name: String
    let coachID: UUID
    let children: [UUID]
}
