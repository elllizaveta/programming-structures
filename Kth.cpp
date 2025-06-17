#ifndef SORT_H
#define SORT_H
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
  T pivot_value = *pivot;

  while (r > l) {
    if (pivot_value < (*r)) {
      --r;
      continue;
    }
    if (*l < pivot_value) {
      ++l;
      continue;
    }
    if (!(*l < (*r)) && !(*r < (*l))) {
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
void KthElement(T* begin, T* kth, T* end) {
  if (end == begin) {
    return;
  }
  T* new_pivot = Partition(begin, end, kth);
  if (new_pivot < kth) {
    KthElement(new_pivot + 1, kth, end);
    return;
  } else if (kth < new_pivot) {
    KthElement(begin, kth, new_pivot);
    return;
  }
  KthElement(new_pivot, kth, new_pivot);
  return;
}

#endif
