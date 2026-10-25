#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>

void spiralTopClk(int** m, size_t rows, size_t cols, int sign)
{
  size_t top = 0;
  size_t left = 0;
  size_t bottom = rows;
  size_t right = cols;
  int step = 1;
  while (top < bottom && left < right) {
    for (size_t j = left; j < right; ++j) {
      m[top][j] -= sign * step++;
    }
    ++top;
    for (size_t i = top; i < bottom; ++i) {
      m[i][right - 1] -= sign * step++;
    }
    --right;
    if (top < bottom) {
      for (size_t j = right; j > left; --j) {
        m[bottom - 1][j - 1] -= sign * step++;
      }
      --bottom;
    }
    if (left < right) {
      for (size_t i = bottom; i > top; --i) {
        m[i - 1][left] -= sign * step++;
      }
      ++left;
    }
  }
}

void spiralBotCnt(int** m, size_t rows, size_t cols)
{
  size_t top = 0;
  size_t left = 0;
  size_t bottom = rows;
  size_t right = cols;
  int step = 1;
  while (top < bottom && left < right) {
    for (size_t j = left; j < right; ++j) {
      m[bottom - 1][j] += step++;
    }
    --bottom;
    for (size_t i = bottom; i > top; --i) {
      m[i - 1][right - 1] += step++;
    }
    --right;
    if (top < bottom) {
      for (size_t j = right; j > left; --j) {
        m[top][j - 1] += step++;
      }
      ++top;
    }
    if (left < right) {
      for (size_t i = top; i < bottom; ++i) {
        m[i][left] += step++;
      }
      ++left;
    }
  }
}

void printMatrix(const int* const* m, size_t rows, size_t cols, std::ostream& out)
{
  out << rows << ' ' << cols;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      out << ' ' << m[i][j];
    }
  }
  out << '\n';
}

void solve(int** m, size_t rows, size_t cols, std::ostream& out)
{
  spiralTopClk(m, rows, cols, 1);
  printMatrix(m, rows, cols, out);
  spiralTopClk(m, rows, cols, -1);
  spiralBotCnt(m, rows, cols);
  printMatrix(m, rows, cols, out);
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
  const long num = std::strtol(argv[1], &end, 10);
  if (end == argv[1] || *end != '\0') {
    std::cerr << "First parameter is not a number\n";
    return 1;
  }
  switch (num) {
  case 1: {
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

    if (cols != 0 && rows > maxElements / cols) {
      std::cerr << "Matrix is too large\n";
      return 2;
    }
    int arr[maxElements] = {};
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        if (!(input >> arr[i * cols + j])) {
          std::cerr << "Unexpected input\n";
          return 2;
        }
      }
    }
    std::ofstream out(argv[3]);
    if (!out.is_open()) {
      std::cerr << "Cannot open output file\n";
      return 2;
    }
    int* row_ptrs[maxElements];
    if (cols != 0) {
      for (size_t i = 0; i < rows; ++i) {
        row_ptrs[i] = arr + i * cols;
      }
    }
    solve(row_ptrs, rows, cols, out);
    break;
  }
  case 2: {
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

    int** const arr = static_cast< int** >(std::malloc(rows * sizeof(*arr)));
    if (arr == nullptr && rows > 0) {
      std::cerr << "Memory allocation failed\n";
      return 2;
    }
    for (size_t i = 0; i < rows; ++i) {
      arr[i] = static_cast< int* >(std::malloc(cols * sizeof(*arr[i])));
      if (arr[i] == nullptr && cols > 0) {
        for (size_t k = 0; k < i; ++k) {
          std::free(arr[k]);
        }
        std::free(arr);
        std::cerr << "Memory allocation failed\n";
        return 2;
      }
    }

    for (size_t i = 0; i < rows; ++i) {
      for (size_t j = 0; j < cols; ++j) {
        if (!(input >> arr[i][j])) {
          std::cerr << "Unexpected input\n";
          for (size_t k = 0; k < rows; ++k) {
            std::free(arr[k]);
          }
          std::free(arr);
          return 2;
        }
      }
    }
    std::ofstream out(argv[3]);
    if (!out.is_open()) {
      std::cerr << "Cannot open output file\n";
      for (size_t i = 0; i < rows; ++i) {
        std::free(arr[i]);
      }
      std::free(arr);
      return 2;
    }
    solve(arr, rows, cols, out);

    for (size_t i = 0; i < rows; ++i) {
      std::free(arr[i]);
    }
    std::free(arr);
    break;
  }
  default:
    std::cerr << "First parameter is not a number or out of range\n";
    return 1;
  }
  return 0;
}
