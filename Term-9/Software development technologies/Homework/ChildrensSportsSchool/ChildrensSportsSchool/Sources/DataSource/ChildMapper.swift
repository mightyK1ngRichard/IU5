//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

// MARK: - AnyChildMapper

protocol AnyChildMapper {

    func fetchParentKids(parentID: UUID) -> [Child]
    func fetchChild(id: UUID) -> Child?
    func createChild(child: Child)
    func updateChild(_ child: Child)
}

// MARK: - ChildMapper

struct ChildMapper {

    let db: AnyChildDataBase
}

// MARK: - AnyChildMapper

extension ChildMapper: AnyChildMapper {

    func fetchParentKids(parentID: UUID) -> [Child] {
        let childrens = db.fetchParentChildren(parentID: parentID)

        return childrens.map {
            Child(
                id: $0.id,
                userID: $0.userID,
                baseInfo: nil,
                parentID: $0.parentID,
                groupID: $0.groupID
            )
        }
    }

    func fetchChild(id: UUID) -> Child? {
        guard let childRecord = db.fetchChild(id: id) else {
            return nil
        }

        return Child(
            id: childRecord.id,
            userID: childRecord.userID,
            baseInfo: nil,
            parentID: childRecord.parentID,
            groupID: childRecord.groupID
        )
    }

    func updateChild(_ child: Child) {
        let childRecord = ChildRecord(
            id: child.id,
            userID: child.userID,
            parentID: child.parentID,
            groupID: child.groupID
        )
        db.updateChild(childRecord: childRecord)
    }

    func createChild(child: Child) {
        let childRecord = ChildRecord(
            id: child.id,
            userID: child.userID,
            parentID: child.parentID,
            groupID: child.groupID
        )

        db.createChild(child: childRecord)
    }
}
