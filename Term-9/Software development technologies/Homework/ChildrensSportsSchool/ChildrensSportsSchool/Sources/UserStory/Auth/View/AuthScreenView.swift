//
//  Created by Dmitriy Permyakov on 17.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

struct AuthScreenView: View {

    @State
    var state: AuthScreenViewState
    let output: AuthScreenViewModel

    var body: some View {
        VStack(spacing: 25) {
            TextField("Логин", text: $state.emailInput)
                .padding(.horizontal)
                .padding(.vertical, 10)
                .glassEffect()

            SecureField("Пароль", text: $state.passwordInput)
                .textContentType(.password)
                .padding(.horizontal)
                .padding(.vertical, 10)
                .glassEffect()
        }
        .alert(state.errorMessage, isPresented: $state.alertIsPresented) {
            Button("Хорошо") {}
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .padding()
        .background(backgroundColor)
        .overlay(alignment: .bottom) {
            buttonContainer
        }
    }
}

// MARK: - UI Subviews

private extension AuthScreenView {

    var buttonContainer: some View {
        HStack {
            actionButton(title: "Войти", action: output.onTapLogin)
                .buttonStyle(.glass)
            actionButton(title: "Создать", action: output.onTapRegister)
                .buttonStyle(.glassProminent)

        }
        .padding()
    }

    func actionButton(
        title: String,
        action: @escaping () -> Void
    ) -> some View {
        Button {
            action()
        } label: {
            Text(title)
                .font(.headline)
                .frame(maxWidth: .infinity)
                .padding(.vertical, 8)
        }
    }

    var backgroundColor: some View {
        LinearGradient(
            colors: [
                Color(red: 0.38, green: 0.18, blue: 0.65),
                Color(red: 0.76, green: 0.32, blue: 0.76),
                Color(red: 1.00, green: 0.44, blue: 0.60)
            ],
            startPoint: .topLeading,
            endPoint: .bottomTrailing
        )
        .ignoresSafeArea()
    }
}

#Preview {
    AuthScreenAssembly.assemble(output: nil)
}
