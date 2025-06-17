#include <iostream>

template <class T>
struct UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr();
  explicit UniquePtr(T*);
  UniquePtr(UniquePtr<T>&&) noexcept;
  UniquePtr<T>& operator=(UniquePtr<T>&&) noexcept;
  T* Release();
  void Reset(T*);
  void Reset();
  void Swap(UniquePtr<T>&);
  T* Get() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
  ~UniquePtr();
};

template <class T>
UniquePtr<T>::UniquePtr() : ptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* other) : ptr_(other) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr_(other.ptr_) {
  other.ptr_ = nullptr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
  UniquePtr tmp = std::move(other);
  Swap(tmp);
  return *this;
}

template <class T>
T* UniquePtr<T>::Release() {
  T* ret = ptr_;
  ptr_ = nullptr;
  return ret;
}

template <class T>
void UniquePtr<T>::Reset(T* other) {
  delete ptr_;
  ptr_ = other;
}

template <class T>
void UniquePtr<T>::Reset() {
  delete ptr_;
  ptr_ = nullptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) {
  std::swap(ptr_, other.ptr_);
}

template <class T>
T* UniquePtr<T>::Get() const {
  return ptr_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return ptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return ptr_ != nullptr;
}

template <class T>
UniquePtr<T>::~UniquePtr<T>() {
  delete ptr_;
}
