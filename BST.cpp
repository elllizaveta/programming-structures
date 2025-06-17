#include <iostream>

struct BST {
 private:
  struct Node {
    int64_t key;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
  };

  Node* root_ = nullptr;

  void ClearNode(Node* root);
  void PrintNode(Node* root);
  void PreOrderNode(Node* root);
  void PostOrderNode(Node* root);
  Node* BuildBSTNode(int64_t* begin, int64_t* end);

 public:
  void Insert(int64_t x);
  void Clear();
  void BuildBST(int64_t* begin, int64_t* end);
  void PreOrder();
  void PostOrder();
};

void BST::Clear() {
  ClearNode(root_);
}

void BST::PreOrderNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->key << " ";
  PreOrderNode(root->left);
  PreOrderNode(root->right);
}

void BST::PreOrder() {
  PreOrderNode(root_);
  std::cout << std::endl;
}

void BST::PostOrderNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  PostOrderNode(root->left);
  PostOrderNode(root->right);
  std::cout << root->key << " ";
}

void BST::PostOrder() {
  PostOrderNode(root_);
  std::cout << std::endl;
}

void BST::ClearNode(Node* root) {
  if (root == nullptr) {
    return;
  }
  if (root->left != nullptr) {
    ClearNode(root->left);
  }
  if (root->right != nullptr) {
    ClearNode(root->right);
  }
  delete root;
}

void BST::Insert(int64_t x) {
  Node* parent = nullptr;
  Node* cur = root_;
  while (cur != nullptr) {
    parent = cur;
    if (cur->key == x) {
      return;
    }
    if (x < cur->key) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  auto ins = new Node;
  ins->key = x;
  ins->parent = parent;
  if (parent == nullptr) {
    root_ = ins;
    return;
  }
  if (ins->key < parent->key) {
    parent->left = ins;
    return;
  }
  parent->right = ins;
}

BST::Node* BST::BuildBSTNode(int64_t* begin, int64_t* end) {
  if (begin >= end) {
    return nullptr;
  }
  auto root = new Node;
  root->key = *begin;
  int64_t* lb = std::lower_bound(begin + 1, end, root->key);
  root->left = BuildBSTNode(begin + 1, lb);
  root->right = BuildBSTNode(lb, end);
  return root;
}

void BST::BuildBST(int64_t* begin, int64_t* end) {
  root_ = BuildBSTNode(begin, end);
}

int main() {
  size_t n;
  BST s;
  std::cin >> n;
  auto a = new int64_t[n];
  for (size_t i = 0; i < n; ++i) {
    std::cin >> *(a + i);
  }
  s.BuildBST(a, a + n);
  s.PostOrder();
  s.Clear();
  delete[] a;
}
