#ifndef CHAPTER8_H
#define CHAPTER8_H

template <class T>
struct ret_obj {
  bool valid;
  T value;
};

template <class T>
class SLNode_t 
{
  public:
  /*structure methods */
    SLNode_t <T> *next;
    SLNode_t <T> *child;

    T value;
  /*constructor*/
    SLNode_t <T> ( const T &val): value{val}, next{NULL} {}
};

template <class T>
SLNode_t <T> *sl_node(const T &value);

template <class T>
class SList_t {
public:
  SLNode_t <T> *head;
  SLNode_t <T> *tail;
  SList_t<T>(): head{NULL}, tail{NULL} {}
  void pushFront(const T &value);
  ret_obj<T> popFront();
  void pushBack(const T &value);
  ret_obj<T> popBack();
  bool contains(const T &value);
  bool removeValue(const T &value);
  void display();

  void reverse (SList_t<T> *list = NULL);
  bool isPalindrome();
  ret_obj<T> kthLastNode(SList_t *list, unsigned int n);
  void shiftRight(int n );
  void shiftLeft(int n);
  SList_t<T> *sum_numerals (SList_t<T> *a, SList_t<T>* b, bool least_sig_digit_first = true);
  SList_t<T> *setupLoop(unsigned int count, unsigned int loop_pos);
  bool hasLoop();
  SLNode_t<T> *loopStart();
  void breakLoop();
  unsigned int nodeCount();
  void swapPairs();
  void flattenChildren(); 
  void unflattenChildren();
};

template <class T>
SList_t <T> *sl_list();

template <class T>
class DLNode_t 
{
  public:
  /*structure methods */
    DLNode_t <T> *next, *prev;
    DLNode_t <T> *child;
    T value;
  /*constructor*/
    DLNode_t <T> ( const T &val): value{val}, next{NULL}, prev{NULL} {}
};


template <class T>
class DList_t {
  DLNode_t<T> *head, *tail;
  public:
  DList_t<T> (): head{NULL}, tail{NULL} {}
  void push(const T &value);
  ret_obj<T> pop(void);
  ret_obj<T> front(void);
  ret_obj<T> back(void);
  bool contains (const T &value);
  unsigned int size (void);

  void prepend_value(const T &value, const T &existingValue);
  void append_value(const T &value, const T &existingValue);
  ret_obj<T> kth_to_last_value(const unsigned &k);
  void delete_middle_node(DLNode_t<T> ** ptr_addr);
  bool is_valid(void);
  void partition (T value );
  bool is_palindrome(void);
  void reverse(void);
  DLNode_t<T> *loop_start(void);
  void break_loop(void);
  void repair(void) 
};

template <class T>
DList_t <T> *dl_list();
template <class T>
DLNode_t <T> *dl_node(const T &value);

#endif 