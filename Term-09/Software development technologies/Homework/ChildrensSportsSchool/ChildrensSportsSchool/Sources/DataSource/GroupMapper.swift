//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

// MARK: - AnyGroupMapper

protocol AnyGroupMapper {

    func createGroup(group: CoachGroup)
    func fetchCoachGroups(coachID: UUID) -> [CoachGroup]
}

// MARK: - GroupMapper

struct GroupMapper {

    let db: AnyGroupDataBase
}

// MARK: - AnyGroupMapper

extension GroupMapper: AnyGroupMapper {

    func createGroup(group: CoachGroup) {
        let newGroup = GroupRecord(
            id: group.id,
            name: group.name,
            coachID: group.coachID
        )
        db.createGroup(group: newGroup)
    }

    func fetchCoachGroups(coachID: UUID) -> [CoachGroup] {
        db.fetchCoachGroups(coachID: coachID).map {
            CoachGroup(
                id: $0.id,
                name: $0.name,
                coachID: $0.coachID,
                children: []
            )
        }
    }
}
