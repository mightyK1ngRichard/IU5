//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

/// Заявка на добавление ребёнка к тренеру
struct AddRequestRecord {

    let coachID: UUID
    let childID: UUID
    let status: String
}
