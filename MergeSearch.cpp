#ifndef MERGE_H
#define MERGE_H
#include <iostream>

template <class T, class U, class R>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, R* out) {
  size_t na = first_end - first_begin;
  size_t nb = second_end - second_begin;
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
}

#endif
