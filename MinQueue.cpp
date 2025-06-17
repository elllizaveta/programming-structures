#include <iostream>
#include <cstring>

struct List {
 private:
  struct Node {
    int64_t value;
    Node* next = nullptr;
  };

  Node* end_ = nullptr;
  Node* begin_ = nullptr;
  size_t size_ = 0;

 public:
  size_t Size() const;
  int64_t PopFront();
  void PushBack(int64_t x);
  void PushFront(int64_t x);
  void Clear();
  const int64_t& Front() const;
  const int64_t& Back() const;
};

void List::Clear() {
  while (Size() != 0) {
    PopFront();
  }
}

const int64_t& List::Front() const {
  return begin_->value;
}

const int64_t& List::Back() const {
  return end_->value;
}

size_t List::Size() const {
  return size_;
}

int64_t List::PopFront() {
  --size_;
  Node* del = begin_;
  int64_t del_val = del->value;
  if (Size() == 0) {
    end_ = nullptr;
    begin_ = nullptr;
    delete del;
    return del_val;
  }
  begin_ = del->next;
  delete del;
  return del_val;
}

void List::PushBack(int64_t x) {
  ++size_;
  auto elem = new Node;
  elem->value = x;
  if (Size() == 1) {
    end_ = elem;
    begin_ = elem;
    return;
  }
  end_->next = elem;
  end_ = elem;
}

void List::PushFront(int64_t x) {
  ++size_;
  auto elem = new Node;
  elem->value = x;
  elem->next = begin_;
  if (Size() == 1) {
    end_ = elem;
  }
  begin_ = elem;
}

struct Stack {
 private:
  List a_;

 public:
  size_t Size() const;
  int64_t PopBack();
  void PushBack(int64_t x);
  void Clear();
  const int64_t& Back() const;
  const int64_t& Front() const;
};

size_t Stack::Size() const {
  return a_.Size();
}

int64_t Stack::PopBack() {
  return a_.PopFront();
}

void Stack::PushBack(int64_t x) {
  return a_.PushFront(x);
}

void Stack::Clear() {
  return a_.Clear();
}

const int64_t& Stack::Back() const {
  return a_.Front();
}

const int64_t& Stack::Front() const {
  return a_.Back();
}

struct MinStack {
 private:
  Stack a_;
  Stack min_;

 public:
  size_t Size() const;
  const int64_t& Back() const;
  const int64_t& Front() const;
  void Clear();
  const int64_t& Min() const;
  int64_t PopBack();
  void PushBack(int64_t x);
};

size_t MinStack::Size() const {
  return a_.Size();
}

const int64_t& MinStack::Back() const {
  return a_.Back();
}

const int64_t& MinStack::Front() const {
  return a_.Front();
}

void MinStack::Clear() {
  a_.Clear();
  min_.Clear();
}

const int64_t& MinStack::Min() const {
  return min_.Back();
}

int64_t MinStack::PopBack() {
  min_.PopBack();
  return a_.PopBack();
}

void MinStack::PushBack(int64_t x) {
  if (min_.Size() == 0) {
    min_.PushBack(x);
  } else {
    min_.PushBack(std::min(x, min_.Back()));
  }
  a_.PushBack(x);
}

struct QueueMin {
 private:
  MinStack a_;
  MinStack b_;
  void Replace();

 public:
  size_t Size() const;
  const int64_t& Front() const;
  int64_t Dequeue();
  void Enqueue(int64_t x);
  void Clear();
  const int64_t& Min() const;
};

size_t QueueMin::Size() const {
  return a_.Size() + b_.Size();
}

const int64_t& QueueMin::Front() const {
  if (b_.Size() != 0) {
    return b_.Back();
  }
  return a_.Front();
}

void QueueMin::Clear() {
  a_.Clear();
  b_.Clear();
}

const int64_t& QueueMin::Min() const {
  if (a_.Size() == 0) {
    return b_.Min();
  }
  if (b_.Size() == 0) {
    return a_.Min();
  }
  return std::min(a_.Min(), b_.Min());
}

int64_t QueueMin::Dequeue() {
  if (b_.Size() == 0) {
    Replace();
  }
  return b_.PopBack();
}

void QueueMin::Enqueue(int64_t x) {
  a_.PushBack(x);
}

void QueueMin::Replace() {
  while (a_.Size() != 0) {
    b_.PushBack(a_.PopBack());
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t k;
  std::cin >> k;
  QueueMin s;
  char a[15];
  int64_t x;
  while (std::cin >> a) {
    if (strcmp(a, "front") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.Front() << std::endl;
      }
    } else if (strcmp(a, "size") == 0) {
      std::cout << s.Size() << std::endl;
    } else if (strcmp(a, "clear") == 0) {
      s.Clear();
      std::cout << "ok" << std::endl;
    } else if (strcmp(a, "dequeue") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.Dequeue() << std::endl;
      }
    } else if (strcmp(a, "enqueue") == 0) {
      std::cin >> x;
      s.Enqueue(x);
      std::cout << "ok" << std::endl;
    } else {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.Min() << std::endl;
      }
    }
  }
  s.Clear();
}
