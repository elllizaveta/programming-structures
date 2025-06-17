#ifndef HEAP_H
#define HEAP_H
#include <iostream>

template <class T>
void Swap(T& l, T& r) {
  T k = l;
  l = r;
  r = k;
}

template <class T>
void SiftUp(T* begin, T* i) {
  T* parent = begin + (i - 1 - begin) / 2;
  if (i > begin && (*parent) < (*i)) {
    Swap(*parent, *i);
    SiftUp(begin, parent);
  }
}

template <class T>
void PushHeap(T* begin, T* end) {
  SiftUp(begin, end - 1);
}

template <class T>
void SiftDown(T* begin, T* end, T* i) {
  T* left = begin + 2 * (i - begin) + 1;
  T* right = begin + 2 * (i - begin) + 2;
  T* largest = i;
  if (left < end && (*largest) < (*left)) {
    largest = left;
  }
  if (right < end && (*largest) < (*right)) {
    largest = right;
  }
  if (largest != i) {
    Swap(*largest, *i);
    SiftDown(begin, end, largest);
  }
}

template <class T>
void PopHeap(T* begin, T* end) {
  Swap(*begin, *(end - 1));
  SiftDown(begin, end - 1, begin);
}

#endif
