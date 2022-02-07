import Foundation

class HomeViewModel: NSObject, ObservableObject {
    func loadData() {
        guard let core = NTVGameApplicationCore.shared() else { return }

        let screenSize: CGRect = UIScreen.main.bounds

        core.initialize(Int32(screenSize.width), height: Int32(screenSize.height), mode: 1)
    }
}
