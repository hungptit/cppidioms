#include <sys/types.h>

#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

enum class PredictorType { NONE, NOMINAL, ORDINAL, PERIODIC, MEASURE };
enum class AugmentationType { ON, OFF };
enum class ModelType { LINEAR, RL, GP };

struct PredictorParameters {
  PredictorType type = PredictorType::NONE;
  AugmentationType augmentation = AugmentationType::OFF;
};

std::ostream& operator<<(std::ostream& os, const PredictorType type) {
  if (type == PredictorType::NOMINAL) {
    return os << "\"NOMINAL\"";
  }
  if (type == PredictorType::ORDINAL) {
    return os << "\"ORDIAL\"";
  }
  if (type == PredictorType::MEASURE) {
    return os << "\"MEASURE\"";
  }
  return os << "\"NONE\"";
}

std::ostream& operator<<(std::ostream& os, const AugmentationType type) {
  if (type == AugmentationType::OFF) {
    return os << "\"OFF\"";
  }
  return os << "\"ON\"";
}

std::ostream& operator<<(std::ostream& os, const PredictorParameters param) {
  return os << "{\"type\":" << param.type << ","
            << "\"augmentation\":" << param.augmentation << "}";
}

struct ContingencyTable {
  size_t row = 0;
  size_t col = 0;
  std::vector<std::vector<double>> data = {};
};

struct ModelParameters {
  ModelType type = ModelType::LINEAR;
  AugmentationType augmentation = AugmentationType::OFF;
  std::optional<double> lambda = {};
  std::optional<ContingencyTable> table = {};
};

struct PredictionParameters {
  ModelParameters model_params;
  std::vector<PredictorParameters> pred_params;
};

class ArgumentParser {
 private:
  static constexpr char SINGLE_QUOTE = '\'';
  static constexpr char COMMA = ',';

  // 'model=rl,augmentation=off,lambda=0.5,contingency_table=[[1,2,3,4,5,6],[1,2,3,4,5,6]]'
  // ModelParameters parse_model_parameters() {}

  // Will look like this: 'type=ordered,augmentation=off'
  // PredictorParameters parse_predictor_parameters() {}

 public:
  template <typename Iter>
  PredictionParameters parse(Iter begin, Iter end) {}
};

int main() {
  PredictorParameters pred_param = {};
  std::cout << "pred_param: " << pred_param << "\n";
}
