#include <iostream>
#include <cstddef>

int main()
{
  const size_t min_len = 2;
  size_t count = 0;
  int prev = 0;
  size_t cng = 0;
  size_t div_rem = 0;
  while (true) {
    int n = 0;
    std::cin >> n;
    if (std::cin.fail()) {
      std::cerr << "Число не распознано\n";
      return 1;
    }
    if (n == 0) {
      break;
    }
    if (count == 0) {
      prev = n;
      count++;
      continue;
    }
    if ((prev < 0 && n > 0) || (prev > 0 && n < 0)) {
      cng++;
    }
    if (n % prev == 0) {
      div_rem++;
    }
    prev = n;
    count++;
  }
  std::cout << cng << "\n";

  if (count < min_len) {
    std::cerr << "Недостаточно чисел, чтобы рассчитать характеристику\n";
    return 2;
  }
  std::cout << div_rem << "\n";
  return 0;
}
