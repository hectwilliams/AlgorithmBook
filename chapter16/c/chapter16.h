
 enum boolean
{
  false,
  true
} boolean;


struct Trie
{
  const char *string;
  struct Trie **children;
  int children_size;
};


struct Trie * trie_allocate (const char *string, int size);
int Trie_add (struct Trie **tree, const char *str);
int Trie_contains(const char *str, const struct Trie **trie);
const char * Trie_first(const struct Trie **trie);
const char * Trie_last(const struct Trie **trie);
int Trie_remove(struct Trie *node, const char *word);
void Trie_remove_child(struct Trie *node, int index);
int Trie_size(struct Trie *node);
const char * Trie_next (const char * str, struct Trie *node );

struct TrieMulti
{
  int count;
  char *string;
  struct TrieMulti **children;
  int children_size;
};

struct TrieMulti * trie_multi_allocate (const char *string, int size);
void TrieMulti_add (struct TrieMulti **tree, const char *str);

int TrieMulti_remove(struct TrieMulti *node, const char *str);
int TrieMulti_size(struct TrieMulti *node);
int contains (const char * string, struct TrieMulti *node);

struct TrieMap
{
  char *key;
  char *string;
  struct TrieMap **children;
  int children_size;
};
void TrieMap_remove_child(struct TrieMap *node, int index);
void TrieMap_delete_children (struct TrieMap *node);

char * TrieMap_add(const char *key, const char *value, struct TrieMap **trie);
enum boolean TrieMap_remove(const char *key, struct TrieMap *node);
char *TrieMap_contains(const char *key , struct TrieMap *node);
int TrieMap_size(struct TrieMap *node);


struct keyValue
{
  const char *key;
  const char *value;
};

struct keyValue TrieMap_first (const struct TrieMap *node);
struct keyValue TrieMap_last (const struct TrieMap *node) ;
struct keyValue TrieMap_next (const char *key, const struct TrieMap *node);
