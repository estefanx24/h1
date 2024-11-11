#ifndef AVL_IMPL_H
#define AVL_IMPL_H

#include <algorithm>

#include "avl.h"

template <typename T>
AVLNode<T>::AVLNode(T value)
    : data(value), left(nullptr), right(nullptr), height(1) {}

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) const {
  if (node == nullptr)
    return 0;
  return node->height;
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) const {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
  AVLNode<T>* x = y->left;
  AVLNode<T>* T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = 1 + std::max(height(y->left), height(y->right));
  x->height = 1 + std::max(height(x->left), height(x->right));

  return x;
}

template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
  AVLNode<T>* y = x->right;
  AVLNode<T>* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = 1 + std::max(height(x->left), height(x->right));
  y->height = 1 + std::max(height(y->left), height(y->right));

  return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
  AVLNode<T>* current = node;

  while (current->left != nullptr)
    current = current->left;

  return current;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
  if (node == nullptr)
    return new AVLNode<T>(key);

  if (key < node->data)
    node->left = insert(node->left, key);
  else if (key > node->data)
    node->right = insert(node->right, key);
  else
    return node;

  node->height = 1 + std::max(height(node->left), height(node->right));

  int balance = getBalance(node);


  if (balance > 1 && key < node->left->data)
    return rightRotate(node);

  if (balance < -1 && key > node->right->data)
    return leftRotate(node);

  if (balance > 1 && key > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, T key) {
  if (node == nullptr)
    return node;

  if (key < node->data)
    node->left = remove(node->left, key);
  else if (key > node->data)
    node->right = remove(node->right, key);
  else {
    if ((node->left == nullptr) || (node->right == nullptr)) {
      AVLNode<T>* temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      AVLNode<T>* temp = minValueNode(node->right);

      node->data = temp->data;

      node->right = remove(node->right, temp->data);
    }
  }

  if (node == nullptr)
    return node;

  node->height = 1 + std::max(height(node->left), height(node->right));

  int balance = getBalance(node);


  if (balance > 1 && getBalance(node->left) >= 0)
    return rightRotate(node);

  if (balance > 1 && getBalance(node->left) < 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && getBalance(node->right) <= 0)
    return leftRotate(node);

  if (balance < -1 && getBalance(node->right) > 0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

template <typename T>
bool AVLTree<T>::search(AVLNode<T>* node, T key) const {
  if (node == nullptr)
    return false;
  if (key == node->data)
    return true;
  else if (key < node->data)
    return search(node->left, key);
  else
    return search(node->right, key);
}

template <typename T>
void AVLTree<T>::inorder(AVLNode<T>* node, std::vector<T>& ret) const {
  if (node != nullptr) {
    inorder(node->left, ret);
    ret.push_back(node->data);
    inorder(node->right, ret);
  }
}


template <typename T>
void AVLTree<T>::insert(T key) {
  root = insert(root, key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
  root = remove(root, key);
}

template <typename T>
bool AVLTree<T>::search(T key) const {
  return search(root, key);
}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal() const {
  std::vector<T> result;
  inorder(root, result);
  return result;
}

template <typename T>
int AVLTree<T>::height() const {
  return height(root);
}

#endif
