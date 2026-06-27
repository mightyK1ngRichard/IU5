//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

@MainActor
protocol AuthScreenOutput: AnyObject {

    func authScreenDidLogin(user: User)
}
