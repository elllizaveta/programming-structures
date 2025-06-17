#include <iomanip>
#include <memory>
#include <stdexcept>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

class Any {
 private:
  class IHolder {
   public:
    virtual IHolder* Clone() const = 0;
    virtual ~IHolder() = default;
  };

  template <typename T>
  class AnyHolder : public IHolder {
   public:
    T value_;

    explicit AnyHolder(const T&);
    AnyHolder<T>& operator=(const AnyHolder&);
    IHolder* Clone() const override;
    void Swap(AnyHolder&);
  };

  IHolder* ptr_;

  template <typename T>
  friend T AnyCast(const Any& value);

 public:
  Any();
  Any(const Any&);
  Any(Any&& other);
  ~Any();

  template <typename T>
  Any(const T&);  // NOLINT

  template <typename T>
  Any& operator=(const T&);
  Any& operator=(Any&&);
  Any& operator=(const Any&);

  void Swap(Any& other);
  void Reset();
  bool HasValue() const;
};

template <typename T>
Any::AnyHolder<T>::AnyHolder(const T& other) : value_(other) {
}

template <typename T>
Any::AnyHolder<T>& Any::AnyHolder<T>::operator=(const AnyHolder<T>& other) {
  if (this == &other) {
    return *this;
  }
  AnyHolder<T> tmp = other;
  Swap(tmp);
  return *this;
}

template <typename T>
void Any::AnyHolder<T>::Swap(AnyHolder<T>& other) {
  std::swap(value_, other.value_);
}

template <typename T>
Any::IHolder* Any::AnyHolder<T>::Clone() const {
  return new AnyHolder<T>(value_);
}

inline Any::Any() : ptr_(nullptr) {
}

inline Any::Any(const Any& other) {
  if (other.ptr_) {
    ptr_ = other.ptr_->Clone();
  } else {
    ptr_ = nullptr;
  }
}

inline Any::~Any() {
  delete ptr_;
}

template <typename T>
Any::Any(const T& other) : ptr_(new AnyHolder<T>(other)) {
}

inline Any::Any(Any&& other) : ptr_(std::move(other.ptr_)) {
  other.ptr_ = nullptr;
}

template <typename T>
Any& Any::operator=(const T& other) {
  Any tmp = other;
  Swap(tmp);
  return *this;
}

inline Any& Any::operator=(Any&& other) {
  if (this == &other) {
    return *this;
  }
  auto tmp = std::move(other);
  Swap(tmp);
  return *this;
}

inline Any& Any::operator=(const Any& other) {
  if (this == &other) {
    return *this;
  }
  Any tmp = other;
  Swap(tmp);
  return *this;
}

inline void Any::Swap(Any& other) {
  std::swap(ptr_, other.ptr_);
}

inline void Any::Reset() {
  if (HasValue()) {
    delete ptr_;
  }
  ptr_ = nullptr;
}

inline bool Any::HasValue() const {
  return !(ptr_ == nullptr);
}

template <typename T>
T AnyCast(const Any& value) {
  auto tmp = dynamic_cast<Any::AnyHolder<T>*>(value.ptr_);
  if (tmp == nullptr) {
    throw BadAnyCast();
  }
  return tmp->value_;
}
