
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

    console.log( "info:\t ", node.value, node.color);

    if (node.right)
    {
      this.display.call(this, node.right);
    }
  }

};

RBNode.prototype.rightRotate = function(parent, rbtreeClass)
{
  let c, t;

  c = this.left;
  t = c.right;

  c.right = this;
  this.left = t;

  if (this == parent)
  {
    rbtreeClass.root = c;
  }

  else if (parent.left == this)
  {
    parent.left = c;
  }

  else if (parent.right == this)
  {
    parent.right = c;
  }

};

RBNode.prototype.leftRotate = function(parent, rbtreeClass)
{
  let c, t;

  c = this.right;
  t = c.left;

  c.left = this;
  this.right = t;


  if (this == parent)
  {
    rbtreeClass.root = c;
  }

  else if (parent.left == this)
  {
    parent.left = c;
  }

  else if (parent.right == this)
  {
    parent.right = c;
  }
};

RBNode.prototype.rotationCode = function()
{
  let no_rotation = 0;
  let left = 0, right = 0;

  if (this.left == null)
  {
    left = 0;
  }

  else if (this.left.color == 1)
  {
    left = 1;
  }

  if (this.right == null)
  {
    right = 0;
  }

  else if (this.right.color == 1)
  {
    right = 1;
  }




  if (this.left)
  {


    if (this.left.left)
    {
      if (this.left.color && this.left.left.color)
      {
        if (right)
        {
          return 5;
        }
        return 1;
      }
    }

    if (this.left.right)
    {
      if (this.left.color && this.left.right.color)
      {
        if (right)
        {
          return 5;
        }
        return 2;
      }
    }

  }

  if (this.right )
  {

    if (this.right.right)
    {
      if (this.right.color && this.right.right.color)
      {
        if (left)
        {
          return 5;
        }

        return 3;
      }
    }

    if (this.right.left)
    {
      if (this.right.color && this.right.left.color)
      {
        if (left)
        {
          return 5;
        }
        return 4;
      }
    }

  }

  return no_rotation;

};

RBTree.prototype.blackHeightErrorHanlder = function(hasImbalance, target, parentOfTarget)
{
  let op = 0;
  let promote = null;

  if (hasImbalance)
  {
    op = target.rotationCode();
  }

  let switcher = {
    1: () => {
      promote = target.left;
      /* right rotate target */
      target.rightRotate(parentOfTarget, this);
    },

    2: ()=> {
      promote = target.left.right;
      /* left rotate child */
      target.left.leftRotate(target, this);
      /* right rotate target */
      target.rightRotate(parentOfTarget, this);
    },

    3: () => {
      promote = target.right;
      /* left rotate target */
      target.leftRotate(parentOfTarget, this);
    },

    4: () => {
      promote = target.right.left;
      /* right rotate child */
      target.right.rightRotate(target, this);
      /* left rotate target */
      target.leftRotate(parentOfTarget, this);
    },

    5: () => {
      target.color ^= 1;
      target.left.color ^=1;
      target.right.color ^= 1;
    }

  };

  let functor = switcher[op];

  if (functor )
  {
    functor();
  }

  if (promote != null )
  {
    promote.color = 0;
    promote.left.color = promote.right.color = 1;
  }

  this.root.color = 0;
  // this.display();
  // console.log("\n");


};

RBTree.prototype.add = function(value, node = null, parent = null)
{
  let count = 0;

  if (node == null)
  {
    parent = node = this.root;
  }

  if (this.root == null)
  {
    this.root = parent = node = new RBNode(value);
  }
  else if (value < node.value)
  {
    if (node.left)
    {
      count  = this.add(value, node.left, node);
      count += node.left.color;
    }
    else
    {
      node.left = new RBNode(value);
      return 1 ;
    }
  }
  else if (value > node.value)
  {
    if (node.right)
    {
      count = this.add(value, node.right, node);
      count += node.right.color;

    }
    else
    {
      node.right = new RBNode(value);
      return 1 ;
    }
  }
  else if (value == node.value)
  {
    node.count++;
    return 0;
  }


  console.log("where ami ", node.value, "count", count)
  this.blackHeightErrorHanlder(count >= 2, node, parent) ;

  if (node.color == 0 || count >= 2)
  {
    return 0;

  }

  // count = node.color;

  return count;

};

RBNode.prototype.successor  = function ()
{

  let runner = this.right;
  while (runner.left)
  {
    runner = runner.left;
  }

  return runner.value;
};

RBNode.prototype.copy = function (src)
{
  if (src)
  {
    this.left = src.left;
    this.right = src.right;
    this.count = src.count;
    // this.color = src.color;  NOT ALLOWED RED BLACK TREE
    this.value = src.value;
  }
};

RBTree.prototype.findParent = function (target, node = null)
{
  if (node == null)
  {
    node = this.root;
  }

  if (node)
  {
    if (target.value < node.value)
    {
      if (node.left)
      {
        if (node.left == target )
        {
          return node;
        }
        else
        {
          this.findParent(target, node.left);
        }
      }
    }

    if (target.value > node.value)
    {
      if (node.right)
      {
        if (node.right == target)
        {
          return node;
        }
        else
        {
          this.findParent(target, node.right);
        }
      }
    }
  }

  return null;

};


RBTree.prototype.removeHelper = function (target, parent)
{
  let hasRed = false;
  let successor;

  if (target.left && target.right)
  {
    successor = target.successor();
    this.remove(successor);
    target.value = successor;
  }

  else if (target.left)
  {

    if (target.color || target.left.color)
    {
      target.color = 0;
      hasRed = true;
    }

    target.copy(target.left);

    if (target != this.root && !hasRed)
    {
      this.removeHelperBalance (target, 1, parent);
    }

  }

  else if (target.right)
  {

    if (target.color || target.right.color)
    {
      target.color = 0;
      hasRed = true;
    }

    target.copy(target.right)

    if (target != this.root && !hasRed)
    {
      this.removeHelperBalance (target, -1, parent);
    }

  }

  else if ( !target.left && !target.right )
  {

    if (this.root == target)
    {
      this.root = null;
    }

    else if (parent.left == target)
    {

      parent.left = null;

      if (!target.color) // leaf node is not red
      {
        this.removeHelperBalance (null, 1, parent);
      }

    }

    else if (parent.right == target   )
    {

      parent.right = null;

      if (!target.color) // leaf node is not red
      {
        this.removeHelperBalance(null, -1, parent);
      }

    }

  }

};


RBTree.prototype.removeHelperBalance = function (u, dir, p)
{
  let s;
  let sibColorLeft, sibColorRight, sibColor;


  if (dir == -1)  // update node (i.e. u ) is located at p.right
  {
    s = p.left;
  }

  if (dir == 1)  // update node (i.e. u ) is located at p.left
  {
    s = p.right;
  }

  // find colors of sibling subtree

  sibColor = s.color;

  if (s.left)
  {
    sibColorLeft = s.left.color;
  }
  else
  {
    sibColorLeft = 0;
  }

  if (s.right)
  {
    sibColorRight = s.right.color;
  }
  else
  {
    sibColorRight = 0;
  }

  if (sibColor == 0)
  {
    // CASE:  sibling black and black children

    if (sibColorLeft == 0 && sibColorRight == 0)
    {
      // recolor sibling
      s.color ^= 1;

      // add black to parent
      p.color--;
    }

    // CASE: sibling black w / red child
    else if (sibColorLeft == 1)
    {

      if (dir == -1)   // left left case
      {
        // set sibling child black
        s.left.color = 0;

        // swap colors or parent and sibling
        {
          let tmp = s.color;
          s.color = p.color;
          p.color = tmp;
        }

        // right rotate parent
        p.rightRotate( this.findParent(p), this );


        // remove double black node (iff node null)
        if (p.right)
        {
          p.right.color--;
        }
      }


      if (dir == 1)  // right left case
      {
        // set sibling  red
        s.color = 1;

        // set sibling child black
        s.left.color = 0;

        /// right rotate sibling
        s.rightRotate(p, this);

        // case 2 ( recursion )
        this.removeHelperBalance(u, dir, p );  // left rotation or right rotation

      }

    }

    // CASE: sibling black w / red child

    else if (sibColorRight == 1 )
    {

      if (dir == 1)   // right right case
      {
        // set sibling child black
        s.right.color = 0;

        // swap colors or parent and sibling
        {
          let tmp = s.color;
          s.color = p.color;
          p.color = tmp;
        }

        // left rotate parent
        p.leftRotate( this.findParent(p), this );

        // remove double black node (iff node null)
        if (p.left)
        {
          p.left.color--;
        }
      }

      if (dir == -1)  // left right case
      {
        // set sibling red
        s.color = 1;

        // set sibling child black
        s.right.color = 0;

        // left rotate sibling
        s.leftRotate(p, this);

        // case 2 (recursion)
        this.removeHelperBalance(u, dir, p);  // left rotation or right rotation
      }
    }
  }

  // CASE 4: sibling red

  if (sibColor == 1)
  {
    // swap colors of parent and sibling
    {
      let tmp = s.color;
      s.color = p.color;
      p.color = tmp;
    }

    if (dir == 1)
    {
      p.leftRotate( this.findParent(p), this );
    }

    if (dir == -1)
    {
      p.rightRotate(this.findParent(p) , this);
    }

    // CASE 1,2, or 3 (recursion)
    this.removeHelperBalance(p.left, 1, p);

  }

};

RBTree.prototype.remove = function (value, node = null, parent = null)
{
  if (!node)
  {
    parent = node = this.root;
  }

  if (node)
  {

    if (value == node.value)
    {
      this.removeHelper(node, parent);
    }

    else if (value < node.value)
    {
      this.remove(value, node.left, node);
    }

    else if (value > node.value)
    {
      this.remove(value, node.right, node);
    }

    if (node.color == -1)
    {
      if (node == this.root)
      {
        this.root.color = 0;
      }
      else
      {
        if (parent.left == node)
        {
          this.removeHelperBalance(node, 1, parent );   // double black found
        }
        else if (parent.right == node)
        {
          this.removeHelperBalance(node, - 1, parent );   // double black found
        }
      }
    }

  }

};


RBNode.prototype.heights = function (collection = [], curr = [],  count = 0)
{

  count += this.color == 0;

  if (this.left == null  && this.right == null)  // leaf
  {
    count += 1;
    collection.push(count)
    curr.push(this.value);
    console.log(" -- > \t\t", curr);
  }

  if (this.left)
  {
    this.left.heights(collection, curr.concat(this.value),  count);
  }

  if (this.right)
  {
    this.right.heights(collection, curr.concat(this.value),  count);
  }

  if (curr.length == 0)
  {
    console.log(collection);
  }
};

(
  function()
  {
    let tree = new RBTree();

    tree.add(3);
    tree.add(1 );
    tree.add(5);
    tree.add(7);
    tree.add(6);
    tree.add(8);
    tree.add(9 );
    tree.add(10);
    tree.add(12);
    tree.add(12333);
    tree.add(2);

    // tree.remove(12333);
    tree.display();

    tree.root.heights();
    // console.log(tree.root.value)

  }()
)