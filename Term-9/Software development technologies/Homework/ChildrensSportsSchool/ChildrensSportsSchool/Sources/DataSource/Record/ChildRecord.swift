//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

/// Ребёнок
struct ChildRecord {

    let id: UUID
    let userID: UUID
    let parentID: UUID
    var groupID: UUID?
}
