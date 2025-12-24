//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

@MainActor
protocol ProfileScreenOuput: AnyObject {

    func profileScreenDidOpenCoachList(with child: Child)
    func profileScreenDidLogout()
}
