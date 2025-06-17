#include <iostream>

void Enumeration(int* a, size_t num, size_t m, int* b, size_t& count, size_t cur_count, uint64_t sum, uint64_t cur_sum, int* c) {
  if (num == m) {
    if (cur_sum == sum && count > cur_count) {
      for (size_t i = 0; i < cur_count; ++i) {
        c[i] = b[i];
      }
      std::cout << std::endl;
      count = cur_count;
    }
    return;
  }
  Enumeration(a, num + 1, m, b, count, cur_count, sum, cur_sum, c);
  b[cur_count] = a[num];
  cur_sum += a[num];
  Enumeration(a, num + 1, m, b, count, cur_count + 1, sum, cur_sum, c);
  b[cur_count + 1] = a[num];
  cur_sum += a[num];
  Enumeration(a, num + 1, m, b, count, cur_count + 2, sum, cur_sum, c);
}

int main() {
  uint64_t sum;
  uint64_t full_sum = 0;
  std::cin >> sum;
  size_t m;
  std::cin >> m;
  auto a = new int[m];
  for (size_t i = 0; i < m; ++i) {
    std::cin >> a[i];
    full_sum += 2 * a[i];
  }
  auto b = new int[2 * m];
  auto best_comb = new int[2 * m];
  size_t count = 31;
  if (full_sum < sum) {
    std::cout << -1 << std::endl;
  } else {
    Enumeration(a, 0, m, b, count, 0, sum, 0, best_comb);
    if (count == 31) {
      std::cout << 0 << std::endl;
    } else {
      std::cout << count << std::endl;
      for (size_t i = 0; i < count; ++i) {
        std::cout << best_comb[i] << " ";
      }
      std::cout << std::endl;
    }
  }
  delete[] a;
  delete[] b;
  delete[] best_comb;
}
