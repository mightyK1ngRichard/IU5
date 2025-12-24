//
//  Created by Dmitriy Permyakov on 07.12.2025.
//

import SwiftUI

/**
 1. Вход
 1. Добавить ребёнка
 2. Создать группу
 2. Записать ребёнка
 3. Посмотерть тренеров
 */
@main
struct ChildrensSportsSchoolApp: App {
    var body: some Scene {
        WindowGroup {
            RootScreenAssembly.assemble()
        }
    }
}
