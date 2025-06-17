#include <iostream>

struct SplayTree {
 private:
  struct Node {
    int64_t key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };

  struct Pair {
    Node* first;
    Node* second;
  };

  Node* root_ = nullptr;
  void SetParent(Node* child, Node* parent);
  void KeepParent(Node* root);
  void Rotate(Node* child, Node* parent);
  Node* Splay(Node* root);
  Node* Find(Node* root, int64_t key);
  Pair* Split(Node* root, int64_t key);
  void ClearNode(Node* root);
  void PrintNode(Node* root);
  Node* Next(Node* root, int64_t key);

 public:
  void Insert(int64_t key);
  void Print();
  int64_t Find(int64_t key);
  void Clear();
};

void SplayTree::PrintNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  if (root->left) {
    PrintNode(root->left);
  }
  std::cout << root->key << " ";
  if (root->right) {
    PrintNode(root->right);
  }
}

void SplayTree::Print() {
  return PrintNode(root_);
}

void SplayTree::ClearNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  ClearNode(root->left);
  ClearNode(root->right);
  delete root;
}

void SplayTree::Clear() {
  ClearNode(root_);
}

void SplayTree::SetParent(Node* child, Node* parent) {
  if (child != nullptr) {
    child->parent = parent;
  }
}

void SplayTree::KeepParent(Node* root) {
  SetParent(root->left, root);
  SetParent(root->right, root);
}

void SplayTree::Rotate(Node* child, Node* parent) {
  Node* gparent = parent->parent;
  if (gparent != nullptr) {
    if (gparent->left == parent) {
      gparent->left = child;
    } else {
      gparent->right = child;
    }
  }
  if (parent->left == child) {
    parent->left = child->right;
    child->right = parent;
  } else {
    parent->right = child->left;
    child->left = parent;
  }
  KeepParent(child);
  KeepParent(parent);
  SetParent(child, gparent);
}

SplayTree::Node* SplayTree::Splay(Node* root) {
  if (root->parent == nullptr) {
    return root;
  }
  Node* parent = root->parent;
  Node* gparent = parent->parent;
  if (gparent == nullptr) {
    Rotate(root, parent);
    return root;
  }
  if ((gparent->left == parent) == (parent->left == root)) {
    Rotate(parent, gparent);
    Rotate(root, parent);
  } else {
    Rotate(root, parent);
    Rotate(root, gparent);
  }
  return Splay(root);
}

SplayTree::Node* SplayTree::Next(Node* root, int64_t key) {
  if (root == nullptr) {
    return nullptr;
  }
  if (key < root->key && root->left != nullptr) {
    auto find = Next(root->left, key);
    return Splay(find->key < key ? root : find);
  }
  if (key > root->key && root->right != nullptr) {
    return Next(root->right, key);
  }
  return Splay(root);
}

SplayTree::Node* SplayTree::Find(Node* root, int64_t key) {
  if (root == nullptr) {
    return nullptr;
  }
  if (key < root->key && root->left != nullptr) {
    return Find(root->left, key);
  }
  if (key > root->key && root->right != nullptr) {
    return Find(root->right, key);
  }
  return Splay(root);
}

int64_t SplayTree::Find(int64_t key) {
  root_ = Next(root_, key);
  if ((root_ != nullptr && root_->key < key) || root_ == nullptr) {
    return -1;
  }
  return root_->key;
}

SplayTree::Pair* SplayTree::Split(Node* root, int64_t key) {
  auto ans = new Pair;
  if (root == nullptr) {
    ans->first = nullptr;
    ans->second = nullptr;
    return ans;
  }
  root = Find(root, key);
  if (root->key == key) {
    SetParent(root->left, nullptr);
    SetParent(root->right, nullptr);
    ans->first = root->left;
    ans->second = root->right;
    delete root;
    root_ = root;
    return ans;
  }
  if (root->key > key) {
    Node* left = root->left;
    root->left = nullptr;
    SetParent(left, nullptr);
    ans->first = left;
    ans->second = root;
    root_ = root;
    return ans;
  }
  Node* right = root->right;
  root->right = nullptr;
  SetParent(right, nullptr);
  ans->first = root;
  ans->second = right;
  root_ = root;
  return ans;
}

void SplayTree::Insert(int64_t key) {
  auto chichi = Split(root_, key);
  auto ver = new Node;
  ver->key = key;
  ver->left = chichi->first;
  ver->right = chichi->second;
  KeepParent(ver);
  root_ = ver;
  delete chichi;
}

int main() {
  size_t n;
  std::cin >> n;
  SplayTree s;
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
      next = s.Find(x);
      std::cout << next << std::endl;
    }
  }
  s.Clear();
}
