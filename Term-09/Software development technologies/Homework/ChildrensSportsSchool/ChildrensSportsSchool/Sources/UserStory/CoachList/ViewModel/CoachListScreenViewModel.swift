//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

final class CoachListScreenViewModel: Sendable {

    private let child: Child
    private let state: CoachListScreenViewState
    private let coachListService: CoachListService
    private weak var output: CoachListScreenOutput?

    init(
        child: Child,
        state: CoachListScreenViewState,
        coachListService: CoachListService,
        output: CoachListScreenOutput
    ) {
        self.child = child
        self.state = state
        self.coachListService = coachListService
        self.output = output
    }
}

// MARK: - CoachListScreenViewOuput

extension CoachListScreenViewModel {

    func onAppear() {
        state.coaches = coachListService.fetchCoaches()
    }

    func onSelectCoach(coach: Coach) {
        // Создаём заявку
        coachListService.addChildInCoach(child: child, to: coach)
        output?.coachListScreenDidClose()
    }
}
