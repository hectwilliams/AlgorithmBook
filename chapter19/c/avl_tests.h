
#ifndef CHAPTER19_H
#define CHAPTER19_H

#include "chapter19.h"

#endif

/* AVL Remove tree tests */

//  remove node with 1 child

void avl_remove_single_child_node_a ();  // avl_remove_balanced/index.html  slide 5
void avl_remove_single_child_node_b ();  // avl_remove_balanced/index.html   slide 6
void avl_remove_single_child_node_c ();  // avl_remove_balanced/index.html    slide 7

//  remove node with 0 children
void avl_remove_zero_children_node_a ();  // avl_remove_balanced/index.html  slide 19
void avl_remove_zero_children_node_b ();  // avl_remove_balanced/index.html  slide 20
void avl_remove_zero_children_node_c ();  // avl_remove_balanced/index.html  slide 21

// remove node with 2 children
void avl_remove_full_node_a (); // avl_remove_balanced/index.html slide 14
void avl_remove_full_node_b (); // avl_remove_balanced/index.html slide 15
void avl_remove_full_node_c (); // avl_remove_balanced/index.html slide 16
void avl_remove_full_node_d (); // avl_remove_balanced/index.html slide 17
void avl_remove_full_node_e (); // avl_remove_balanced/index.html slide 18
void avl_remove_full_node_f (); // avl_remove_balanced/index.html slide 19



void avl_remove_single_child_node_a ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 50);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 70);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

  /*
    inOrder list:

  prior to removal:
    [val - 25  bal - 0 ]
    [val - 50  bal - 0 ]
    [val - 70  bal - 0 ]
    [val - 100 bal - 2 ]

  after  removal:
    [val - 25  bal - 0 ]
    [val - 50  bal - 0 ]
    [val - 70  bal - 0 ]

  */
}

void avl_remove_single_child_node_b ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 50);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 27);
  AVLTree_add(&tree, 16);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 50);
  display(tree);


  /*
  prior to removal:
    [val - 16  bal - 0 ]
    [val - 25  bal - 0 ]
    [val - 27  bal - 0 ]
    [val - 50  bal - 2 ]
    [val - 100  bal - 3 ]

  after  removal:
    [val - 16  bal - 0 ]
    [val - 25  bal - 0 ]
    [val - 27  bal - 0 ]
    [val - 100  bal - 2 ]
  */

}
void avl_remove_single_child_node_c ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 500);
  AVLTree_add(&tree, 700);
  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 50);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 27);
  AVLTree_add(&tree, 16);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 50);
  display(tree);

/*

  prior to removal:
    [val - 16  bal - 0 ]
    [val - 25  bal - 0 ]
    [val - 27  bal - 0 ]
    [val - 50  bal - 2 ]
    [val - 200  bal - 3 ]
    [val - 500  bal - 3 ]
    [val - 700  bal - 0 ]

  after  removal:
   [val - 16  bal - 0 ]
   [val - 25  bal - 0 ]
   [val - 27  bal - 0 ]
   [val - 200  bal - 2 ]
   [val - 500  bal - 2 ]
   [val - 700  bal - 0 ]

*/

}

void avl_remove_zero_children_node_a ()
{
 struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 100);
  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);
/*

  prior to removal:
    [val - 100  bal - 0 ]

  after  removal:

*/

}

void avl_remove_zero_children_node_b ()
{
  struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 25);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 25);
  display(tree);

/*
  prior to removal:
    [val - 25  bal - 0 ]
    [val - 100  bal - 1 ]

  after  removal:
    [val - 100  bal - 0 ]
*/
}

void avl_remove_zero_children_node_c ()
{
  struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 25);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 25);
  display(tree);

  /*

  prior to removal:
    [val - 25  bal - 0 ]
    [val - 100  bal - 1 ]
    [val - 200  bal - 2 ]

  after  removal:
    [val - 100  bal - 0 ]
    [val - 200  bal - 1 ]
  */

}


void avl_remove_full_node_a ()
{
  struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 120);
  AVLTree_add(&tree, 25);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

  /*
  prior to removal:
    [val - 25  bal - 0 ]   [val - 100  bal - 0 ]   [val - 120  bal - 0 ]

  after  removal:
    [val - 25  bal - 0 ]   [val - 120  bal - 1 ]
  */
}


void avl_remove_full_node_b ()
{
  struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 120);
  AVLTree_add(&tree, 25);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

  /*

  prior to removal:
    [val - 25  bal - 0 ]
    [val - 100  bal - 0 ]
    [val - 120  bal - 0 ]
    [val - 200  bal - 2 ]

  after  removal:
    [val - 25  bal - 0 ]
    [val - 120  bal - 1 ]
    [val - 200  bal - 2 ]
  */
}

void avl_remove_full_node_c ()
{
  struct AVLTree *tree = NULL;
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 120);
  AVLTree_add(&tree, 140);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

  /*
    prior to removal:
      [val - 25  bal - 0 ]
      [val - 100  bal - -1 ]
      [val - 120  bal - -1 ]
      [val - 140  bal - 0 ]

    after  removal:
      [val - 25  bal - 0 ]
      [val - 120  bal - 0 ]
      [val - 140  bal - 0 ]
  */
}

void avl_remove_full_node_d ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 120);
  AVLTree_add(&tree, 140);
  AVLTree_add(&tree, 110);


  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

    /*

    prior to removal:
      [val - 25  bal - 0]
      [val - 100  bal - -1]
      [val - 110  bal - 0]
      [val - 120  bal - 0]
      [val - 140  bal - 0]
      [val - 200  bal - 3]

    after removal:
      [val - 25  bal - 0 ]
      [val - 110  bal - -1]
      [val - 120  bal - -1]
      [val - 140  bal - 0]
      [val - 200  bal - 3]

    */
}

void avl_remove_full_node_e ()
{
  struct AVLTree *tree = NULL;

  AVLTree_add(&tree, 200);
  AVLTree_add(&tree, 100);
  AVLTree_add(&tree, 25);
  AVLTree_add(&tree, 120);
  AVLTree_add(&tree, 110);
  AVLTree_add(&tree, 140);
  AVLTree_add(&tree, 105);

  display(tree);
  printf("\n");
  AVLTree_remove(&tree, 100);
  display(tree);

 /*
    prior to removal:
      [val - 25  bal - 0]
      [val - 100  bal - -2]
      [val - 105  bal - 0 ]
      [val - 110  bal - 1 ]
      [val - 120  bal - 1 ]
      [val - 140  bal - 0 ]
      [val - 200  bal - 4 ]

    after removal:
      [val - 25  bal - 0]
      [val - 105  bal - -1]
      [val - 110  bal - 0 ]
      [val - 120  bal - 0 ]
      [val - 140  bal - 0 ]
      [val - 200  bal - 3 ]
*/
}

