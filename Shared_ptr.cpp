#include <iostream>

template <class T>
struct SharedPtr {
 private:
  T* ptr_ = nullptr;
  size_t* strong_counter_ = nullptr;

 public:
  SharedPtr() noexcept;
  SharedPtr(std::nullptr_t) noexcept;  // NOLINT
  explicit SharedPtr(T* other);
  SharedPtr(const SharedPtr<T>& other) noexcept;
  SharedPtr(SharedPtr<T>&& other) noexcept;
  SharedPtr<T>& operator=(const SharedPtr<T>& other) noexcept;
  SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;
  void Reset(T* other);
  void Reset();
  void Swap(SharedPtr<T>&);
  T* Get() const;
  size_t UseCount() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
  ~SharedPtr();
};

template <class T>
SharedPtr<T>::SharedPtr() noexcept : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(std::nullptr_t) noexcept : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(T* other) : ptr_(other), strong_counter_(new size_t(1)) {
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  if (strong_counter_) {
    ++(*strong_counter_);
  }
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
  other.ptr_ = nullptr;
  other.strong_counter_ = nullptr;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) noexcept {
  SharedPtr<T> tmp = other;
  Swap(tmp);
  return *this;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
  SharedPtr<T> tmp = std::move(other);
  Swap(tmp);
  return *this;
}

template <class T>
void SharedPtr<T>::Reset(T* other) {
  SharedPtr<T> tmp(other);
  Swap(tmp);
}

template <class T>
void SharedPtr<T>::Reset() {
  SharedPtr<T> tmp(nullptr);
  Swap(tmp);
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& other) {
  std::swap(ptr_, other.ptr_);
  std::swap(strong_counter_, other.strong_counter_);
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
size_t SharedPtr<T>::UseCount() const {
  if (!strong_counter_) {
    return 0;
  }
  return *strong_counter_;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return ptr_ != nullptr;
}

template <class T>
SharedPtr<T>::~SharedPtr<T>() {
  if (strong_counter_ == nullptr) {
    return;
  }
  if (--(*strong_counter_) == 0) {
    delete ptr_;
    delete strong_counter_;
  }
}
