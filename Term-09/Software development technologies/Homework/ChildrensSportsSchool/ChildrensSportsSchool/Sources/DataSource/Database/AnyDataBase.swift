//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

typealias AnyDataBase = AnyUserDataBase & AnyChildDataBase & AnyAddRequestDataBase & AnyGroupDataBase & AnyCoachDataBase

protocol AnyChildDataBase {

    func fetchParentChildren(parentID: UUID) -> [ChildRecord]
    func createChild(child: ChildRecord)
    func updateChild(childRecord: ChildRecord)
    func fetchChild(id: UUID) -> ChildRecord?
}

protocol AnyUserDataBase {

    func fetchUser(name: String) -> UserRecord?
    func fetchUser(id: UUID) -> UserRecord?
    func createUser(user: UserRecord)
    func fetchUsers() -> [UserRecord]
}

protocol AnyCoachDataBase {

    func fetchCoaches() -> [CoachRecord]
}

protocol AnyAddRequestDataBase {

    func createRequest(request: AddRequestRecord)
    func fetchRequests(coachID: UUID) -> [AddRequestRecord]
    func fetchRequest() -> [AddRequestRecord]
    func fetchRequest(childID: UUID) -> AddRequestRecord?
    func updateRequest(_ newRequest: AddRequestRecord)
}

protocol AnyGroupDataBase {

    func createGroup(group: GroupRecord)
    func fetchCoachGroups(coachID: UUID) -> [GroupRecord]
}
