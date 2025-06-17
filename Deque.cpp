#include <cstring>
#include <iostream>

struct List {
 private:
  struct Node {
    int64_t value;
    Node* next = nullptr;
    Node* prev = nullptr;
  };

  Node* begin_ = nullptr;
  Node* end_ = nullptr;
  size_t size_ = 0;

 public:
  size_t GetSize() const;
  const int64_t& Front() const;
  const int64_t& Back() const;
  int64_t PopFront();
  int64_t PopBack();
  void PushFront(int64_t x);
  void PushBack(int64_t x);
  void Clear();
};

size_t List::GetSize() const {
  return size_;
}

void List::Clear() {
  while (GetSize() != 0) {
    PopFront();
  }
}

const int64_t& List::Front() const {
  return begin_->value;
}

const int64_t& List::Back() const {
  return end_->value;
}

int64_t List::PopFront() {
  if (GetSize() == 1) {
    Node* del = begin_;
    int64_t del_val = del->value;
    begin_ = nullptr;
    end_ = nullptr;
    --size_;
    delete del;
    return del_val;
  }
  Node* del = begin_;
  int64_t del_val = del->value;
  begin_ = del->next;
  begin_->prev = nullptr;
  --size_;
  delete del;
  return del_val;
}

int64_t List::PopBack() {
  if (GetSize() == 1) {
    Node* del = end_;
    int64_t del_val = del->value;
    begin_ = nullptr;
    end_ = nullptr;
    --size_;
    delete del;
    return del_val;
  }
  Node* del = end_;
  int64_t del_val = del->value;
  end_ = del->prev;
  end_->next = nullptr;
  --size_;
  delete del;
  return del_val;
}

void List::PushFront(int64_t x) {
  ++size_;
  if (GetSize() == 1) {
    auto elem = new Node;
    elem->value = x;
    begin_ = elem;
    end_ = begin_;
    return;
  }
  auto elem = new Node;
  elem->value = x;
  elem->next = begin_;
  begin_->prev = elem;
  begin_ = elem;
}

void List::PushBack(int64_t x) {
  ++size_;
  if (GetSize() == 1) {
    auto elem = new Node;
    elem->value = x;
    end_ = elem;
    begin_ = end_;
    return;
  }
  auto elem = new Node;
  elem->value = x;
  elem->prev = end_;
  end_->next = elem;
  end_ = elem;
}

struct Deque {
 private:
  List deque_;

 public:
  size_t Size() const {
    return deque_.GetSize();
  }
  const int64_t& Front() const {
    return deque_.Front();
  }
  const int64_t& Back() const {
    return deque_.Back();
  }
  int64_t PopFront() {
    return deque_.PopFront();
  }
  int64_t PopBack() {
    return deque_.PopBack();
  }
  void PushFront(int64_t x) {
    return deque_.PushFront(x);
  }
  void PushBack(int64_t x) {
    return deque_.PushBack(x);
  }
  void Clear() {
    return deque_.Clear();
  }
};

int main() {
  size_t k;
  std::cin >> k;
  Deque s;
  char a[15];
  int64_t x;
  while (std::cin >> a) {
    if (strcmp(a, "front") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.Front() << std::endl;
      }
    } else if (strcmp(a, "back") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.Back() << std::endl;
      }
    } else if (strcmp(a, "size") == 0) {
      std::cout << s.Size() << std::endl;
    } else if (strcmp(a, "clear") == 0) {
      s.Clear();
      std::cout << "ok" << std::endl;
    } else if (strcmp(a, "pop_front") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.PopFront() << std::endl;
      }
    } else if (strcmp(a, "pop_back") == 0) {
      if (s.Size() == 0) {
        std::cout << "error" << std::endl;
      } else {
        std::cout << s.PopBack() << std::endl;
      }
    } else if (strcmp(a, "push_front") == 0) {
      std::cin >> x;
      s.PushFront(x);
      std::cout << "ok" << std::endl;
    } else if (strcmp(a, "push_back") == 0) {
      std::cin >> x;
      s.PushBack(x);
      std::cout << "ok" << std::endl;
    } else {
      s.Clear();
      std::cout << "bye" << std::endl;
      return 0;
    }
  }
  s.Clear();
}
