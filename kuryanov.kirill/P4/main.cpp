#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>

namespace kuryanov
{
  char *resize(const char *arr, size_t &capacity, size_t size)
  {
    const size_t new_capacity = capacity * 2;
    char *const result = new char[new_capacity];
    for (size_t i = 0; i < size; ++i)
    {
      result[i] = arr[i];
    }
    delete[] arr;
    capacity = new_capacity;
    return result;
  }

  char *readLine(size_t &size)
  {
    const size_t initial_capacity = 8;
    size = 0;
    size_t capacity = initial_capacity;
    char *str = new char[capacity];
    char cur = '\0';
    try
    {
      while (std::cin.get(cur) && cur != '\n')
      {
        if (size + 1 >= capacity)
        {
          str = resize(str, capacity, size);
        }
        str[size++] = cur;
      }
    }
    catch (const std::bad_alloc &)
    {
      delete[] str;
      throw;
    }
    str[size] = '\0';
    return str;
  }

  char *latTwo(const char *str1, size_t size1, const char *str2, size_t size2, char *out) noexcept
  {
    size_t result_size = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter)
    {
      bool is_found = false;
      for (size_t i = 0; i < size1 && !is_found; ++i)
      {
        is_found = (std::tolower(static_cast< unsigned char >(str1[i])) == letter);
      }
      for (size_t j = 0; j < size2 && !is_found; ++j)
      {
        is_found = (std::tolower(static_cast< unsigned char >(str2[j])) == letter);
      }
      if (is_found)
      {
        out[result_size++] = letter;
      }
    }
    out[result_size] = '\0';
    return out;
  }

  char *uniTwo(const char *str1, size_t size1, const char *str2, size_t size2, char *out) noexcept
  {
    size_t i = 0;
    size_t i1 = 0;
    size_t i2 = 0;
    while (i1 < size1 || i2 < size2)
    {
      if (i1 < size1)
      {
        out[i++] = str1[i1++];
      }
      if (i2 < size2)
      {
        out[i++] = str2[i2++];
      }
    }
    out[i] = '\0';
    return out;
  }
}

int main()
{
  const char *const latin_second = "def ghk";
  const char *const uniting_second = "def ";
  size_t st_size = 0;
  char *st_string = nullptr;
  char *sumstr = nullptr;
  try
  {
    st_string = kuryanov::readLine(st_size);
    if (st_size == 0)
    {
      std::cerr << "Empty input\n";
      delete[] st_string;
      return 1;
    }
    const size_t latin_size = std::strlen(latin_second);
    const size_t uniting_size = std::strlen(uniting_second);
    sumstr = new char[st_size + uniting_size + 1];
    const size_t num_let = 26;
    char letstr[num_let + 1] = {};

    std::cout << kuryanov::latTwo(st_string, st_size, latin_second, latin_size, letstr) << '\n';
    std::cout << kuryanov::uniTwo(st_string, st_size, uniting_second, uniting_size, sumstr) << '\n';
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation failed\n";
    delete[] st_string;
    delete[] sumstr;
    return 1;
  }

  delete[] st_string;
  delete[] sumstr;
  return 0;
}
