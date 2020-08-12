#include <iostream>
#include <limits>
#include <vector>

// Only support greater comparison
std::vector<double> compute(const std::vector<double>& input,
                            const double threshold,
                            const double initialThreshold) {
  double currentThreshold = initialThreshold;
  std::vector<double> results;
  for (auto it = input.cbegin(); it != input.cend(); ++it) {
    if (*it > threshold) {
      results.push_back(*it);
    } else {
      if (*it > currentThreshold) {
        currentThreshold = *it;
      }
    }
  }
  if (results.empty()) return results;
  if (currentThreshold != initialThreshold) results.push_back(currentThreshold);
  return results;
}

// Support custom comparison
template <typename Comparator>
std::vector<double> compute2(const std::vector<double>& input,
                             const double threshold,
                             const double initialThreshold) {
  Comparator comp;
  double currentThreshold = initialThreshold;
  std::vector<double> results;
  for (auto it = input.cbegin(); it != input.cend(); ++it) {
    if (comp(*it, threshold)) {
      results.push_back(*it);
    } else {
      if (comp(*it, currentThreshold)) {
        currentThreshold = *it;
      }
    }
  }
  if (results.empty()) return results;
  if (!results.empty() && currentThreshold != initialThreshold)
    results.push_back(currentThreshold);
  return results;
}

void print(const std::vector<double>& data, const std::string& msg) {
  std::cout << msg << "[";
  for (auto val : data) {
    std::cout << val << " ";
  }
  std::cout << "]\n";
}

int main() {
  const std::vector<double> input{1, 4, -1, 0, 3, 7};
  print(input, "Input data: ");

  auto res1 = compute(input, 2, std::numeric_limits<double>::min());
  print(res1, "The output of compute: ");

  // std::greater
  print(compute2<std::greater<double>>(input, 2,
                                       std::numeric_limits<double>::min()),
        "The output of compute2 (greater): ");

  // std::less
  print(
      compute2<std::less<double>>(input, 2, std::numeric_limits<double>::max()),
      "The output of compute2 (less): ");
}
