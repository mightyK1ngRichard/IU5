//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

struct Parent: Identifiable, Hashable {

    let id: UUID
    let name: String
    let children: [Child]
}
