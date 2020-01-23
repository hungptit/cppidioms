#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> generate1(const int M, const int N) {
    std::vector<int> results(M * N, 0);
    int idx = 0;
    std::generate(results.begin(), results.end(), [&idx, N]() -> int { return (idx++) / N; });
    return results;
}
std::vector<int> generate2(const int M, const int N) {
    const int len = M * N;
    std::vector<int> results(len, 0);
    for (int idx = 0; idx < results.size(); ++idx) {
        results[idx] = idx / N;
    }
    return results;
}

int main() {
    auto results = generate1(5, 6);
    for (auto idx : results) std::cout << idx;
    std::cout << "\n";
}
