//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

final class DataBase: @unchecked Sendable {

    static let shared: AnyDataBase = DataBase()

    private var memoryUsers = [UserRecord]()
    private var memoryKids = [ChildRecord]()
    private var memoryCoaches = [CoachRecord]()
    private var memoryRequests = [AddRequestRecord]()
    private var memoryGroups = [GroupRecord]()

    private let queue = DispatchQueue(label: "data.base.queue")

    private init() {
        memoryUsers = [
            .init(id: UUID(), name: "Леонель Месси", password: "test", role: "coach"),
            .init(id: UUID(), name: "Криштиано Роналду", password: "test", role: "coach"),
            .init(id: UUID(), name: "Андрей Аршавин", password: "test", role: "coach"),
            .init(id: UUID(), name: "Данила Эксайл", password: "test", role: "coach"),
            .init(id: UUID(), name: "Влад Бумага", password: "test", role: "coach"),
            .init(id: UUID(), name: "Test", password: "test", role: "coach"),
            .init(id: UUID(), name: "Coach", password: "test", role: "coach"),
        ]
        memoryCoaches = memoryUsers.map {
            .init(id: $0.id, salary: 1_000_000)
        }
    }
}

// MARK: - AnyUserDataBase

extension DataBase: AnyUserDataBase {

    func fetchUsers() -> [UserRecord] {
        queue.sync {
            memoryUsers
        }
    }

    func fetchUser(name: String) -> UserRecord? {
        queue.sync {
            memoryUsers.first(where: { $0.name == name })
        }
    }

    func fetchUser(id: UUID) -> UserRecord? {
        queue.sync {
            memoryUsers.first(where: { $0.id == id })
        }
    }

    func createUser(user: UserRecord) {
        queue.async {
            self.memoryUsers.append(user)
        }
    }
}

// MARK: - AnyChildDataBase

extension DataBase: AnyChildDataBase {

    func fetchParentChildren(parentID: UUID) -> [ChildRecord] {
        queue.sync {
            self.memoryKids.filter { $0.parentID == parentID }
        }
    }

    func createChild(child: ChildRecord) {
        queue.async {
            self.memoryKids.append(child)
        }
    }

    func fetchChild(id: UUID) -> ChildRecord? {
        queue.sync {
            memoryKids.first(where: { $0.id == id })
        }
    }

    func updateChild(childRecord: ChildRecord) {
        queue.async {
            guard let index = self.memoryKids.firstIndex(where: { $0.id == childRecord.id }) else {
                return
            }

            self.memoryKids[index] = childRecord
        }
    }
}

// MARK: - AnyCoachDataBase

extension DataBase: AnyCoachDataBase {

    func fetchCoaches() -> [CoachRecord] {
        queue.sync {
            memoryCoaches
        }
    }
}

// MARK: - AnyAddRequestDataBase

extension DataBase: AnyAddRequestDataBase {

    func createRequest(request: AddRequestRecord) {
        queue.async {
            self.memoryRequests.append(request)
        }
    }

    func fetchRequests(coachID: UUID) -> [AddRequestRecord] {
        queue.sync {
            memoryRequests.filter { $0.coachID == coachID }
        }
    }

    func fetchRequest() -> [AddRequestRecord] {
        queue.sync {
            memoryRequests
        }
    }

    func fetchRequest(childID: UUID) -> AddRequestRecord? {
        queue.sync {
            memoryRequests.first { $0.childID == childID }
        }
    }

    func updateRequest(_ newRequest: AddRequestRecord) {
        queue.async {
            guard let index = self.memoryRequests.firstIndex(where: {
                $0.childID == newRequest.childID && $0.coachID == newRequest.coachID
            }) else { return }

            self.memoryRequests[index] = newRequest
        }
    }
}

// MARK: - AnyGroupDataBase

extension DataBase: AnyGroupDataBase {

    func fetchCoachGroups(coachID: UUID) -> [GroupRecord] {
        queue.sync {
            memoryGroups.filter { $0.coachID == coachID }
        }
    }

    func createGroup(group: GroupRecord) {
        queue.async {
            self.memoryGroups.append(group)
        }
    }
}
