#include <iostream>

struct Pair {
  int64_t key = 0;
  int64_t value = 0;
};

struct Gryazzz {
 private:
  struct Node {
    int64_t key;
    int64_t value;
    int height = 1;
    size_t size = 1;
    int64_t max_lenght;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root_ = nullptr;

 public:
  void Clear();
  int Height() const;
  size_t Size() const;
  void Erase(int64_t key);
  Pair NextKey(int64_t key) const;
  Pair NextValue(int64_t key) const;
  void Insert(int64_t key, int64_t value);
  Pair Max();
  Pair MaxLength();

 private:
  int BalanceFactor(const Node* root) const;
  void FixHeight(Node* root);
  void ClearNode(Node* root);
  Node* RightRotate(Node* root);
  Node* LeftRotate(Node* root);
  Node* Balance(Node* root);
  int HeightNode(Node* root) const;
  size_t SizeNode(Node* root) const;
  int64_t Kth(Node* root, size_t idx) const;
  Node* EraseNode(Node* root, int64_t key);
  Node* InsertNode(Node* root, int64_t key, int64_t value);
  Node* MinimumNode(Node* root);
  Node* EraseMinKey(Node* root);
  int64_t Length(Node* root);
  Pair MaxLengthNode(Node* root);
  int64_t MaxLength(Node* root);
};

// Private methods:

int Gryazzz::BalanceFactor(const Node* root) const {
  return HeightNode(root->right) - HeightNode(root->left);
}

void Gryazzz::FixHeight(Node* root) {
  root->height = std::max(HeightNode(root->left), HeightNode(root->right)) + 1;
  root->size = SizeNode(root->left) + SizeNode(root->right) + 1;
  root->max_lenght = std::max(Length(root), std::max(MaxLength(root->left), MaxLength(root->right)));
}

int64_t Gryazzz::MaxLength(Node* root) {
  return root == nullptr ? 0 : root->max_lenght;
}

int64_t Gryazzz::Length(Node* root) {
  return root == nullptr ? 0 : root->value - root->key + 1;
}

void Gryazzz::ClearNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  ClearNode(root->left);
  ClearNode(root->right);
  delete root;
}

Gryazzz::Node* Gryazzz::RightRotate(Node* root) {
  Node* l = root->left;
  root->left = l->right;
  l->right = root;
  FixHeight(root);
  FixHeight(l);
  return l;
}

Gryazzz::Node* Gryazzz::LeftRotate(Node* root) {
  Node* r = root->right;
  root->right = r->left;
  r->left = root;
  FixHeight(root);
  FixHeight(r);
  return r;
}

Gryazzz::Node* Gryazzz::Balance(Node* root) {
  FixHeight(root);
  if (BalanceFactor(root) == 2) {
    if (BalanceFactor(root->right) == -1) {
      root->right = RightRotate(root->right);
    }
    return LeftRotate(root);
  }
  if (BalanceFactor(root) == -2) {
    if (BalanceFactor(root->left) == 1) {
      root->left = LeftRotate(root->left);
    }
    return RightRotate(root);
  }
  return root;
}

int Gryazzz::HeightNode(Node* root) const {
  return root == nullptr ? 0 : root->height;
}

size_t Gryazzz::SizeNode(Node* root) const {
  return root == nullptr ? 0 : root->size;
}

int64_t Gryazzz::Kth(Node* root, size_t idx) const {
  if (SizeNode(root->left) == idx) {
    return root->key;
  }
  if (SizeNode(root->left) > idx) {
    return Kth(root->left, idx);
  }
  return Kth(root->right, idx - SizeNode(root->left) - 1);
}

Gryazzz::Node* Gryazzz::EraseNode(Node* root, int64_t key) {
  if (root == nullptr) {
    return root;
  }
  if (key < root->key) {
    root->left = EraseNode(root->left, key);
  } else if (key > root->key) {
    root->right = EraseNode(root->right, key);
  } else {
    Node* left = root->left;
    Node* right = root->right;
    delete root;
    if (right == nullptr) {
      return left;
    }
    Node* min = MinimumNode(right);
    min->right = EraseMinKey(right);
    min->left = left;
    return Balance(min);
  }
  return Balance(root);
}

Gryazzz::Node* Gryazzz::MinimumNode(Node* root) {
  Node* min = root;
  while (min != nullptr && min->left != nullptr) {
    min = min->left;
  }
  return min;
}

Gryazzz::Node* Gryazzz::InsertNode(Node* root, int64_t key, int64_t value) {
  if (root == nullptr) {
    auto r = new Node;
    r->key = key;
    r->value = value;
    r->max_lenght = value - key + 1;
    return r;
  }
  if (key < root->key) {
    root->left = InsertNode(root->left, key, value);
  } else {
    root->right = InsertNode(root->right, key, value);
  }
  return Balance(root);
}

Gryazzz::Node* Gryazzz::EraseMinKey(Node* root) {
  if (root->left == nullptr) {
    return root->right;
  }
  root->left = EraseMinKey(root->left);
  return Balance(root);
}

Pair Gryazzz::MaxLengthNode(Node* root) {
  if (root->left != nullptr && root->left->max_lenght == root_->max_lenght) {
    return MaxLengthNode(root->left);
  }
  if (Length(root) == root_->max_lenght) {
    Pair ans = {root_->max_lenght, root->key};
    return ans;
  }
  return MaxLengthNode(root->right);
}

// Public methods:

void Gryazzz::Clear() {
  ClearNode(root_);
  root_ = nullptr;
}

int Gryazzz::Height() const {
  return HeightNode(root_);
}

size_t Gryazzz::Size() const {
  return SizeNode(root_);
}

void Gryazzz::Erase(int64_t key) {
  root_ = EraseNode(root_, key);
}

Pair Gryazzz::NextKey(int64_t key) const {
  Pair ans = {-1, 0};
  Node* cur = root_;
  while (cur != nullptr) {
    if (key == cur->key) {
      ans.key = key;
      ans.value = cur->value;
      break;
    }
    if (key < cur->key) {
      if (ans.key > cur->key || ans.key < key) {
        ans.key = cur->key;
        ans.value = cur->value;
      }
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return ans;
}

Pair Gryazzz::NextValue(int64_t key) const {
  Pair ans = {0, -1};
  Node* cur = root_;
  while (cur != nullptr) {
    if (key == cur->value) {
      ans.value = key;
      ans.key = cur->key;
      break;
    }
    if (key < cur->value) {
      if (ans.value > cur->value || ans.value < key) {
        ans.value = cur->value;
        ans.key = cur->key;
      }
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return ans;
}

void Gryazzz::Insert(int64_t key, int64_t value) {
  root_ = InsertNode(root_, key, value);
}

Pair Gryazzz::Max() {
  Node* min = root_;
  while (min->right != nullptr) {
    min = min->right;
  }
  Pair pair = {min->key, min->value};
  return pair;
}

Pair Gryazzz::MaxLength() {
  return MaxLengthNode(root_);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  // Дерево свободных ячеек: key = "начало", value = "конец"
  Gryazzz free;
  free.Insert(1, n);
  // Номера запроса: key = "номер запроса", value = "пара: начало, конец выделенной памяти"
  auto requests = new Pair[m + 1];

  int64_t request;
  for (size_t i = 1; i <= m; ++i) {
    std::cin >> request;
    if (request > 0) {
      if (free.Size() == 0) {
        std::cout << -1 << std::endl;
        continue;
      }
      auto[length, begin] = free.MaxLength();
      if (length < request) {
        std::cout << -1 << std::endl;
        continue;
      }
      int64_t end = begin + length - 1;
      free.Erase(begin);
      if (length != request) {
        free.Insert(begin + request, end);
      }
      *(requests + i) = {begin, begin + request - 1};
      std::cout << begin << std::endl;
    } else {
      request *= -1;
      auto[start, end] = *(requests + request);
      if (end == 0 && start == 0) {
        continue;
      }
      auto[prev_start, prev_end] = free.NextValue(start - 1);
      auto[next_start, next_end] = free.NextKey(end + 1);
      if (prev_end == start - 1) {
        start = prev_start;
        free.Erase(prev_start);
      }
      if (next_start == end + 1) {
        end = next_end;
        free.Erase(next_start);
      }
      free.Insert(start, end);
    }
  }
  free.Clear();
  delete[] requests;
}
