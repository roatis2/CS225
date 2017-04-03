/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    /*pointer manipulation*/
    Node * temp = t->right;
    t->right = temp->left;
    temp->left = t;
    /*update heights for temp and t*/
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    /*update t ptr*/
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    /*pointer manipulation*/
    Node * temp = t->left;
    t->left = temp->right;
    temp->right = t;
    /*update heights for temp and t*/
    t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    temp->height = max(heightOrNeg1(temp->left), heightOrNeg1(temp->right)) + 1;
    /*update t ptr*/
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    /*left rotations*/
    if(getBalance(subtree) == 2){
      if(getBalance(subtree->right) == 1)
        rotateLeft(subtree);
      else
        rotateRightLeft(subtree);
      }
    /*right rotations*/
    else if(getBalance(subtree) == -2){
      if(getBalance(subtree->left) == -1)
        rotateRight(subtree);
      else
        rotateLeftRight(subtree);
    }
}

/*helper function for rebalance*/
template <class K, class V>
int AVLTree<K, V>::getBalance(Node*& subtree)
{
  if(subtree == NULL)
    return 0;
  return heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL)
      subtree = new Node(key, value);
    /*insert left*/
    else if(key < subtree->key){
      insert(subtree->left, key, value);
      rebalance(subtree);
    }
    /*insert right*/
    else if(key > subtree->key){
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
    /*update height*/
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    /*key to be deleted is less than root*/
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    }
    /*key to be delete is greater than root*/
    else if (key > subtree->key)
    {
        // your code here
        remove(subtree->right, key);
    }
    /*found node to remove*/
    else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            noChildRemove(subtree);

        }
        else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            twoChildRemove(subtree);

        }
        else {
            /* one-child remove */
            // your code here
            oneChildRemove(subtree);


        }
        if (subtree == NULL)
            return;
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    rebalance(subtree);
}

/*from notes*/
template <class K, class V>
void AVLTree<K, V>::noChildRemove(Node* & subRoot){
  Node * temp = subRoot;
  subRoot = NULL;
  delete temp;
}

/*from lecture notes*/
template <class K, class V>
void AVLTree<K, V>::oneChildRemove(Node* & subRoot){
  Node * temp = subRoot;
  if(subRoot->left == NULL)
    subRoot = subRoot->right;
  else if(subRoot->right == NULL)
    subRoot = subRoot->left;
  delete temp;
}

/*from lecture notes*/
template <class K, class V>
void AVLTree<K, V>::twoChildRemove(Node* & subRoot){
  Node * iop = subRoot->left;
  while(iop->right != NULL)
    iop = iop->right;
  swap(subRoot, iop);
  remove(subRoot->left, iop->key);
}
