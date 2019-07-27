#include "test_trees.h"

//#include "binary_tree.h"
#include "avl_tree.h"

#include <stdio.h>

void test_trees()
{
    FILE *fout = stdout;
    fout = fopen("trees.txt", "w");
    clsAVLTree<int> *avlTree = new clsAVLTree<int>(1);
    for(int i=0; i < 10; ++i) {
        avlTree->insert(i);
        avlTree->printTree(fout, "tree", 1);
    }

    avlTree->printTree(fout, "tree_all", 1);

    avlTree->remove(0);
    avlTree->remove(5);
    avlTree->remove(1);
    avlTree->remove(6);
    avlTree->remove(8);
    avlTree->printTree(fout, "tree_del", 1);
    fclose(fout);
}
