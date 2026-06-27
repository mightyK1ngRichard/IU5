//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

@MainActor
@Observable
final class ProfileScreenViewState {

    var showChildFieldsInput = false
    var showGroupNameInput = false
    var showSelectGroupForChild = false
    var showAlert = false

    var selectedChild: (name: String, id: UUID)?
    var childNameInput = String()
    var groupNameInput = String()
    var selectedGroup: CoachGroup?

    var headerInfo: HeaderInfo
    var roleKind: RoleKind
    var children: [ChildCellModel] = []
    private(set) var groups: [CoachGroup] = []

    init(user: User) {
        headerInfo = .init(title: user.name)
        roleKind = {
            switch user.role {
            case .child:
                .child
            case .parent:
                .parent
            case .coach:
                .coach
            }
        }()
    }
}

// MARK: - Helpers

extension ProfileScreenViewState {

    func updateGroups(groups: [CoachGroup]) {
        if !groups.isEmpty {
            selectedGroup = groups[0]
        }
        
        self.groups = groups
    }

    struct HeaderInfo {

        let title: String

        static var clear: HeaderInfo { .init(title: String()) }
    }

    enum RoleKind: String {

        case parent = "Родитель"
        case child = "Ребёнок"
        case coach = "Тренер"
    }
}

// MARK: - ChildCellModel

extension ProfileScreenViewState {

    struct ChildCellModel: Identifiable {

        let id: UUID
        let name: String
        var groupID: UUID?
        var status: CellStatus
    }
}

extension ProfileScreenViewState.ChildCellModel {

    enum CellStatus {

        case created
        case waiting
        case accepted
        case rejected
    }

    var title: String {
        switch status {
        case .waiting:
            "Ожидает обработку тренера"
        case .accepted:
            "Принят в группу: \(groupID?.uuidString.suffix(4), default: "None")"
        case .rejected:
            "Отказано"
        case .created:
            "Создан"
        }
    }
}

extension ProfileScreenViewState.ChildCellModel.CellStatus {

    init(from status: AddRequest.RequestStatus?) {
        switch status {
        case .waiting:
            self = .waiting
        case .accepted:
            self = .accepted
        case .rejected:
            self = .rejected
        case .none:
            self = .created
        }
    }

    var textColor: Color {
        switch self {
        case .waiting:
            .orange
        case .accepted:
            .green
        case .rejected:
            .red
        case .created:
            .clear
        }
    }
}
