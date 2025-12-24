//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

struct CoachListScreenView: View {

    @State
    var state: CoachListScreenViewState
    let output: CoachListScreenViewModel

    var body: some View {
        ScrollView {
            LazyVStack {
                ForEach(state.coaches) { coach in
                    CoachCell(
                        title: coach.baseInfo?.name ?? "Ошибка",
                        subtitle: nil,
                        buttonTitle: "Записаться"
                    ) {
                        output.onSelectCoach(coach: coach)
                    }
                }
            }
        }
        .navigationTitle("Тренера для \"\(state.childName)\"")
        .navigationBarTitleDisplayMode(.inline)
        .onAppear(perform: output.onAppear)
    }
}
