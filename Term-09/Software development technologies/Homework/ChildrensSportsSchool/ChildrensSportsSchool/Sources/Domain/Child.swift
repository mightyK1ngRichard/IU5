//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

struct Child: Identifiable, Hashable {

    let id: UUID
    let userID: UUID
    var baseInfo: User?
    let parentID: UUID
    let groupID: UUID?
    var status: AddRequest.RequestStatus?
}
