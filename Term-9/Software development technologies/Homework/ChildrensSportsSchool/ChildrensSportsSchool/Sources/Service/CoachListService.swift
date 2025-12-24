//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

protocol AnyCoachListService {

    func fetchCoaches() -> [Coach]
    func addChildInCoach(child: Child, to coach: Coach)
}

// MARK: - CoachListService

struct CoachListService {

    let coachMapper: AnyCoachMapper
    let addRequestMapper: AnyAddRequestMapper
    let userMapper: AnyUserMapper
}

// MARK: - AnyCoachListService

extension CoachListService: AnyCoachListService {

    func fetchCoaches() -> [Coach] {
        var coaches = coachMapper.fetchCoaches()
        coaches.enumerated().forEach { (index, coach) in
            guard let userData = userMapper.fetchUserInfo(by: coach.id) else {
                return
            }

            coaches[index].baseInfo = userData
        }

        return coaches
    }

    func addChildInCoach(child: Child, to coach: Coach) {
        // Создаём заявку
        addRequestMapper.createRequest(request: AddRequest(
            coachID: coach.id,
            childID: child.id,
            child: nil,
            status: .waiting
        ))
    }
}
