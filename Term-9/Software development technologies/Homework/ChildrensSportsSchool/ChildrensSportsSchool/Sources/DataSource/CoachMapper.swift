//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

// MARK: - AnyCoachMapper

protocol AnyCoachMapper {

    func fetchCoaches() -> [Coach]
}

// MARK: - CoachMapper

struct CoachMapper {

    let db: AnyCoachDataBase
}

// MARK: - AnyCoachMapper

extension CoachMapper: AnyCoachMapper {

    func fetchCoaches() -> [Coach] {
        db.fetchCoaches().map {
            Coach(id: $0.id, baseInfo: nil)
        }
    }
}
