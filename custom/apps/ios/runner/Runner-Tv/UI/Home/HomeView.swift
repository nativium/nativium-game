
import Foundation
import SwiftUI

struct HomeView: View {
    @ObservedObject private(set) var viewModel = HomeViewModel()

    var body: some View {
        View {}
            .onAppear {
                self.viewModel.loadData()
            }
    }
}
