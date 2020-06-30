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

#endif 