#include <iostream>

struct AVL {
 private:
  struct Node {
    int64_t key;
    int height = 1;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  Node* root_ = nullptr;

  int BalanceFactor(const Node* root) const;
  void FixHeight(Node* root);
  void ClearNode(Node* root);
  Node* RightRotate(Node* root);
  Node* LeftRotate(Node* root);
  Node* Balance(Node* root);
  Node* InsertNode(Node* root, int64_t x);
  int HeightNode(const Node* root) const;

 public:
  void Insert(int64_t x);
  void Clear();
  int64_t Find(int64_t x) const;
  int Height() const;
};

int AVL::Height() const {
  return HeightNode(root_);
}

AVL::Node* AVL::Balance(Node* root) {
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

AVL::Node* AVL::RightRotate(Node* root) {
  Node* l = root->left;
  root->left = l->right;
  l->right = root;
  FixHeight(root);
  FixHeight(l);
  return l;
}

AVL::Node* AVL::LeftRotate(Node* root) {
  Node* r = root->right;
  root->right = r->left;
  r->left = root;
  FixHeight(root);
  FixHeight(r);
  return r;
}

void AVL::Clear() {
  ClearNode(root_);
}

int AVL::BalanceFactor(const Node* root) const {
  return HeightNode(root->right) - HeightNode(root->left);
}

void AVL::FixHeight(Node* root) {
  root->height = std::max(HeightNode(root->left), HeightNode(root->right)) + 1;
}

void AVL::ClearNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  ClearNode(root->left);
  ClearNode(root->right);
  delete root;
}

int AVL::HeightNode(const Node* root) const {
  return root == nullptr ? 0 : root->height;
}

void AVL::Insert(int64_t x) {
  root_ = InsertNode(root_, x);
}

AVL::Node* AVL::InsertNode(Node* root, int64_t x) {
  if (root == nullptr) {
    auto r = new Node;
    r->key = x;
    return r;
  }
  if (x < root->key) {
    root->left = InsertNode(root->left, x);
  } else {
    root->right = InsertNode(root->right, x);
  }
  return Balance(root);
}

int64_t AVL::Find(int64_t x) const {
  int64_t ans = -1;
  Node* cur = root_;
  while (cur != nullptr) {
    if (x == cur->key) {
      ans = x;
      break;
    }
    if (x < cur->key) {
      if (ans > cur->key || ans < x) {
        ans = cur->key;
      }
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return ans;
}

int main() {
  size_t n;
  std::cin >> n;
  AVL s;
  char type;
  int64_t x;
  int64_t next;
  bool is_was_next = false;
  const uint64_t mod = 1'000'000'000;
  while (std::cin >> type) {
    std::cin >> x;
    if (type == '+') {
      if (is_was_next) {
        s.Insert((x + next + mod) % mod);
        is_was_next = false;
      } else {
        s.Insert(x);
      }
    } else {
      is_was_next = true;
      if (s.Height() == 0) {
        next = -1;
      } else {
        next = s.Find(x);
      }
      std::cout << next << std::endl;
    }
  }
  s.Clear();
}
