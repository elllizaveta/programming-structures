#ifndef BIN_H
#define BIN_H
#include <iostream>

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  const T* l = begin;
  const T* r = end;
  const T* m = l + (r - l) / 2;
  while (r - l > 1) {
    if (value < (*m)) {
      r = m;
    } else {
      l = m;
    }
    m = l + (r - l) / 2;
  }
  if (*l < value || value < (*l)) {
    return false;
  }
  return true;
}

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  const T* l = begin - 1;
  const T* r = end;
  const T* m = l + (r - l) / 2;
  while (r - l > 1) {
    if (*m < value) {
      l = m;
    } else {
      r = m;
    }
    m = l + (r - l) / 2;
  }
  return r;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  const T* l = begin - 1;
  const T* r = end;
  const T* m = l + (r - l) / 2;
  while (r - l > 1) {
    if (value < (*m)) {
      r = m;
    } else {
      l = m;
    }
    m = l + (r - l) / 2;
  }
  return r;
}

#endif
