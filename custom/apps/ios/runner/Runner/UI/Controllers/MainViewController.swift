import Foundation
import UIKit

class MainViewController: UIViewController {
    private var initialized = false

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)

        initialize()
    }

    func initialize() {
        if initialized {
            return
        }

        initialized = true

        guard let core = NTVGameApplicationCore.shared() else { return }

        let screenSize: CGRect = UIScreen.main.bounds

        core.initialize(Int32(screenSize.width), height: Int32(screenSize.height), mode: 1)
    }
}
