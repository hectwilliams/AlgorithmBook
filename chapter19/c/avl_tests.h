
#ifndef CHAPTER19_H
#define CHAPTER19_H

#include "chapter19.h"

#endif

void avl_remove_test_remove_x(int value);   /* AVL Remove tree tests  reference avl_remove slide 5+ */
void avl_remove_test_remove_x_y(int value0, int value1); //  delete two values
void avl_remove_test_remove_x_y_z(int value0, int value1, int value2); //  delete three values

void avl_rotate();


/* AVL Add balanced */
void balanced_add_test ();  // reference avl_balanced_add_remove.pdf

/* AVL Add balanced */
void balanced_remove_test ();  // reference avl_balanced_add_remove.pdf

/* AVL Repair test */
void repair_test ();  // reference avl_balanced_add_remove.pdf

  const int array[] = {
           100,
        50,       500,
      25,      450,        1000,
    20,     300,  480,   900,   2000,
   15,    200,          800
  };

  const int array2[] = {
    100, 50
  };


void addToTree (struct AVLTree **tree, const int *array, int size)
{
  for (int i = 0; i < size ; i++)
  {
    AVLTree_add(tree, array[i]);
  }
}

void avl_remove_test_remove_x(int value)
{
  struct AVLTree *tree = NULL;
  addToTree(&tree, array,  sizeof(array) / sizeof(int) );
  AVLTree_remove(&tree, value);
  display(tree);  // print inorder data (balance and value attributes )
}
void avl_remove_test_remove_x_y(int value0, int value1)
{
  struct AVLTree *tree = NULL;
  addToTree(&tree, array,  sizeof(array) / sizeof(int) );
  AVLTree_remove(&tree, value0);
  AVLTree_remove(&tree, value1);
  display(tree);  // print inorder data (balance and value attributes )
}
void avl_remove_test_remove_x_y_z(int value0, int value1, int value2)
{
  struct AVLTree *tree = NULL;
  addToTree(&tree, array,  sizeof(array) / sizeof(int) );
  AVLTree_remove(&tree, value0);
  AVLTree_remove(&tree, value1);
  AVLTree_remove(&tree, value2);
  display(tree);  // print inorder data (balance and value attributes )
}

void avl_test ()
{
  struct AVLTree *tree = NULL;
  addToTree(&tree, array2,  sizeof(array2) / sizeof(int) );
  AVLTree_remove(&tree, 100);
  display(tree);  // print inorder data (balance and value attributes )
}


// ROTATION

void avl_rotate()
{

    struct AVLTree *tree = NULL;
    AVLTree_add(&tree, 10);
    AVLTree_add(&tree, 15);
    AVLTree_add(&tree, 5);
    AVLTree_add(&tree, 3);
    AVLTree_add(&tree, 13);
    AVLTree_add(&tree, 13);
    AVLTree_add(&tree, 17);
    AVLTree_add(&tree, 16);
    AVLTree_add(&tree, 14);


    display(tree);  // print inorder data (balance and value attributes )
    AVLTree_leftRotate( &tree, tree->right);
    // AVLTree_rightRotate(&tree, tree->right);
    printf("\n");
    printf("current root  %d  %d    \n", tree->right->value, tree->right->right->value);
    display(tree);  // print inorder data (balance and value attributes )
}




void balanced_add_test ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 50 );
  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 300);
  AVLTree_add(&tree, 400);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 5 );
  AVLTree_add(&tree, 10);

  for (int i = 0; i < sizeof(array)/ sizeof(int) ; i++)
  {
    AVLTree_add(&tree, array[i]);
  }

  AVLTree_repair(&tree);  // repair tree

  display(tree);

}

void red_black_tree_test ()
{
  struct RBTreeObj *object = NULL;

  RBTree_add(&object, 3);
  RBTree_add(&object, 1);
  RBTree_add(&object, 5);
  RBTree_add(&object, 7);
  RBTree_add(&object, 6);
  RBTree_add(&object, 8);
  RBTree_add(&object, 9);
  RBTree_add(&object, 10);
  RBTree_add(&object, 12);
  RBTree_add(&object, 12333);
  RBTree_add(&object, 2);

  RBTree_remove(&object, 6);

  RBTree_display(object->root);


}