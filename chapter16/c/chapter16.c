
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "chapter16.h"


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

struct keyValue TrieMap_first (const struct TrieMap *node)
{
  char curr_char, prev_char = '\0', min_char = '\0';
  const struct TrieMap *curr;
  int pos = -1;
  struct keyValue obj = {.key = "", .value = ""};

  while (node != curr)
  {
    curr = node;
    pos++;
    for (int i = 0; i < curr->children_size; i++)
    {
      curr_char = curr->children[i]->key[pos];
      if (min_char == '\0' || curr_char <= min_char)
      {
        node = curr->children[i];
        min_char = curr_char;
      }
    }
  }

  if (node)
  {
    obj.key = node->key;
    obj.value = node->string;
  }
  return obj;
}

struct keyValue TrieMap_last (const struct TrieMap *node)
{
  int pos = 0;
  char *curr_string, *max_string = "";
  const struct TrieMap *curr;
  struct keyValue obj = {.key = "", .value = ""};

  while (node != curr)
  {
    curr = node;
    pos++;

    for (int i = 0; i < curr->children_size; i++)
    {
      curr_string = curr->children[i]->key;
      if (max_string == "" || strncmp(curr_string, max_string, pos) >= 0 )
      {
        node = curr->children[i];
        max_string = curr_string;
      }
    }
  }

  if (node)
  {
    obj.key = node->key;
    obj.value = node->string;
  }
  return obj;
}

int main()
{

    struct TrieMap *trie = NULL;
    // Trie_add(&trie, "hello");
    // Trie_add(&trie, "hellor");

    TrieMap_add("first", "hello", &trie);
    // TrieMap_add("firs", "hell", &trie);
    // TrieMap_add("fir", "pick", &trie);

   struct keyValue object = TrieMap_last( trie);
    printf(" Object : key : %s  value: %s \n", object.key, object.value);
}