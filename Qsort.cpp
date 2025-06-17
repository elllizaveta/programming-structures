#include <iostream>

template <class T>
void Swap(T& l, T& r) {
  T k = l;
  l = r;
  r = k;
}

template <class T>
T* Partition(T* begin, T* end, T* pivot) {
  T* l = begin;
  T* r = end - 1;
  int pivot_value = *pivot;
  while (l != r) {
    if (*r > pivot_value) {
      --r;
      continue;
    }
    if (*l < pivot_value) {
      ++l;
      continue;
    }
    if (*l == *r) {
      --r;
    }
    Swap(*l, *r);
  }
  if (*r < pivot_value) {
    Swap(*l, *r);
  }
  return l;
}

template <class T>
void QSort(T* begin, T* end) {
  if (end - begin <= 0) {
    return;
  }
  int x = rand();
  int pivot = x % (end - begin);
  T* new_pivot = Partition(begin, end, begin + pivot);
  QSort(begin, new_pivot);
  QSort(new_pivot + 1, end);
}

bool CheckUnic(int* a, size_t n1, int* b, size_t n2) {
  bool check = true;
  size_t i = 1;
  size_t j = 1;
  if (a[i - 1] != b[j - 1]) {
    check = false;
  }
  while (check && i < n1 && j < n2) {
    if (a[i] == a[i - 1]) {
      i += 1;
      continue;
    }
    if (b[j] == b[j - 1]) {
      j += 1;
      continue;
    }
    if (a[i] != b[j]) {
      check = false;
    }
    i += 1;
    j += 1;
  }
  while (check && i < n1) {
    if (a[i] != a[i - 1]) {
      check = false;
    }
    i += 1;
  }
  while (check && j < n2) {
    if (b[j] != b[j - 1]) {
      check = false;
    }
    j += 1;
  }
  return check;
}

int main() {
  size_t n1;
  std::cin >> n1;
  auto unic_elem_n1 = new int[n1];
  for (size_t i = 0; i < n1; ++i) {
    std::cin >> unic_elem_n1[i];
  }
  QSort(unic_elem_n1, unic_elem_n1 + n1);
  size_t n2;
  std::cin >> n2;
  auto unic_elem_n2 = new int[n2];
  for (size_t i = 0; i < n2; ++i) {
    std::cin >> unic_elem_n2[i];
  }
  QSort(unic_elem_n2, unic_elem_n2 + n2);
  if (CheckUnic(unic_elem_n1, n1, unic_elem_n2, n2)) {
    std::cout << "YES" << std::endl;
  } else {
    std::cout << "NO" << std::endl;
  }
  delete[] unic_elem_n1;
  delete[] unic_elem_n2;
}
