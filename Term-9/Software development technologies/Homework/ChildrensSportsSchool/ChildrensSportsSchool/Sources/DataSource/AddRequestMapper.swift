//
//  Created by Dmitriy Permyakov on 18.12.2025.
//  Copyright © 2025 Bmstu. All rights reserved.
//

import Foundation

protocol AnyAddRequestMapper {

    func fetchRequest() -> [AddRequest]
    func fetchCoachRequests(id: UUID) -> [AddRequest]
    func fetchRequest(childID: UUID) -> AddRequest?
    func createRequest(request: AddRequest)
    func updateRequest(_ newRequest: AddRequest)
}

// MARK: - AddRequestMapper

struct AddRequestMapper {

    let db: AnyAddRequestDataBase
}

// MARK: - AnyAddRequestMapper

extension AddRequestMapper: AnyAddRequestMapper {

    func fetchRequest() -> [AddRequest] {
        db.fetchRequest()
            .compactMap {
                guard let status = AddRequest.RequestStatus(rawValue: $0.status) else {
                    return nil
                }

                return AddRequest(
                    coachID: $0.coachID,
                    childID: $0.childID,
                    child: nil,
                    status: status
                )
            }
    }

    func createRequest(request: AddRequest) {
        let requestRecord = AddRequestRecord(
            coachID: request.coachID,
            childID: request.childID,
            status: request.status.rawValue
        )
        db.createRequest(request: requestRecord)
    }

    func fetchCoachRequests(id: UUID) -> [AddRequest] {
        db.fetchRequests(coachID: id)
            .compactMap {
                guard let status = AddRequest.RequestStatus(rawValue: $0.status) else {
                    return nil
                }

                return AddRequest(
                    coachID: $0.coachID,
                    childID: $0.childID,
                    child: nil,
                    status: status
                )
            }
    }

    func fetchRequest(childID: UUID) -> AddRequest? {
        guard let request = db.fetchRequest(childID: childID) else {
            return nil
        }

        return AddRequest(
            coachID: request.coachID,
            childID: request.childID,
            child: nil,
            status: .init(rawValue: request.status)!
        )
    }

    func updateRequest(_ newRequest: AddRequest) {
        db.updateRequest(
            AddRequestRecord(
                coachID: newRequest.coachID,
                childID: newRequest.childID,
                status: newRequest.status.rawValue
            )
        )
    }
}
