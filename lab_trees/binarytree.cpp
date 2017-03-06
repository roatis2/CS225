/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    // your code here
    //swap pointers as you go down


    //Node * t = root;
    mirrorHelp(root);
    //mirrorHelp(t->right);


}




template <typename T>
void BinaryTree<T>::mirrorHelp(Node *& subRoot)
{
        Node * t = subRoot; //declare var to hold the node in question
        Node * holder; //declare holder var for when we swap.
        if(t != NULL){
            //holder = t->right;
            //t->right = t->left;
            //t->left = holder;
            mirrorHelp(t->left); //do it on the right and left side
            mirrorHelp(t->right);

            holder = t->left; //switch pointers
            t->left = t->right;
            t->right = holder;
        }else{
            /*mirrorHelp(t->left); //do it on the right and left side
            mirrorHelp(t->right);

            holder = t->left; //switch pointers
            t->left = t->right;
            t->right = holder;
            */
            return;

        }



}


/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    //check to see if each L tree is less than the root and the R tree
    return isOrderedHelp(root); //call helper function on the root

    return false;
}

template <typename T>
bool BinaryTree<T>::isOrderedHelp(const Node* subRoot)const
{
    // your code here
    bool check = true; //start off true so that all unhandled cases can be true, such as right and left both equaling null
    //Node * t = subRoot; apparently cannot do this here?

    if(subRoot == NULL){ //check is subroot is null bc then it'd be ordered!
        check = true; //make check true
        return check; //return immediately so value does not change
    }
    if(subRoot->right != NULL){ //making sure it isnt null, bc then it could be false
        if(subRoot->right->elem > subRoot->elem){ //checks to make sure that the value of the one on the right of the current node is bigger than the one on the current
            check = true; // by not returning, gives opportunity to change
        }else{
            check = false;
        }

    }else{
        //check = true; cant put something here bc might change the value

    }
    if(subRoot->left != NULL){//same deal as the right one, here
        if(subRoot->left->elem < subRoot->elem){
            check = true;
        }else{
            check = false;
        }

    }else{
        //check = true;

    }
    bool right = isOrderedHelp(subRoot->right);
    bool left = isOrderedHelp(subRoot->left);

    return (right && left && check); //returns a value that recursively goes through the list and if any of the values are false it'll automatically return false, which is what we want



    //check to see if each L tree is less than the root and the R tree
    //return false;
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards,
 * ending at a leaf node. Paths ending in a left node should be printed before
 * paths ending in a node further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
    //vector <const BinaryTree<T>::Node *> trees;


    int trees[2195]; //declare array w number of slots as random amount
    printPathsHelp(root, trees, 0);
}

template <typename T>
void BinaryTree<T>::printPathsHelp(const Node* subRoot, int trees[], int counter) const
{
    //Node * t = subRoot; //pointer var to hold subroot
    if(subRoot != NULL){
        //return; //base case!

        trees[counter] = subRoot->elem; //put the value of the node in the next place in the array
        counter++; //move the place so that we will create an array of values
        if(subRoot->left == NULL && subRoot->right == NULL){ //print once we get to the very bottom
            cout << "Path: ";
            for(int k = 0; k < counter; k++){
                //cout << "Path: " << trees[k] << endl;
                cout << trees[k] << " ";

            }
            cout<<endl;
            counter = 0; //new pattern, don't want to be starting at the wrong place
        }else{
            printPathsHelp(subRoot->left, trees, counter); //run on the right and left NEED TO BE IN ORDER SO THAT WE DONT RETURN RESULTS FROM RIGHT TO LEFT!!!!
            printPathsHelp(subRoot->right, trees, counter);

        }
    }

}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return 10;
}
