#include <iostream>

template <class T>
void Merge(T* a, T* a_end, T* b, T* b_end, uint64_t& ans) {
  size_t na = a_end - a;
  size_t nb = b_end - b;
  auto c = new T[na + nb];
  size_t ia = 0, ib = 0, ic = 0;
  while (ia < na && ib < nb) {
    if (a[ia] <= b[ib]) {
      c[ic] = a[ia];
      ++ia;
    } else {
      c[ic] = b[ib];
      ++ib;
      ans += na - ia;
    }
    ++ic;
  }
  while (ia < na) {
    c[ic] = a[ia];
    ++ia;
    ++ic;
  }
  while (ib < nb) {
    c[ic] = b[ib];
    ++ib;
    ++ic;
  }
  for (size_t i = 0; i < na; ++i) {
    a[i] = c[i];
  }
  for (size_t i = 0; i < nb; ++i) {
    b[i] = c[na + i];
  }
  delete[] c;
}

template <class T>
void MergeSort(T* a, T* a_end, uint64_t& ans) {
  if (a_end - a == 1 || a_end - a == 0) {
    return;
  }
  MergeSort(a, (a + (a_end - a) / 2), ans);
  MergeSort((a + (a_end - a) / 2), a_end, ans);
  Merge(a, (a + (a_end - a) / 2), (a + (a_end - a) / 2), a_end, ans);
}

int main() {
  size_t n;
  std::cin >> n;
  auto a = new int[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  uint64_t ans = 0;
  MergeSort(a, a + n, ans);
  std::cout << std::endl << ans << std::endl;
  delete[] a;
}
