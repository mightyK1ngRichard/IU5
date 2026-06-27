//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

final class ProfileScreenViewModel {

    private let userID: UUID
    private let profileService: ProfileService
    private let state: ProfileScreenViewState
    private weak var output: ProfileScreenOuput?

    private var saveChildren: [Child] = []

    init(
        userID: UUID,
        profileService: ProfileService,
        state: ProfileScreenViewState,
        output: ProfileScreenOuput
    ) {
        self.userID = userID
        self.profileService = profileService
        self.state = state
        self.output = output
    }
}

// MARK: - ProfileScreenViewOutput

extension ProfileScreenViewModel {

    func onAppear() {
        switch state.roleKind {
        case .parent:
            do {
                let parent = try profileService.fetchParentInfo(userID: userID)
                saveChildren = parent.children
                state.children = parent.children.map {
                    .init(
                        id: $0.id,
                        name: $0.baseInfo?.name ?? "Ошибка",
                        groupID: $0.groupID,
                        status: .init(from: $0.status)
                    )
                }
            } catch {
                print("[DEBUG]: \(error)")
            }
        case .child:
            break
        case .coach:
            let requests = profileService.fetchRequests(coachID: userID)
            state.children = requests.map {
                .init(
                    id: $0.childID,
                    name: $0.child?.baseInfo?.name ?? "Unknown child",
                    groupID: $0.child?.groupID,
                    status: .init(from: $0.status)
                )
            }

            state.updateGroups(groups: profileService.fetchCoachGroups(coachID: userID))
        }
    }

    func onTapGroupCell(group: CoachGroup) {
    }

    func onTapAddChildInGroup() {
        guard let childID = state.selectedChild?.id,
              let group = state.selectedGroup
        else { return }

        profileService.addChildInGroup(childID: childID, groupID: group.id)

        if let index = state.children.firstIndex(where: { $0.id == childID }) {
            state.children[index].status = .accepted
            state.children[index].groupID = group.id
        }
        state.showSelectGroupForChild = false
    }

    func onTapCreateGroup() {
        guard !state.groupNameInput.isEmpty else {
            return
        }

        let group = profileService.createGroup(name: state.groupNameInput, coachID: userID)
        state.updateGroups(groups: state.groups + [group])
        state.showGroupNameInput = false
        state.groupNameInput.removeAll(keepingCapacity: true)
    }

    func onTapAddChild() {
        guard !state.childNameInput.isEmpty else {
            return
        }

        // Добавили в бд
        do {
            let childName = state.childNameInput
            let child = try profileService.addChild(for: userID, childName: childName)
            saveChildren.append(child)
            state.children.append(
                .init(
                    id: child.id,
                    name: childName,
                    groupID: child.groupID,
                    status: .created
                )
            )
        } catch {
            print("[DEBUG]: \(error)")
        }

        // Обновили UI
        state.childNameInput.removeAll(keepingCapacity: true)
        state.showChildFieldsInput = false
    }

    func onTapLogout() {
        output?.profileScreenDidLogout()
    }

    func onTapChild(_ childID: UUID) {
        guard let child = saveChildren.first(where: { $0.id == childID }) else {
            return
        }
        output?.profileScreenDidOpenCoachList(with: child)
    }
}
