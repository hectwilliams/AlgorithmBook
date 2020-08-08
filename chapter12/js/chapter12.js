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
        selection = k.next;
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
      selection_prev.next = curr;

      curr = selection;
    }

    curr_prev = curr;
    curr = curr_prev.next;
  }

}

function test()
{
  let collection  = [5, 4,3,2,1];
  selectionSort(collection);
  console.log(collection);
};

function test2 ()
{
  let list = SList()
  list.add(5);
  list.add(4);
  list.add(3);
  list.add(2);
  list.add(1);

  selectionSort_list(list);
  list.display();
}

test2();