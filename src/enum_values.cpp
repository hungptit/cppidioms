#include <iostream>
#include <string>

enum QueryAttributes : uint32_t {
  NormalQuery = 0,
  RelativeToNow = 1,  //< The query is relative to the current date/time.
  Random = 2,         //< Query involves random numbers.
  UserSpecific =
      4,  //< Query has user references (only defined for abstract queries).
  ContainsTempTable =
      8,  //< Query contains temp tables (only defined for native queries).
};

int main() {
  QueryAttributes attr1 = QueryAttributes::NormalQuery;
  std::cout << "QueryAttributes::NormalQuery: " << attr1 << "\n";

  auto attr2 = attr1 | QueryAttributes::RelativeToNow;

  std::cout << "attr2: " << attr2 << "\n";

  auto attr3 = attr2 | QueryAttributes::Random;
  std::cout << "attr3: " << static_cast<QueryAttributes>(attr3) << "\n";

  return EXIT_SUCCESS;
}
