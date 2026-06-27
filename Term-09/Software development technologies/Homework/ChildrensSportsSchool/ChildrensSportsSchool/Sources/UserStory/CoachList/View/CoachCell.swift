//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import SwiftUI

extension CoachCell {

    struct Subtitle {
        let title: String
        let color: Color
    }
}

struct CoachCell: View {

    let title: String
    let subtitle: Subtitle?
    let buttonTitle: String
    let onSelect: () -> Void

    var body: some View {
        HStack(spacing: 16) {
            Circle()
                .fill(Color.blue.opacity(0.1))
                .frame(width: 60, height: 60)
                .overlay(
                    Text(title.prefix(2))
                        .font(.title3)
                        .fontWeight(.semibold)
                        .foregroundColor(.blue)
                )

            VStack(alignment: .leading, spacing: 4) {
                Text(title)
                    .font(.headline)
                    .foregroundColor(.primary)
                if let subtitle {
                    Text(subtitle.title)
                        .font(.caption)
                        .foregroundColor(subtitle.color)
                }
            }
            .frame(maxWidth: .infinity, alignment: .leading)

            Button {
                onSelect()
            } label: {
                Text(buttonTitle)
            }
            .buttonStyle(.glassProminent)
        }
        .padding(.vertical)
        .padding(.horizontal, 2)
        .background(
            RoundedRectangle(cornerRadius: 16)
                .fill(Color(.systemBackground))
                .shadow(color: .black.opacity(0.05), radius: 5, x: 0, y: 2)
        )
        .padding(.horizontal)
    }
}
