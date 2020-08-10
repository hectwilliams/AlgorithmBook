var SLNode = function(data)
{
  if (! (this instanceof(SLNode)))
  {
    return new SLNode(data);
  }
  this.value = data;
  this.next = null;
}

var SList = function()
{
  if (!(this instanceof(SList)))
  {
    return new SList();
  }
  this.head = null;

  this.add = (data) => {
    let runner;

    if (this.head == null)
    {
      this.head = SLNode(data);
    }
    else
    {
      runner = this.head;
      while (runner.next)
      {
        runner = runner.next;
      }
      runner.next = SLNode(data);
    }
  };

  this.display = () => {
    let runner= this.head
    while (runner)
    {
      console.log(runner.value);
      runner = runner.next;
    }
  }
}

var swap = function (collection, i, k)
{
  let tmp = collection[k];
  collection[k] = collection[i];
  collection[i] = tmp;
};

var bubbleSort = function(collection = [])
{
  for (let i = 0; i < collection.length - 1; i++)
  {
    for (let k = 0; k < collection.length - i - 1; k++)
    {
      swap(collection, k, k + 1 ) ;
    }
  }
};

var selectionSort = function(collection = [])
{
  let sel_index;
  let size = collection.length;

  for (let i = 0; i < size; i++)
  {
    sel_index = i;

    for (let k = sel_index; k < size; k++)
    {
      if (collection[k] < collection[sel_index])
      {
        sel_index = k;
      }
    }

    if (sel_index != i)
    {
      swap(collection, sel_index, i);
    }
  }
}

var bubbleSort_list = function (llist)
{
  let curr = llist.head;
  let k, kprev, buffer, end;

  k = kprev = buffer = end;


  while (curr != end )
  {
    k = llist.head;
    kprev = null;

    while (k.next)
    {
      if (k.value  > k.next.value)
      {
        buffer = k.next;
        k.next = k.next.next;

        if (curr == k)
        {
          curr = buffer;
        }
        if (k == llist.head)
        {
          buffer.next = llist.head;
          llist.head = buffer;
        }
        else if (kprev)
        {
          kprev.next = buffer;
          buffer.next = k;
        }
        kprev = buffer;
        k = kprev.next;
      }
      else
      {
        kprev = k;
        k = k.next;
      }
    }
    end = k;
    curr = curr.next;
  }
}

var selectionSort_list = function (llist)
{
  let curr, k, kprev, curr_prev, selection_prev, selection;

  curr = k = kprev = curr_prev = selection_prev = selection = null;

  curr = llist.head

  while (curr)
  {
    k = selection = curr;
    while (k.next)
    {
      if (k.next.value < selection.value)
      {
        selection = k.next
;
        selection_prev = k;
      }
      k = k.next;
    }

    if (curr != selection)
    {
      selection_prev.next = selection_prev.next.next;

      selection.next = curr.next;

      if (curr == llist.head)
      {
        llist.head = selection ;
      }
      else
      {
        curr_prev.next = selection;
      }

      curr.next = selection_prev.next;

      if (curr != selection_prev)
      {
        selection_prev.next = curr;
      }
      else
      {
        selection.next = curr;
      }

      curr = selection;
    }

    curr_prev = curr;
    curr = curr_prev.next;
  }

}

var multiSort = function (llist, prio = 0)
{

  let curr, k, k_prev, curr_prev, selection_prev, selection;

  curr = k = kprev = curr_prev = selection_prev = selection = null;

  if (prio == 2)
  {
    return;
  }

  curr = llist.head;

  while (curr)
  {
     k = selection = curr;
     while (k.next)
     {
      if ( (prio == 0 && k.next.value.last < selection.value.last ) || (prio == 1 && k.next.value.first < selection.value.first && k.next.value.last == selection.value.last)     )
      {
        selection_prev = k;
        selection = k.next;
      }
      k = k.next;
     }

     if (curr != selection)
     {
       selection_prev.next = selection_prev.next.next;
       selection.next = curr.next;

       if (curr == llist.head)
       {
         llist.head = selection;
       }
       else
       {
         curr_prev.next = selection;
       }
       curr.next = selection_prev.next;
       if (curr != selection_prev)
       {
         selection_prev.next = curr;
       }
       else
       {
         selection.next = curr;
       }
       curr = selection
     }
     curr_prev = curr;
     curr =  curr.next;
  }

}

function test2 ()
{
  let list = SList()
  list.add({first: 'Aaron', last: 'Carnevale' });
  list.add({first: 'Lee', last: 'Abbey' });
  list.add({first: 'Giorgio', last: 'Carnevale' });

  multiSort(list);
  list.display();
}

test2();