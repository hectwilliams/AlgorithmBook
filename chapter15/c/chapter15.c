#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "chapter15.h"

struct BST *btnode_alloc(int value)
{
  struct BST *node = (struct BST *)malloc(sizeof(struct BST));
  node->value = value;
  node->parent = node->left = node->right = NULL;
  return node;
}

void BST_display(struct BST **tree)
{
  if (*tree)
  {
    if ((*tree)->left)
    {
      BST_display( &(*tree)->left);
    }

    printf(" %d |" , (*tree)->value);

    if ((*tree)->right)
    {
      BST_display( & (*tree)->right);
    }
  }
}

void BST_add(struct BST **tree, int value)
{
  struct BST *node = btnode_alloc(value);
  struct BST *curr = *tree;

  if (*tree == NULL)
  {
    *tree = node;
  }
  else
  {
    if (value < curr->value)
    {
      if (curr->left == NULL)
      {
        curr->left = node;
      }
      else
      {
        return BST_add( & curr->left,value);
      }
    }
    else
    {
      if (value >= curr->value)
      {
        if (curr->right == NULL)
        {
          curr->right = node;
        }
        else
        {
          BST_add(& curr->right, value);
        }
      }
    }
  }
}

int BST_height(struct BST **tree)
{
  int left = 0, right = 0;

  if ((*tree)->left)
  {
    left = 1 + BST_height( &(*tree)->left);
  }

  if ((*tree)->right)
  {
    right = 1 + BST_height( &(*tree)->right);
  }

  return left == right ? right : left;
}

struct BST * BST_remove_successor(struct BST **tree)
{
  struct BST *node = *tree;
  struct BST *prev = node;

  if (node->right)
  {
    node = node->right;
    while (node->left)
    {
      prev = node;
      node = node->left;
    }
  }

  if (prev->left == node)
  {
    prev->left = NULL;
  }
  else
  {
    prev->right = NULL;
  }
  return node;
}

void BST_remove(struct BST **tree, int value)
{
  static struct BST *prev = NULL, *succesor;

  if (*tree == NULL)
  {
    return;
  }

  if ( (*tree)->value == value )
  {
    if (!! (*tree)->left && !!(*tree)->right)
    {

    // find successor
      succesor = BST_remove_successor(tree);

    // link successor
        succesor->left = (*tree)->left;
        succesor->right= (*tree)->right;

    // update root node
      if (prev ==NULL)
      {
        *tree = succesor;
      }
    // update subtree
      else
      {
        if (prev->left == *tree)
        {
          prev->left = succesor;
        }
        else
        {
          prev->right = succesor;
        }
      }
    }
    else if ( !!(*tree)->left ^ !!(*tree)->right )
    {
      if (prev == NULL)
      // update root
      {
        if ((*tree)->left == NULL)
        {
          *tree = (*tree)->right;
        }
        else
        {
          *tree = (*tree)->left;
        }
      }
      else
      // update subtree
      {
        if (prev->left == *tree)
        {
          if ((*tree)->left == NULL)
          {
            prev->left = (*tree)->right;
          }
          else
          {
            prev->left = (*tree)->left;
          }
        }
        else if (prev->right == *tree)
        {
          if ((*tree)->left == NULL)
          {
            prev->right = (*tree)->right;
          }
          else
          {
            prev->right = (*tree)->left;
          }
        }
      }
    }
    else if ( (*tree)->left == NULL && (*tree)->right == NULL)
    {
      if (prev == NULL)
      {
        *tree = NULL;
      }
      else
      {
        if (prev->left == *tree)
        {
          prev->left = NULL;
        }

        else
        {
          prev->right = NULL;
        }
      }
    }
  }

  if (*tree)
  {
    if ((*tree)->left)
    {
      if ( value < (*tree)->value)
      {
        prev = *tree;
        BST_remove(&(*tree)->left, value);
      }
    }

    if ((*tree)->right)
    {
      if (value >= (*tree)->value)
      {
        prev = *tree;
        BST_remove(&(*tree)->right, value);
      }
    }
  }

  prev = NULL;
}


enum boolean BST_Full(struct BST **tree)
{
  enum boolean isFull = false;

  if ((*tree))
  {
    isFull = ( (*tree)->left && (*tree)->right ) ^ ((*tree)->left == NULL && (*tree)->right == NULL);
    printf("\n[%d]\n", isFull);
    if ((*tree)->left)
    {
      isFull &= BST_Full (&(*tree)->left);
    }

    if ((*tree)->right)
    {
     isFull &=  BST_Full (&(*tree)->right);
    }
  }
  return isFull;
}

enum boolean BST_Complete(struct BST **tree)
{

  enum boolean isComplete = false ;
  int left = 0, right = 0;
  struct BST *node = *tree;

  if (node)
  {

    if (node->left)
    {
      left = BST_height(&node->left);
    }

    if (node->right)
    {
      right = BST_height(&node->right) ;
    }

    isComplete = left >= right;

    if (node->left)
    {
      isComplete &= BST_Complete(&node->left);
    }

    if (node->right)
    {
     isComplete &=  BST_Complete(&node->right);
    }
  }

  return isComplete;
}

void BST_addNode (struct BST *node, struct BST **tree)
{
  if (*tree == NULL)
  {
    *tree = node;
  }
  else if (node)
  {

    if (node->value < (*tree)->value)
    {
      if ((*tree)->left)
      {
        BST_addNode(node, & (*tree)->left);
      }
      else
      {
        (*tree)->left = node;
      }
    }

    else
    {
      if ((*tree)->right)
      {
        BST_addNode(node, & (*tree)->right);
      }
      else
      {
        (*tree)->right = node;
      }
    }
  }
}

void bstRepairReinsert(struct BST *src, struct BST **dest)
{
  /* pre traversal iterates each node */

  struct BST *node = src, *reinsert  = NULL;

  if (node)
  {

    if (node->left)
    {
      reinsert = node->left;
      node->left = NULL;
      bstRepairReinsert(reinsert, dest);
    }

    if (node->right)
    {
      reinsert = node->right;
      node->right = NULL;
      bstRepairReinsert( reinsert, dest);
    }

    BST_addNode(node, dest);
  }
}

enum boolean bstRepair(struct BST **tree)
{
  static struct BST *root = NULL;
  struct BST *node = *tree, *reinsertionNode = NULL;
  enum boolean repaired =  false;

  if (root == NULL)
  {
    root = *tree;
  }

  if (node)
  {
    if (node->left)
    {
      if (node->left->value >= node->value)
      {
        repaired = true;
        reinsertionNode = node->left;
        node->left = NULL;
        bstRepairReinsert(reinsertionNode, &root);
      }
    }

    if (node->right)
    {
      if (node->right->value < node->value)
      {
        repaired = true;
        reinsertionNode = node->right;
        node->right = NULL;
        bstRepairReinsert(reinsertionNode, &root);
      }
    }

    if (node)
    {
      if (node->left)
      {
        repaired |= bstRepair (&node->left);
      }

      if (node->right)
      {
        repaired |= bstRepair (&node->right);
      }
    }
  }

  root = NULL;
  return repaired;
}

int BST_smallest_difference(struct BST **tree)
{
  struct BST *node = *tree;
  static int currMin = __INT_MAX__;

  if (node)
  {
    if (node->left)
    {
      if ( abs(node->value - node->left->value)  < currMin) {
        currMin = abs(node->value - node->left->value);
      }
      BST_smallest_difference(&node->left);
    }

    if (node->right)
    {
      if ( abs(node->value - node->right->value)  < currMin) {
        currMin = abs(node->value - node->right->value);
      }
      BST_smallest_difference(&node->right);
    }
  }
  return currMin;
}

struct BST *partition_around_value(int value, struct BST **tree)
{
  static struct BST *prev = NULL;
  struct BST *node = *tree;
  struct BST *result = NULL;

  if (node)
  {
    if (value < node->value)
    {
      if (node->left)
      {
        prev = node;
        return partition_around_value(value, &node->left);
      }
      else
      {
        result = node;
      }
    }
    else if (value > node->value)
    {
      if (node->right )
      {
        prev = node;
        return partition_around_value(value, &node->right);
      }
      else
      {
        result = node;
      }
    }
    else
    {

      // prev enabled
      if (prev)
      {
        if (prev->left == node)
        {
          result = node;
          prev->left = NULL;
        }

        if (prev->right == node)
        {
          result = node;
          prev->right = NULL;
        }
        return result;
      }
      else
      {
        result = node;
        *tree = NULL;
      }
    }

  }

  prev = NULL;
  return result;
}

struct BST *partition_evenly (struct BST **tree)
{
  struct BST *result = NULL;
  static struct BST *head = NULL;
  static struct BST *buffer0 = NULL;
  static struct BST *buffer1 = NULL;
  struct BST *node = *tree;
  static int count = 0;

  if (!head)
  {
    head = *tree;
  }

  if (node)
  {
    if (node->left)
    {
      partition_evenly(&node->left);
      node->left = NULL;
      count = !count;
    }
    if (node->right)
    {
      partition_evenly(&node->right);
      node->right = NULL;
      count = !count;
    }
    if (count % 2 == 0)
    {
      BST_addNode(node, &buffer0);
    }
    else
    {
      BST_addNode(node, &buffer1);
    }
  }

  if (*tree == head)
  {
    result = buffer0;
    *tree = buffer1;
    head = NULL;
    buffer0 = NULL;
    buffer1 = NULL;
  }

  return result;
}

void BST_reverse (struct BST **tree)
{
  struct BST *node = *tree;
  struct BST *left, *right;

  if (node)
  {
    left = (node->left);
    right = (node->right);

    node->left = right;
    node->right = left;

    if (node->left)
    {
      BST_reverse(&node->left);
    }

    if (node->right)
    {
      BST_reverse(&node->right);
    }
  }
}

int BST_kthBiggest(struct BST **tree, int k)
{
  struct BST *node = *tree;
  static int count = 0;
  int result = 0;

  if (node)
  {
    if (node->right)
    {
      result |= BST_kthBiggest(&node->right, k);
    }

    count++;

    if (k == count)
    {
      printf("[%d]", node->value);
      result |= node->value;
    }

    if (node->left)
    {
      result |= BST_kthBiggest(&node->left, k);
    }
  }
  count = 0;
  return result;
}

void BST_print_value_for_layer(struct BST **tree, int layer)
{
  struct LL *llist = (struct LL *) malloc(sizeof(struct LL));
  struct LL *runner;
  int currDepth;

  llist->node = (struct BST *) *tree;
  llist->next = NULL;
  llist->depth = 0;

  while (llist)
  {
    currDepth =llist->depth ;

    if (llist->depth == layer)
    {
      printf(" [%d] \n",  ((struct BST *)llist->node)->value );
    }

    if ( ((struct BST *) llist->node)->left )
    {
      runner = llist;
      while(runner->next)
      {
        runner = runner->next;
      }
      runner->next = (struct LL *) malloc(sizeof(struct LL));
      runner->next->node = ((struct BST *) llist->node)->left;
      runner->next->next = NULL;
      runner->next->depth = currDepth + 1;
    }

    if ( ((struct BST *) llist->node)->right )
    {
      runner = llist;
      while(runner->next)
      {
        runner = runner->next;
      }
      runner->next = (struct LL *) malloc(sizeof(struct LL));
      runner->next->node = ((struct BST *) llist->node)->right;
      runner->next->next = NULL;
      runner->next->depth = currDepth+ 1;
    }
    llist = llist->next;
  }
}

struct Trie * trie_allocate (const char *string, int size)
{
  struct Trie *node =  (struct Trie *) malloc( sizeof(struct Trie) );
  char *buffer = (char *) malloc(sizeof(char) * size + 1);

  // printf("[%s]  [%d]\n", string, size);

  strncpy(buffer, string, size);
  // lowercase
  for (int i = 0 ; i < size; i++)
  {
    buffer[i] = tolower(buffer[i]);
  }
  node->string = buffer;
  node->children_size = 0;
  node->children = (struct Trie **) malloc( sizeof(struct Trie *) * node->children_size  );
  return node;
}

int Trie_add (struct Trie **tree, const char *str)
{
  struct Trie *node, *curr;
  int pos = 0;
  int result = 0;
  char lower_str[50] = "";

  if (*tree == NULL)
  {
    *tree = trie_allocate("", 1);
  }

  // lowercase input string
  for (int i = 0; *(str + i); i++)
  {
    lower_str[i] = tolower( *(str + i ) );
  }

  node = *tree;

  while (str[pos])
  {
    pos++;
    curr = node;

    for (int i = 0; i < node->children_size; i++)
    // iterate children
    {
      if ( strncmp(  node->children[i]->string, lower_str , pos) == 0 )
      // enter new node
      {
        node = node->children[i];
        break;
      }
    }

    if (curr == node)
    // insert trie node
    {
      result = result || 1;
      node->children_size++;
      node->children = realloc(node->children, sizeof(struct Trie *) * node->children_size  );
      node->children [ node->children_size - 1 ] = trie_allocate(str, pos);
      node =  node->children [ node->children_size - 1 ];
    }
  }
  return result;
}

int Trie_contains(const char *str, const struct Trie **trie)
{
  const struct Trie *node, *curr ;
  int pos = 0;
  char lower_str[50] = "";

  if (*trie == NULL)
  {
    return 0;
  }

  node = *trie;

  for (int i = 0; *(str + i); i++)
  {
    lower_str[i] = tolower(*(str++));
  }

  while (node != curr)
  {
    curr = node;
    for (int i  = 0; i < node->children_size; i++)
    {
      if ( strncmp(node->children[i]->string , lower_str, pos + 1 )  == 0)
      {
        node = node->children[i];
        pos++;
        break;
      }
    }
  }
  return pos == strlen(str);
}

const char * Trie_first(const struct Trie **trie)
{
  const struct Trie *node = *trie, *curr;
  static char buffer[50] = "";
  int pos = 0;
  char curr_char, prev_char = '\0', min_char = '\0';

  if (node == NULL)
  {
    return "";
  }

  while (node != curr)
  {
    curr = node;
    for (int i = 0; i < curr->children_size; i++)
    {
      curr_char = curr->children[i]->string[pos];
      if (min_char == '\0' || curr_char <= min_char)
      {
        node  = curr->children[i];
        min_char = curr_char;
      }
    }
    pos++;
  }
  memset(buffer, '\0', 50);
  memcpy(buffer, node->string, strlen(node->string));
  return buffer;
}

const char * Trie_last(const struct Trie **trie)
{
  const struct Trie *node = *trie, *curr;
  static char buffer[50] = "";
  int pos = 0;
  char * curr_string = "", *max_string = "";

  if (node == NULL)
  {
    return "";
  }

  while (node != curr)
  {
    curr = node;
    pos++;

    for (int i = 0; i < curr->children_size; i++)
    {
      curr_string = curr->children[i]->string;

      if (max_string == "" || strncmp(curr_string, max_string, pos) >= 0)
      {
        node  = curr->children[i];
        max_string = curr_string;
      }
    }
  }
  memset(buffer, '\0', 50);
  memcpy(buffer, node->string, strlen(node->string));
  return buffer;
}

void Trie_remove_child(struct Trie *node, int index)
{
  node->children[index] = NULL;
  for (int j = index; j < node->children_size - 1; j++)
  {
    node->children[j] = node->children[j + 1];
  }
  --node->children_size;
}

int Trie_remove(struct Trie *node, const char *word)
{
  int found = 0;

  if (node == NULL)
  {
    return 0 ;
  }

  if (strncmp(word, node->string, strlen(word)) == 0)
  {
    return 1;
  }

  for (int i = 0; i < node->children_size && !found; i++)
  {
    if (strstr(word, node->children[i]->string) == word)
    {
      found |= Trie_remove( node->children[i] , word);

      if (found == 1)
      {
        /* delete node */
        if (strncmp(word, node->children[i]->string, strlen(word)) == 0)
        {
          Trie_remove_child(node, i);
        }
        else if (node->children_size == 1)
        {
          if (node->children[0]->children_size == 0 )
          {
            Trie_remove_child(node, 0);
            node->children = NULL;
          }
        }
      }
    }
  }

  return found;
}

int Trie_size(struct Trie *node)
{

  int count = 0;

  if (node->children_size == 0)
  {
    return 0;
  }

  if (node)
  {
    for (int i = 0; i < node->children_size; i++)
    {
      count +=  +(strlen(node->string) > 0) + Trie_size(node->children[i]);
    }
  }
  return count;
}

const char * Trie_next (const char * str, struct Trie *node )
{
   const char *next =  NULL;

  for (int i = 0; i < node->children_size ; i++)
  {
    if (strstr(str, node->children[i]->string ) )
    {
      return Trie_next(str, node->children[i]);
    }
  }

  // find min char
  for (int i = 0; i < node->children_size; i++)
  {
    if (next == NULL || strcmp(node->children[i]->string, next) < 0)
    {
      next = node->children[i]->string;
    }
  }
  return next;
}

struct TrieMulti * trie_multi_allocate (const char *string, int size)
{
  struct TrieMulti *node = (struct TrieMulti *) malloc(sizeof(struct TrieMulti));
  node->string = (char *) malloc (sizeof(char) * (size + 1) );

  for (int i = 0; i < size ; i++)
  {
    node->string[i] = tolower(string[i]);
  }
  // init vars
  node->count = 0;
  node->children_size = 0;
  node->children = (struct TrieMulti **) malloc( sizeof(struct TrieMulti *) * node->children_size  );
  return node;
}

void TrieMulti_add (struct TrieMulti **tree, const char *str)
{
  struct TrieMulti *node , *curr;
  int pos = 0;

  if (*tree == NULL)
  {
    *tree = trie_multi_allocate("", 1);
  }

  node = *tree;

  if (node == NULL)
  {
    return;
  }

  while ( str[pos] )
  {
    pos++;
    curr = node;


    for (int i = 0; i < node->children_size; i++)
    {
      if ( strncmp(node->children[i]->string, str,  pos) == 0  )
      // substring found  (increment node)
      {
        node = node->children[i];
        node->count++;
        break;
      }
    }

    if (curr == node)
    // new entry
    {
      node->children_size++;
      node->children = realloc(node->children, sizeof(struct TrieMulti *) * node->children_size  );
      node->children [ node->children_size - 1 ] = trie_multi_allocate(str, pos);
      node =  node->children [ node->children_size - 1 ];
      node->count++;
    }

  }
}

void TrieMulti_remove_child (struct TrieMulti *node, int index)
{
  if (node->children[index])
  {
    node->children[index] = NULL;
    for (int j = index; j < node->children_size - 1; j++)
    {
      node->children[j] = node->children[j + 1];
      node->children[j + 1] = NULL;
    }
    --node->children_size;
  }
}

int TrieMulti_remove(struct TrieMulti *node, const char *str)
{
  int pos = 0;
  int  found = 0;
  struct TrieMulti *curr;

  if (!node)
  {
    return false;
  }

  if (strncmp(node->string, str, strlen(str)) == 0)
  {
    return 1;
  }

  for (int i = 0 ; i < node->children_size && !found; i++)
  {
    if (strstr (str, node->children[i]->string ) == str )
    {
      found =  TrieMulti_remove(node->children[i], str);

      if (found == 1)
      {
        if (node->count > 1)
        {
          node->count--;
        }
        else if (node->count == 1)
        {
          if (strncmp(str, node->children[i]->string, strlen(str)) == 0)
          {
            TrieMulti_remove_child(node, i);
          } else if (node->children_size == 1)
          {
            if (node->children[0]->children_size == 0 )
            {
              TrieMulti_remove_child(node, 0);
              node->children = NULL;
            }

          }
        }
      }
    }
  }
  return found;
}

int TrieMulti_size(struct TrieMulti *node)
{
  int count = 0;

  if (!node)
  {
    return 0;
  }

  if (node)
  {
    count += node->count;
  }

  for (int i = 0; i < node->children_size; i++)
  {
    count +=  TrieMulti_size(node->children[i]);
  }

  return count;
}

int contains (const char * string, struct TrieMulti *node)
{
    if (node)
  {
    if ( strncmp(string, node->string, strlen(string))  == 0)
    {
      return node->count;
    }

    for (int i = 0; i < node->children_size; i++)
    {
      if ( strstr (string, node->children[i]->string) == string )
      {
        return contains(string, node->children[i]);
      }
    }
  }
  return 0;
}

struct TrieMap * trie_map_allocate (const char *key, int key_len, const char *value, int value_len )
{
  struct TrieMap *node = (struct TrieMap *) malloc( sizeof(struct TrieMap) );
  int keySize = key_len + 1;
  int valueSize = value_len + 1;

  node->string = (char *) malloc(keySize + 1);
  node->key = (char *) malloc(valueSize + 1);

  //lower case string
  for (int i = 0; i < key_len; i++)
  {
    node->key[i] = tolower(key[i]);
  }
  for (int i = 0; i < value_len; i++)
  {
    node->string[i] = tolower(value[i]);
  }

  //init remaining fields
  node->children_size = 0;
  node->children = (struct TrieMap **) malloc( sizeof(struct TrieMap *) * node->children_size);

  return node;
}

char * TrieMap_add(const char *key, const char *value, struct TrieMap **trie)
{
  int pos = 0;
  struct TrieMap *curr, *node = *trie;

  char * val = NULL;

  if (*trie == NULL)
  {
    *trie = trie_map_allocate("", 0, "", 0);
  }
  node = *trie;

  while (key[pos])
  {
    curr = node;
    pos++;

    for (int i = 0; i < node->children_size; i++)
    {
      if ( strncmp(key, node->children[i]->key, pos) == 0)
      {
        node = node->children[i];
        break;
      }
    }

    if (strncmp(key, node->key, strlen(key)) == 0)
    {
        val = node->string;
        node->string = value;
        return val;
    }

    if (curr == node)
    {
      node->children_size++;
      node->children = realloc(node->children, sizeof(struct TrieMap *) * node->children_size );
      node->children[node->children_size - 1] = trie_map_allocate(key, pos, "", 0);
      node = node->children[node->children_size - 1];
      if (strncmp(key, node->key, strlen(key))  == 0)
      {
        node->string = value;
      }
    }
  }
  return val;
}

void TrieMap_delete_children (struct TrieMap *node)
{
  for (int i = 0; i < node->children_size; i++)
  {
    TrieMap_delete_children(node->children[i]);
    printf("delete children [ %s | %s ] ", node->key, node->string);
    free(node->children[i]);
  }

  //remove subtree
  if (node->children)
  {
    free(node->children );
    node->children_size = 0;
    node->children = NULL;
  }
}

void TrieMap_remove_child(struct TrieMap *node, int index)
{
    printf("deleting child of  [ %s | %s  %d ] \n", node->key, node->string, node->children_size);

    // deletes substree
    if (node->children)
    {

      TrieMap_delete_children (node->children[index]);

      // deletes node link to child
      free (node->children[index]);
      node->children[index] = NULL;
      --node->children_size;

      for (int j = index; j <  node->children_size; j++)
      {
        node->children[j] = node->children[j + 1];
        node->children[j + 1] = NULL;
      }
    }
}

enum boolean TrieMap_remove(const char *key, struct TrieMap *node)
{
  int found = 0;
  if (node == NULL)
  {
    return 0;
  }

  if (strncmp(key, node->key, strlen(key)) == 0)
  {
    return 1;
  }

  for (int i = 0; i < node->children_size; i++)
  {
    if (strstr(key, node->children[i]->key) == key)
    {
      found |= TrieMap_remove(key, node->children[i]);

      if (found)
      {
        if (strncmp(key, node->children[i]->key, strlen(key)) == 0 )
          // remove node
        {
          TrieMap_remove_child(node, i);
        }
        else if (node->children_size == 1)
        {
          if (node->children[0]->children_size == 0 && strlen(node->children[0]->string) == 0 )
          {
            TrieMap_remove_child(node, 0);
          }
        }
      }
    }
  }
  return found;
}

char *TrieMap_contains(const char *key , struct TrieMap *node)
{
  if (!node)
  {
    return "";
  }

  if (strncmp(key, node->key, strlen(key)) == 0 )
  {
    return node->string;
  }

  for (int i = 0; i < node->children_size; i++)
  {
    if (strstr(key, node->children[i]->key) ==  key)
    {
      return TrieMap_contains(key, node->children[i]);
    }
  }
  return "";
}

int TrieMap_size(struct TrieMap *node)
{
  int count = 0;

  for (int i = 0; i < node->children_size; i++)
  {
    count += 1 +  TrieMap_size(node->children[i]);
  }
  return count;

}

int main()
{
  // struct BST *bst = NULL;
  // BST_add(&bst, 32);
  // BST_add(&bst, 17);
  // BST_add(&bst, 28);
  // BST_add(&bst, 23);
  // BST_add(&bst, 29);
  // BST_add(&bst, 49);
  // BST_add(&bst, 2);

  // // BST_display(&bst);
  // // printf("\n") ;
  // // BST_display(&bst);
  // // bst->left->right->value = 1;
  // // printf(" \nis complete - %d \n ", bstRepair(&bst) );
  // // BST_display(&bst);
  // // printf("outcome %d\n", BST_smallest_difference(&bst));
  // // printf("\n\n\n\n");

  // // BST_display(&bst);
  // // printf("\n");
  // // BST_reverse(&bst);
  // // BST_kthBiggest(&bst, 3);
  // printf("\n\n");
  // BST_print_value_for_layer(&bst, 1);

    struct TrieMap *trie = NULL;
    // Trie_add(&trie, "hello");
    // Trie_add(&trie, "hellor");

    TrieMap_add("first", "hello", &trie);
    // TrieMap_add("firs", "hell", &trie);
    // TrieMap_add("fir", "pick", &trie);

    int c= TrieMap_size( trie);
    printf(" Size: %d\n", c);
    // TrieMulti_add(&trie, "hello");
    // TrieMulti_add(&trie, "hellor");

    // printf("[%d]\n", TrieMulti_size(trie));
    // printf(" \n contains %d \n", contains("hello", trie));

    // printf("%d\n", Trie_contains("hellor", &trie));


    // printf("data = %s\n", data);

}
