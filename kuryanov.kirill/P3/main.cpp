#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

namespace kuryanov {
  void spiralTopClk(int* m, size_t rows, size_t cols, int sign)
  {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows;
    size_t right = cols;
    int step = 1;
    while (top < bottom && left < right) {
      for (size_t j = left; j < right; ++j) {
        m[top * cols + j] -= sign * step++;
      }
      ++top;
      for (size_t i = top; i < bottom; ++i) {
        m[i * cols + right - 1] -= sign * step++;
      }
      --right;
      if (top < bottom) {
        for (size_t j = right; j > left; --j) {
          m[(bottom - 1) * cols + j - 1] -= sign * step++;
        }
        --bottom;
      }
      if (left < right) {
        for (size_t i = bottom; i > top; --i) {
          m[(i - 1) * cols + left] -= sign * step++;
        }
        ++left;
      }
    }
  }

  void spiralBotCnt(int* m, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t left = 0;
    size_t bottom = rows;
    size_t right = cols;
    int step = 1;
    while (top < bottom && left < right) {
      for (size_t j = left; j < right; ++j) {
        m[(bottom - 1) * cols + j] += step++;
      }
      --bottom;
      for (size_t i = bottom; i > top; --i) {
        m[(i - 1) * cols + right - 1] += step++;
      }
      --right;
      if (top < bottom) {
        for (size_t j = right; j > left; --j) {
          m[top * cols + j - 1] += step++;
        }
        ++top;
      }
      if (left < right) {
        for (size_t i = top; i < bottom; ++i) {
          m[i * cols + left] += step++;
        }
        ++left;
      }
    }
  }

  std::istream& readMatrix(std::istream& in, int* m, size_t count)
  {
    for (size_t i = 0; i < count; ++i) {
      in >> m[i];
    }
    return in;
  }

  std::ostream& printMatrix(std::ostream& out, const int* m, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols;
    for (size_t i = 0; i < rows * cols; ++i) {
      out << ' ' << m[i];
    }
    return out;
  }
}

int main(int argc, char* argv[])
{
  const int argsCount = 4;
  const size_t maxElements = 10000;

  if (argc < argsCount) {
    std::cerr << "Not enough arguments\n";
    return 1;
  }
  if (argc > argsCount) {
    std::cerr << "Too many arguments\n";
    return 1;
  }
  char* end = nullptr;
  const long num = std::strtol(argv[1], std::addressof(end), 10);
  if (end == argv[1] || *end != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  if (num != 1 && num != 2) {
    std::cerr << "First parameter is out of range\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open()) {
    std::cerr << "Cannot open input file\n";
    return 2;
  }
  int raw_rows = 0;
  int raw_cols = 0;
  if (!(input >> raw_rows >> raw_cols) || raw_rows < 0 || raw_cols < 0) {
    std::cerr << "Unexpected input\n";
    return 2;
  }
  const size_t rows = static_cast< size_t >(raw_rows);
  const size_t cols = static_cast< size_t >(raw_cols);

  if (cols != 0 && rows > std::numeric_limits< size_t >::max() / cols) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }
  const size_t count = rows * cols;
  if (num == 1 && count > maxElements) {
    std::cerr << "Matrix is too large\n";
    return 2;
  }

  int stack_array[maxElements] = {};
  int* dynamic_array = nullptr;
  int* data = stack_array;
  if (num == 2) {
    dynamic_array = static_cast< int* >(std::malloc(count * sizeof(int)));
    if (dynamic_array == nullptr && count > 0) {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
    data = dynamic_array;
  }

  if (!kuryanov::readMatrix(input, data, count)) {
    std::cerr << "Unexpected input\n";
    std::free(dynamic_array);
    return 2;
  }
  std::ofstream out(argv[3]);
  if (!out.is_open()) {
    std::cerr << "Cannot open output file\n";
    std::free(dynamic_array);
    return 2;
  }

  kuryanov::spiralTopClk(data, rows, cols, 1);
  kuryanov::printMatrix(out, data, rows, cols) << '\n';
  kuryanov::spiralTopClk(data, rows, cols, -1);
  kuryanov::spiralBotCnt(data, rows, cols);
  kuryanov::printMatrix(out, data, rows, cols) << '\n';

  std::free(dynamic_array);
  return 0;
}
