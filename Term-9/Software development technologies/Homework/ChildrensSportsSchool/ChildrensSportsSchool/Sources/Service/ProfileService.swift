//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

protocol AnyProfileService {

    func fetchParentInfo(userID: UUID) throws(ProfileError) -> Parent
    func fetchRequests(coachID: UUID) -> [AddRequest]
    func createGroup(name: String, coachID: UUID) -> CoachGroup
    func fetchCoachGroups(coachID: UUID) -> [CoachGroup]
    func addChild(for parentID: UUID, childName: String) throws(ProfileError) -> Child
    func addChildInGroup(childID: UUID, groupID: UUID)
}

// MARK: - ProfileError

enum ProfileError: Error {

    case parentNotFound
    case nameAlreadyExist
}

// MARK: - ProfileService

struct ProfileService {

    let userMapper: AnyUserMapper
    let childMapper: AnyChildMapper
    let requestMapper: AnyAddRequestMapper
    let groupMapper: AnyGroupMapper
}

// MARK: - AnyProfileService

extension ProfileService: AnyProfileService {

    func fetchParentInfo(userID: UUID) throws(ProfileError) -> Parent {
        // Получаем детей
        let children = childMapper.fetchParentKids(parentID: userID)

        // Получаем заявки
        let requests: [UUID: AddRequest.RequestStatus] = requestMapper
            .fetchRequest()
            .reduce(into: [:]) { partialResult, request in
                partialResult[request.childID] = request.status
        }

        // Получаем полные данные детей
        let fullChildren: [Child] = children.compactMap { child in
            var fullChild = child
            guard let userData = userMapper.fetchUserInfo(by: child.userID) else {
                return nil
            }

            fullChild.baseInfo = userData
            fullChild.status = requests[child.id]

            return fullChild
        }

        // Получаем данные родителя
        guard let parent = userMapper.fetchUserInfo(by: userID) else {
            throw .parentNotFound
        }

        return Parent(
            id: parent.id,
            name: parent.name,
            children: fullChildren
        )
    }

    func fetchRequests(coachID: UUID) -> [AddRequest] {
        requestMapper
            .fetchCoachRequests(id: coachID)
            .compactMap { request in
                guard var child = childMapper.fetchChild(id: request.childID),
                      let userData = userMapper.fetchUserInfo(by: child.userID)
                else { return nil }

                child.baseInfo = userData
                return .init(
                    coachID: request.coachID,
                    childID: child.id,
                    child: child,
                    status: request.status
                )
            }
    }

    func createGroup(name: String, coachID: UUID) -> CoachGroup {
        let group = CoachGroup(
            id: UUID(),
            name: name,
            coachID: coachID,
            children: []
        )
        groupMapper.createGroup(group: group)

        return group
    }

    func fetchCoachGroups(coachID: UUID) -> [CoachGroup] {
        groupMapper.fetchCoachGroups(coachID: coachID)
    }

    func addChild(for parentID: UUID, childName: String) throws(ProfileError) -> Child {
        // Проверка уникальности имени
        guard userMapper.getUser(by: childName) == nil else {
            throw .nameAlreadyExist
        }

        // Создаём нового пользователя с ролью ребёнка
        let newUser = User(
            id: UUID(),
            name: childName,
            password: "base-password",
            role: .child
        )
        userMapper.createUser(user: newUser)

        // Создаём ребёнка
        let child = Child(
            id: UUID(),
            userID: newUser.id,
            baseInfo: newUser,
            parentID: parentID,
            groupID: nil
        )
        childMapper.createChild(child: child)

        return child
    }

    func addChildInGroup(childID: UUID, groupID: UUID) {
        // Получаем все данные ребёнка
        guard let child = childMapper.fetchChild(id: childID) else {
            return
        }

        // Обновляем только статус
        childMapper.updateChild(Child(
            id: child.id,
            userID: child.userID,
            baseInfo: nil,
            parentID: child.parentID,
            groupID: groupID
        ))

        // Обновить статус
        guard let request = requestMapper.fetchRequest(childID: child.id) else {
            return
        }
        requestMapper.updateRequest(AddRequest(
            coachID: request.coachID,
            childID: request.childID,
            child: nil,
            status: .accepted
        ))
    }
}
