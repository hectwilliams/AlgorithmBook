
function AVLTree()
{
  this.head = null;
}
function AVLNode (value)
{
  this.value = value;
  this.count  = 1;
  this.left = null;
  this.right = null;
  this.balance = 0;


}



AVLTree.prototype.add = function(value, node = null)
{

  if (!node )
  {
    node = this.head;
  }

  if (!node)
  {
    this.head = new AVLNode(value)
  }
  else
  {
    if (value < node.value)
    {
      if (node.left)
      {
        if (this.add(value, node.left))
        {
          node.balance++;
          return node.balance != 0;
        }
      }
      else
      {
        node.left = new AVLNode(value);
        node.balance++;
        return node.balance != 0;
      }
    }
    else  if (value > node.value)
    {
      if (node.right)
      {
        if (this.add(value, node.right ) )
        {
          node.balance--;
          return node.balance != 0;
        }
      }
      else
      {
        node.right = new AVLNode(value);
        node.balance--;
        return node.balance != 0;
      }
    }

    else if (value == node.value)
    {
      node.count++;
    }

  }

};


AVLNode.prototype.display = function()
{
  if (this.left)
  {
    this.left.display();
  }

  console.log( 'value: ' + this.value + ' ' + 'balance: ' + this.balance );

  if (this.right)
  {
    this.right.display();
  }
};

AVLNode.prototype.height = function()
{
  if (this)
  {
    if (this.left == null && this.right == null)
    {
      return  0;
    }
    else if( this.balance > 0  && this.left)
    {
      return 1 + this.left.height();
    }

    else if ( this.balance < 0 && this.right)
    {
      return 1 + this.right.height();
    }
  }

  return 0;
};


AVLTree.prototype.height = function()
{

  return this.head.height();
};


AVLNode.prototype.isBalanced = function()
{
  return Math.abs(this.balance) <= 1;
};


AVLTree.prototype.isBalanced = function()
{
  return this.head.isBalanced();
};


AVLNode.prototype.inOrderSuccessor = function()
{
  let runner = this.right;
  while (runner.left)
  {
    runner = runner.left;
  }
  return runner.value;
};

AVLNode.prototype.copyAttributes = function(src)
{
  let attrs = ['left', 'right', 'count', 'value', 'balance' ];
  attrs.forEach((attr)=>{
    this[attr] = src[attr];
  });
};

AVLNode.prototype.updateBalanceAck = function(isValid, level)
{
  let prevBal = this.balance;
  if (isValid)
  {
    this.balance += level;
    if (prevBal == 0)
    {
      isValid = false;
    }
  }
  return isValid;
};

AVLNode.prototype.removeHelper = function(parent, AVLTreeClass)
{
  let isRoot = this == parent;
  let successor;
  let flag = true;


  if (this.left && this.right)
  {
    successor = this.inOrderSuccessor();
    flag = AVLTreeClass.remove(successor, this);
    flag = this.updateBalanceAck(flag , 1);
    this.value = successor;
  }

  else if (this.right)
  {
    this.copyAttributes(this.right);
    if (!isRoot)
    {
      parent.balance++;
    }
  }

  else if (this.left)
  {
    this.copyAttributes(this.left);
    if (!isRoot)
    {
      parent.balance--;
    }
  }

  else if (this.left == null && this.right == null)
  {
    if (isRoot)
    {
      AVLTreeClass.head = null;
    }

    else if (parent.right == this )
    {
      parent.balance++;
      parent.right = null;
      if (parent.left)
      {
        flag = 0;
      }
    }

    else if (parent.left == this)
    {
      parent.balance--;
      parent.left = null;
      if (parent.right)
      {
        flag = 0;
      }
    }

  }

  return flag;
};

AVLTree.prototype.remove = function(value, node = null)
{
  let flag = 0;

  if (node == null )
  {
    node = this.head;
    if (!node)
    {
      return;
    }
  }

  if (node.value == value)
  {
    flag = node.removeHelper.call(node, this);
  }

  else if (value < node.value)
  {
    if (node.left)
    {
      if (node.left.value == value )
      {
        flag = node.left.removeHelper(node, this);
      }
      else
      {
        flag = this.remove(value, node.left);
        flag = node.updateBalanceAck(flag, -1);
      }
    }
  }

  else if (value >  node.value)
  {
    if (node.right)
    {
      if (node.right.value == value )
      {
        flag = node.right.removeHelper(node, this);
      }
      else
      {
        flag = this.remove(value, node.right);
        flag = node.updateBalanceAck(flag, 1);

      }
    }
  }

  return flag;

};

AVLNode.prototype.calculateBalance = function()
{
  this.balance = (1 + this.height.call(this.left) ) -   (1 + this.height.call(this.right) );
};



AVLNode.prototype.leftRotateTranslate = function(parent, avlTreeObj)
{
  let c, t, promote;

  promote = this.right;

  if (this.right.balance > 0)
  {
    promote = this.right.left;
    avlTreeObj.rightRotate(this.right, this);
  }

  c = this.right;
  t = c.left;

  c.left = this;
  this.right = t;

  this.calculateBalance();
  c.calculateBalance();

  if (parent == this)
  {
    avlTreeObj.head = promote;
  }

  else if (parent.left == this)
  {
    parent.left = promote;
  }

  else if (parent.right == this)
  {
    parent.right = promote;
  }

};


AVLTree.prototype.leftRotate = function(target, node = null)
{
  if (node == null)
  {
    node = this.head;
    if (!node)
    {
      return;
    }
  }

  if ( target.right)
  {
    if (node == target)
    {
      node.leftRotateTranslate(node, this);
    }

    else if (target.value < node.value)
    {
      if (node.left == target)
      {
        node.left.leftRotateTranslate(node, this);
      }
      else
      {
        this.leftRotate(target, node.left);
      }
    }

    else if (target.value > node.value)
    {
      if (node.right == target)
      {
        node.right.leftRotateTranslate(node, this);
      }
      else
      {
        this.leftRotate(target, node.right);
      }
    }
  }
};

AVLTree.prototype.rightRotate = function(target, node = null)
{
  if (node == null )
  {
    node = this.head;
    if (!node)
    {
      return;
    }
  }

  if (target.left)
  {

    if (node == target)
    {
      node.rightRotateTranslate(node, this);
    }

    else if (target.value < node.value)
    {
      if (node.left == target)
      {
        node.left.rightRotateTranslate(node, this);
      }
      else
      {
        this.rightRotate(target, node.left);
      }
    }

    else if (target.value > node.value)
    {
      if (node.right == target)
      {
        node.right.rightRotateTranslate(node, this);
      }
      else
      {
        this.rightRotate(target, node.right);
      }
    }
  }
}

AVLNode.prototype.rightRotateTranslate = function(parent, avlTreeObj)
{
  let c, t, promote;

  promote = this.left;

  if (this.left.balance < 0)
  {
    promote = this.left.right;
    avlTreeObj.leftRotate(this.left, this);
  }

  c = this.left;
  t = c.right;

  c.right = this;
  this.left = t;

  this.calculateBalance();
  c.calculateBalance();


  if (parent == this)
  {
    avlTreeObj.head = promote;
  }
  else if (parent.left == this)
  {
    parent.left = promote;
  }
  else if (parent.right == this)
  {
    parent.right = promote;
  }
};

AVLNode.prototype.balanceCheck = function (avlTree)
{
  if (this.balance  > 1)
  {
    avlTree.rightRotate(this);
  }

  else if (this.balance < -1)
  {
    avlTree.leftRotate(this);
  }
};

AVLTree.prototype.balancedAdd = function (value, node = null)
{
  let ret = 0;

  if (node == null)
  {
    node = this.head;
  }

  if ( !node )
  {
    this.head = new AVLNode(value);
  }
  else if (value < node.value)
  {
    if (node.left)
    {
      if ( this.balancedAdd(value, node.left) )
      {
        node.balance++;
      }
      node.left.balanceCheck(this);
    }
    else
    {
      node.balance++;
      node.left = new AVLNode(value);
    }
    ret = node.balance != 0;
  }

  else if (value > node.value)
  {
    if (node.right)
    {
      if ( this.balancedAdd(value, node.right) )
      {
        node.balance--;
      }
      node.right.balanceCheck(this);
    }
    else
    {
      node.balance--;
      node.right = new AVLNode(value);
    }
    ret = node.balance != 0;
  }

  else if (value == node.value)
  {
    node.count++;
  }

  if (this.head == node )
  {
    this.head.balanceCheck(this);
  }

  return ret;

};


AVLTree.prototype.balancedRemove = function (value, node = null)
{
  let flag = 0;

  if (node == null )
  {
    node = this.head;
    if (!node)
    {
      return;
    }
  }

  if (node.value == value)
  {
    flag = node.removeHelper(node, this);
  }
  else if (value < node.value)
  {
    if (node.left)
    {
      if (node.left.value == value )
      {
        flag = node.left.removeHelper(node, this);
      }
      else
      {
        flag = this.remove(value, node.left);
        flag = node.updateBalanceAck(flag, -1);
      }
    }

    node.left.balanceCheck(this);
  }
  else if (value >  node.value)
  {
    if (node.right)
    {
      if (node.right.value == value )
      {
        flag = node.right.removeHelper(node, this);
      }
      else
      {
        flag = this.remove(value, node.right);
        flag = node.updateBalanceAck(flag, 1);
      }
    }

    node.right.balanceCheck(this);
  }

  if (this.head == node)
  {
    this.head.balanceCheck(this);
  }

  return flag;
};


AVLTree.prototype.repair = function(node  = null  )
{

  if (!node)
  {
    node = this.head;
  }

  if (node)
  {
    if (node.left)
    {
      this.repair(node.left);
    }

    if (node.right)
    {
      this.repair(node.right);
    }
  }

  if (node.left)
  {
    while (node.left.balance > 1 || node.left.balance < -1)
    {
      node.left.balanceCheck(this);
    }
    node.calculateBalance();
  }

  if (node.right)
  {
    while (node.right.balance > 1 || node.right.balance < -1)
    {
      node.right.balanceCheck(this);
    }
    node.calculateBalance();
  }

};


function RBNode(value)
{
  this.color = 1;
  this.left = null;
  this.right = null;
  this.value = value;
  this.count = 1;
}

function RBTree ()
{
  this.root = null;
}

RBTree.prototype.contains = function(value, node = null)
{
  if (node == null)
  {
    node = this.root;
  }

  if (node)
  {
    if (node.value == value)
    {
      return true;
    }

    else if (value < node.value)
    {
      return this.contains.call(this, value, node.left);
    }

    else if (value > node.value)
    {
      return this.contains.call(this, value, node.right);
    }
  }
  return false;
};

RBTree.prototype.translate = function(node, parent = null, code = -1)
{
  let c, gc, gc_l, gc_r, tree;

  const selectCode = {
    0: function(){
      node.color = 1;
      node.left.color = node.right.color = 0;
    },

    1: () =>  {
      c = node.left;
      tree = c.right;
      c.right = node;
      node.left = tree;

      c.color = 0;
      c.left.color = c.right.color = 1;

      if (parent == null)
      {
        this.root = c;
      }
      else if (parent.left == node)
      {
        parent.left = c;
      }
      else if (parent.right == node)
      {
        parent.right = c;
      }

    } ,

    2: ()=> {
      c = node.left;
      gc = node.left.right;
      gc_l = gc.left;
      gc_r = gc.right;

      gc.left = c;
      gc.right = node;
      node.left = gc_r;
      c.right = gc_l;

      gc.color = 0;
      gc.left.color = gc.right.color = 1;

      if ( !parent )
      {
        this.root = gc;
      }
      else if (parent.left == node)
      {
        parent.left = gc;
      }
      else if (parent.right == node)
      {
        parent.right = gc;
      }

    } ,

    3:  ()=> {
      c = node.right;
      tree = c.left;
      c.left = node;
      node.right = tree;
      c.color = 0;
      c.left.color = c.right.color = 1;
      if (parent == null)
      {
        this.root = c;
      }
      else if (parent.left == node)
      {
        parent.left = c;
      }
      else if (parent.right == node )
      {
        parent.right = c;
      }
    } ,

    4:  ()=> {

      c = node.right;
      gc = node.right.left;
      gc_l = gc.left;
      gc_r = gc.right;

      gc.right = c;
      gc.left = node;
      node.right = gc_l;
      c.left = gc_r;

      gc.color = 0;
      gc.left.color = gc.right.color = 1;

      if (parent == null)
      {
        this.root = gc;
      }
      else if (parent.left == node )
      {
        parent.left = gc;
      }
      else if (parent.right == node)
      {
        parent.right = gc;
      }

    }

  };

  if (selectCode[code])
  {
    selectCode[code]();
  }

  if (this.root.color)
  {
    this.root.color = 0;
  }

};

RBTree.prototype.add = function(value, node = null, parent = null)
{
  let acc = 0;

  if (this.root === null)
  {
    this.root = new RBNode(value);
    this.root.color = 0;
  }
  else
  {
    if (node == null)
    {
      node = this.root;
    }

    if (value < node.value)
    {
      if (node.left)
      {
        acc = this.add.call(this, value, node.left, node);
        acc += +(node.left.color)

        if (acc == 2)
        {
          acc = 0;
          if (node.right === null)
          {
            if (node.left && node.left.left)
            {
              this.translate.call(this, node, parent, 1);
            }
            else if (node.left && node.left.right)
            {
              this.translate.call(this, node, parent, 2);
            }
          }
          else if (node.right.color == 0)
          {
            if (node.left && node.left.left)
            {
              this.translate.call(this, node, parent, 1);
            }
            else if (node.left && node.left.right)
            {
              this.translate.call(this, node, parent, 2);
            }
          }
          else if (node.right.color)
          {
            this.translate.call(this, node, parent, 0);
          }
        }
      }
      else
      {
        node.left = new RBNode(value);
        acc = 1;
      }
    }
    else if (value > node.value)
    {
      if (node.right)
      {
        acc = this.add.call(this, value, node.right, node);
        acc += (node.right.color);


        if (acc == 2)
        {
          acc = 0;
          if (node.left === null)
          {
            if (node.right && node.right.right)
            {
              this.translate.call(this, node, parent, 3);
            }
            else if (node.right && node.right.left)
            {
              this.translate.call(this, node, parent, 4);
            }
          }
          else if (node.left.color == 0)
          {
            if (node.right && node.right.right)
            {
              this.translate.call(this, node, parent, 3);
            }
            else if (node.right && node.right.left)
            {
              this.translate.call(this, node, parent, 4);
            }
          }
          else if (node.left.color)
          {
            this.translate.call(this, node, parent, 0);
          }
        }
      }
      else
      {
        node.right = new RBNode(value);
        acc = 1;
      }
    }
    else if (value == node.value)
    {
      node.count++;
      acc = 0;
    }

    if (node.color == 0)
    {
      acc = 0;
    }
  }

  return acc;
};

RBTree.prototype.display = function(node = null)
{
  if (node == null)
  {
    node = this.root;
  }

  if (node)
  {
    if (node.left )
    {
      this.display.call (this, node.left)
    }

    console.log(node.value, node.color);

    if (node.right)
    {
      this.display.call(this, node.right);
    }
  }

};

RBTree.prototype.remove_helper = function (parent = null, node = null)
{
  let successor = null, parentOfSuccessor = null;

  if (node.count > 1)
  {
    node.count--;
  }
  else if (node.left == null && node.right == null)
  {
    successor = null;
  }
  else if (node.left && node.right == null)
  {
    successor = node.left;
  }
  else if (node.right && node.left == null)
  {
    successor = node.right;
  }
  else if (node.right && node.left)
  {
    if (node.right.left == null)
    {
      successor = node.right;
      successor.left = node.left;
    }
    else
    {
      parentOfSuccessor = node.right;
      while (parentOfSuccessor.left.left)
      {
        parentOfSuccessor = parentOfSuccessor.left;
      }
      successor = parentOfSuccessor.left;
      parentOfSuccessor.left = parentOfSuccessor.left.left;

      successor.left = node.left;
      successor.right = node.right;
      successor.count = node.count;
    }
  }

  if (parent== null)
  {
    this.root = successor;
  }
  else if (parent.left == node)
  {
    parent.left = successor;
  }
  else if (parent.right == node)
  {
    parent.right = successor;
  }

};


RBTree.prototype.remove = function (value, node = null)
{
  if (node == null)
  {
    node = this.root;
  }

  if (node )
  {
    if (node.value == value)
    {
      this.remove_helper.call(this, null, node);
    }
    else if (value < node.value)
    {
      if (node.left)
      {
        if (node.left.value == value)
        {
          this.remove_helper.call(this, node, node.left);
        }
        else
        {
          this.remove.call(this, value,  node.left)
        }

      }
    }

    else if (value > node.value)
    {
      if (node.right)
      {
        if (node.right.value == value)
        {
          this.remove_helper.call(this, node, node.right)
        }
        else
        {
          this.remove.call(this, value, node.right);
        }
      }
    }
  }
};

(
  function()
  {
    let tree = new AVLTree();

    let data = [
      100,
      50,       500,
      25,      450,        1000,
      20,     300,  480,   900,   2000,
      15,    200,          800
    ];

  tree.add(100);
  tree.add(50 );
  tree.add(200);
  tree.add(300);
  tree.add(400);
  tree.add(25);
  tree.add(5 );
  tree.add(10);

  data.forEach((ele) => {
    tree.add( Math.floor(Math.random()* 1000) );
  });


  // tree.balancedRemove(100);
  // tree.balancedRemove(400);
  // tree.balancedRemove(500);


    // console.log(tree.head.right.right.value);
    // console.log(tree.head.right.right.right.value);

    tree.repair();
    tree.head.display();

  }()
)