#include <cstddef>
#include <iostream>

int main()
{
  constexpr size_t min_len = 2;
  size_t count = 0;
  int prev = 0;
  size_t sign_changes = 0;
  size_t div_rem = 0;
  int number = 0;

  while (std::cin >> number && number != 0) {
    if ((prev < 0 && number > 0) || (prev > 0 && number < 0)) {
      ++sign_changes;
    }
    if (prev != 0 && number % prev == 0) {
      ++div_rem;
    }
    prev = number;
    ++count;
  }

  if (!std::cin) {
    std::cerr << "Unexpected input\n";
    return 1;
  }

  std::cout << sign_changes << "\n";
  if (count < min_len) {
    std::cerr << "Sequence is too short to calculate divisible count\n";
    return 2;
  }
  std::cout << div_rem << "\n";
  return 0;
}
