//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

struct ProfileScreenView: View {

    @State
    var state: ProfileScreenViewState
    let output: ProfileScreenViewModel

    var body: some View {
        roleContainer
            .toolbar {
                ToolbarItem {
                    Button {
                        output.onTapLogout()
                    } label: {
                        Image(systemName: "rectangle.portrait.and.arrow.right")
                    }
                }
            }
            .safeAreaInset(edge: .top, spacing: .zero) {
                headerView
            }
            .onAppear(perform: output.onAppear)
            .sheet(isPresented: $state.showChildFieldsInput) {
                sheetView
                    .presentationDetents([.height(200)])
            }
            .sheet(isPresented: $state.showGroupNameInput) {
                createGroupSheet
                    .presentationDetents([.height(200)])
            }
            .sheet(isPresented: $state.showSelectGroupForChild) {
                addChildInGroupSheet
                    .presentationDetents([.height(300)])
            }
            .alert("У вас нет группы", isPresented: $state.showAlert) {
                Button("Хорошо, создам") {}
            }
    }
}

// MARK: - UI Subviews

private extension ProfileScreenView {

    var headerView: some View {
        VStack(spacing: 16) {
            Circle()
                .fill(.gray.opacity(0.4))
                .frame(width: 120, height: 120)
                .overlay {
                    Image(systemName: "person")
                        .renderingMode(.template)
                        .resizable()
                        .scaledToFit()
                        .frame(width: 60)
                }

            VStack(spacing: 4) {
                Text(state.headerInfo.title)
                    .font(.title)
                    .bold()

                Text("Роль: \(state.roleKind.rawValue)")
                    .font(.callout)
            }
        }
    }

    var sheetView: some View {
        VStack {
            TextField("Имя ребёнка", text: $state.childNameInput)
                .padding(.vertical, 10)
                .padding(.horizontal)
                .glassEffect()

            Spacer()
            Button {
                output.onTapAddChild()
            } label: {
                Text("Добавить")
            }
            .buttonStyle(.glassProminent)
        }
        .padding()
    }

    var addChildInGroupSheet: some View {
        VStack(alignment: .leading) {
            VStack(alignment: .leading) {
                HStack(spacing: 6) {
                    Text("Добавить ребёнка")
                    Text("\(state.selectedChild?.name, default: "None")")
                        .bold()
                }
                Text("В группу:")
            }
            .font(.title2)

            Picker(selection: $state.selectedGroup) {
                ForEach(state.groups) {
                    Text($0.name)
                        .tag($0)
                }
            } label: {
                Text("Label")
            }
            .pickerStyle(.wheel)

            Spacer()
            Button {
                output.onTapAddChildInGroup()
            } label: {
                Text("Добавить")
            }
            .buttonStyle(.glassProminent)
        }
        .padding()
    }

    var createGroupSheet: some View {
        VStack {
            VStack(alignment: .leading, spacing: 12) {
                Text("Создание группы")
                    .font(.title3)
                    .bold()
                TextField("Название группы", text: $state.groupNameInput)
                    .padding(.vertical, 10)
                    .padding(.horizontal)
                    .glassEffect()
            }
            
            Spacer()
            Button {
                output.onTapCreateGroup()
            } label: {
                Text("Создать")
            }
            .buttonStyle(.glassProminent)
        }
        .padding()
    }

    @ViewBuilder
    var roleContainer: some View {
        switch state.roleKind {
        case .parent:
            parentContainer
        case .child:
            Text("Просто ребёнок")
        case .coach:
            coachContainer
        }
    }

    var parentContainer: some View {
        List {
            Button("Добавить своего ребёнка") {
                state.showChildFieldsInput = true
            }

            ForEach(state.children) { child in
                Button {
                    output.onTapChild(child.id)
                } label: {
                    HStack {
                        Text(child.name)
                        Spacer()
                        Text(child.title)
                            .foregroundStyle(child.status.textColor)
                            .font(.caption2)
                    }
                }
                .disabled(
                    child.status == .accepted || child.status == .waiting
                )
            }
        }
        .background(Color.red)
    }

    var coachContainer: some View {
        ScrollView {
            Button {
                state.showGroupNameInput = true
            } label: {
                Text("Создать группу")
            }
            .buttonStyle(.bordered)
            .padding()

            if !state.groups.isEmpty {
                groupSection
            }

            if !state.children.isEmpty {
                requestsSection
            }
        }
    }

    var requestsSection: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("Эти дети хотят тренироваться с вами:")
                .font(.title2)
                .bold()
                .padding()

            LazyVStack {
                ForEach(state.children) { child in
                    CoachCell(
                        title: "\(child.name)",
                        subtitle: .init(
                            title: child.title,
                            color: child.status.textColor
                        ),
                        buttonTitle: "Записать"
                    ) {
                        guard !state.groups.isEmpty else {
                            state.showAlert = true
                            return
                        }
                        state.selectedChild = (child.name, child.id)
                        state.showSelectGroupForChild = true
                    }
                }
            }
        }
    }

    var groupSection: some View {
        VStack(alignment: .leading, spacing: 8) {
            Text("Ваши группы:")
                .font(.title2)
                .bold()
                .padding(.horizontal)

            ScrollView(.horizontal) {
                HStack(spacing: 12) {
                    ForEach(state.groups) { group in
                        groupCell(for: group)
                            .onTapGesture {
                                output.onTapGroupCell(group: group)
                            }
                    }
                }
                .padding(.horizontal)
            }
            .scrollIndicators(.hidden)
        }
        .frame(maxWidth: .infinity, alignment: .leading)
    }

    func groupCell(for group: CoachGroup) -> some View {
        Text(group.name)
            .font(.callout)
            .fontWeight(.semibold)
            .foregroundColor(.white)
            .padding(.horizontal, 20)
            .padding(.vertical, 12)
            .background(
                LinearGradient(
                    colors: [.blue, .purple],
                    startPoint: .leading,
                    endPoint: .trailing
                ),
                in: .capsule
            )
    }
}
