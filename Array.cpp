#include <iostream>
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
struct Array {
  T arr[N];

  T& operator[](size_t id);
  const T& operator[](size_t id) const;
  T& At(size_t id);
  const T& At(size_t id) const;
  T& Front();
  const T& Front() const;
  T& Back();
  const T& Back() const;
  T* Data();
  const T* Data() const;
  size_t Size() const;
  bool Empty() const;
  void Fill(const T& value);
  void Swap(Array<T, N>& other);
};

template <typename T, size_t N>
T& Array<T, N>::operator[](size_t id) {
  return *(arr + id);
}

template <typename T, size_t N>
const T& Array<T, N>::operator[](size_t id) const {
  return *(arr + id);
}

template <typename T, size_t N>
T& Array<T, N>::At(size_t id) {
  if (id >= N) {
    throw ArrayOutOfRange{};
  }
  return *(arr + id);
}

template <typename T, size_t N>
const T& Array<T, N>::At(size_t id) const {
  if (id >= N) {
    throw ArrayOutOfRange{};
  }
  return *(arr + id);
}

template <typename T, size_t N>
T& Array<T, N>::Front() {
  return *(arr);
}

template <typename T, size_t N>
const T& Array<T, N>::Front() const {
  return *(arr);
}

template <typename T, size_t N>
T& Array<T, N>::Back() {
  return *(arr + N - 1);
}

template <typename T, size_t N>
const T& Array<T, N>::Back() const {
  return *(arr + N - 1);
}

template <typename T, size_t N>
T* Array<T, N>::Data() {
  return arr;
}

template <typename T, size_t N>
const T* Array<T, N>::Data() const {
  return arr;
}

template <typename T, size_t N>
size_t Array<T, N>::Size() const {
  return N;
}

template <typename T, size_t N>
bool Array<T, N>::Empty() const {
  return N == 0 ? true : false;
}

template <typename T, size_t N>
void Array<T, N>::Fill(const T& value) {
  for (size_t i = 0; i < N; ++i) {
    *(arr + i) = value;
  }
}

template <typename T, size_t N>
void Array<T, N>::Swap(Array<T, N>& other) {
  for (size_t i = 0; i < N; ++i) {
    std::swap(arr[i], other[i]);
  }
}

template <typename T, size_t N>
size_t GetSize(T (&)[N]) {
  return N;
}

template <typename T>
size_t GetSize(T) {
  return 0;
}

template <typename T>
struct Rank {
  static constexpr size_t kValue = 0;
};

template <typename T>
struct Rank<T[]> {
  static constexpr size_t kValue = Rank<T>::kValue + 1;
};

template <typename T, size_t N>
struct Rank<T[N]> {
  static constexpr size_t kValue = Rank<T>::kValue + 1;
};

template <typename T, size_t N>
size_t GetRank(T (&)[N]) {
  return Rank<T[N]>::kValue;
}

template <typename T>
size_t GetRank(T) {
  return 0;
}

template <typename T>
struct NumElements {
  static constexpr int64_t kValue = 1;
};

template <typename T>
struct NumElements<T[]> {
  static constexpr int64_t kValue = 1;
};

template <typename T, size_t N>
struct NumElements<T[N]> {
  static constexpr int64_t kValue = NumElements<T>::kValue * N;
};

template <typename T, size_t N>
int64_t GetNumElements(T (&)[N]) {
  return NumElements<T[N]>::kValue;
}

template <typename T>
int64_t GetNumElements(T) {
  return 1;
}
