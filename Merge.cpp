#ifndef SORT_H
#define SORT_H
#include <iostream>

template <class T>
void Merge(T* first_begin, T* first_end, T* second_begin, T* second_end) {
  size_t na = first_end - first_begin;
  size_t nb = second_end - second_begin;
  T* out = new T[na + nb];
  size_t ia = 0, ib = 0, ic = 0;
  while (ia < na && ib < nb) {
    if (first_begin[ia] < second_begin[ib]) {
      out[ic] = first_begin[ia];
      ++ia;
    } else {
      out[ic] = second_begin[ib];
      ++ib;
    }
    ++ic;
  }
  while (ia < na) {
    out[ic] = first_begin[ia];
    ++ia;
    ++ic;
  }
  while (ib < nb) {
    out[ic] = second_begin[ib];
    ++ib;
    ++ic;
  }
  for (size_t i = 0; i < na + nb; ++i) {
    if (i < na) {
      first_begin[i] = out[i];
    } else {
      second_begin[i - (first_end - first_begin)] = out[i];
    }
  }
  delete[] out;
}

template <class T>
void Sort(T* a, T* a_end) {
  if (a_end < a + 2) {
    return;
  }
  Sort(a, (a + (a_end - a) / 2));
  Sort((a + (a_end - a) / 2), a_end);
  Merge(a, (a + (a_end - a) / 2), (a + (a_end - a) / 2), a_end);
}

#endif
