#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stack>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BinaryTreeIterator {
public:
  enum class TraverseOrder {
    PreOrder,
    InOrder,
    PostOrder
  };

  BinaryTreeIterator(TreeNode* root, TraverseOrder order)
    : root_(root),
      order_(order)
  {
    if (root) {
      switch (order_) {
      case TraverseOrder::PreOrder:
        nodes_.push(root);
        break;
      case TraverseOrder::InOrder:
        InOrder(root);
        break;
      case TraverseOrder::PostOrder:
        PostOrder(root);
        break;
      }
    }
  }

  bool hasNext() const {
    return !nodes_.empty();
  }

  int next() {
    TreeNode* next_root = nodes_.top();
    nodes_.pop();
    switch (order_) {
    case TraverseOrder::PreOrder:
      if (next_root->right) {
        nodes_.push(next_root->right);
      }
      if (next_root->left) {
        nodes_.push(next_root->left);
      }
      break;
    case TraverseOrder::InOrder:
      if (next_root->right) {
        InOrder(next_root->right);
      }
      break;
    case TraverseOrder::PostOrder:
      // Nothing to do
      break;
    }

    return next_root->val;
  }

private:
    void InOrder(TreeNode* root) {
        while(root) {
            nodes_.push(root);
            root = root->left;
        }
    }

    void PostOrder(TreeNode* root) {
      if (root) {
        nodes_.push(root);
        PostOrder(root->right);
        PostOrder(root->left);
      }
    }

  TreeNode* root_ = nullptr;
  TraverseOrder order_;
  std::stack<TreeNode*> nodes_;
};

#endif // BINARYTREE_H
