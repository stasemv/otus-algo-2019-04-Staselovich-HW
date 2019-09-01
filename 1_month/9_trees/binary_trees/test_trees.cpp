#include "test_trees.h"

#include "avl_tree.h"
#include "splay_tree.h"

void test_trees()
{
    int stat_amount = 20;
    int iter_amount = 10;
    int start_items_amount = 512;
    double gain = 2;
    double del_part = 0.8;
    bool isPrint = 0;

    int items_amount = start_items_amount;
    FILE *fout = fopen("compare.xls","w");
    fprintf(fout, "start_amount \t%d\t\tstat_amount \t%d\n",
            start_items_amount, stat_amount);
    fprintf(fout, "gain \t%f\t\tdel_part \t%f\n",
            gain, del_part);
    fprintf(fout, "items_amount \tavl_time \t splay_time\n");
    for(int i=0; i < iter_amount;
        ++i, items_amount *= gain) {
        fprintf(fout, "%d\t", items_amount);

        double time;
        clsAVLTree<int> *avlTree = new clsAVLTree<int>();
        time = test_average_tree_time<clsAVLTree, int>(avlTree, "avl_tree",
                                                           items_amount, del_part,
                                                           isPrint, stat_amount);
        fprintf(fout, "%f\t", time);

        clsSplayTree<int> *splay_tree = new clsSplayTree<int>();
        time = test_average_tree_time<clsSplayTree, int>(splay_tree, "splay_tree",
                                                             items_amount, del_part,
                                                             isPrint, stat_amount);
        fprintf(fout, "%f\t", time);
        fprintf(fout, "\n");
    }
    fclose(fout);
}
