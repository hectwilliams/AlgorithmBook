
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


RBTree.prototype.display = function(node = null, obj = {msg: "" })
{
  if (node == null)
  {
    node = this.root;
  }

  if (node)
  {
    if (node.left )
    {
      this.display.call (this, node.left, obj)
    }

    obj.msg +=  JSON.stringify (  { count: node.count , val: node.value, color: node.color} )  + "\n";

    if (node.right)
    {

      this.display.call(this, node.right, obj);
    }
  }

  if (this.root == node)
  {
    console.log(obj.msg);
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

  this.blackHeightErrorHanlder(count >= 2, node, parent) ;

  if (node.color == 0 || count >= 2)
  {
    return 0;

  }

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
    this.value = src.value;
    // this.color = src.color;  NOT ALLOWED RED BLACK TREE
  }
};



RBTree.prototype.findParent = function (target, node = null)
{
  let a = null, b = null;

  if (node == null)
  {
    node = this.root;
  }

  if (node)
  {

    if (node.left)
    {
     a =  this.findParent(target, node.left);
    }


    if (node.right)
    {
      b = this.findParent(target, node.right);

    }

    if (node.right == target )
    {
      return node;
    }

    if (node.left == target)
    {
      return node;
    }
  }

  return a || b;
};

RBTree.prototype.removeHelper = async function (target, parent)
{
  let isDoubleBlack;
  let callbackMessage = "rebalanced tree";

  return new Promise ( (resolve, reject) => {

    if (target.left != null && target.right != null)
    {

      return new Promise ( (resolve2) => {
        resolve2({newSuccessor : target.successor() , node : target});
      })

      .then ( (successorshipObj) => {

        this.remove(successorshipObj.newSuccessor)

        .then ( (msg) => {

          // update node w/ new successsor
          successorshipObj.node.value = successorshipObj.newSuccessor;

          //resolve ack
          return Promise.resolve(1);
        })

        .then ((msg) => {
         return  resolve(callbackMessage + " successorship");
        })

        .catch((err) => {
          reject(" successorship error")
        })

      })

    }

    else if (target.left)
    {

      isDoubleBlack = (target.color || target.left.color) == 0;

      target.copy(target.left);

      if ( ! isDoubleBlack)
      {
        target.color = 0;
        return resolve (callbackMessage );
      }
      else
      {
        resolve (this.removeHelperBalance (target, 1, parent));
      }
    }

    else if (target.right)
    {
      isDoubleBlack = (target.color || target.right.color) == 0;

      target.copy(target.right)

      if (! isDoubleBlack)
      {
        target.color = 0;
        return resolve (callbackMessage );
      }
      else
      {
        resolve (this.removeHelperBalance (target, -1, parent));      // ret promise obj
      }
    }

    else if ( target.left == null && target.right == null )
    {
      isDoubleBlack = (target.color == 0);

      if (this.root == target)
      {
        this.root = null;
        return resolve (callbackMessage );
      }

      else if (parent.left == target)
      {
        parent.left = null;

        if ( !isDoubleBlack  )
        {
          return resolve (callbackMessage );
        }
        else
        {
          return resolve( this.removeHelperBalance (null, 1, parent));
        }
      }

      else if (parent.right == target )
      {
        parent.right = null;

        if ( !isDoubleBlack)
        {
          return resolve (callbackMessage );
        }
        else
        {
          return resolve( this.removeHelperBalance(null, -1, parent));
        }

      }
    }

  })

};


RBTree.prototype.removeHelperBalance = async  function (u, dir, p)
{

  let callbackMessage = "rebalanced tree";

  return new Promise ((resolve) => {

    let s = null;
    let sibColorLeft = 0, sibColorRight = 0, sibColor = 0;

    if (this.root == u && this.root)
    {
      this.root.color = 0;
      return resolve(callbackMessage);
    }

    if (dir == -1)  // update node (i.e. u ) is located at p.right
    {
      s = p.left;
    }

    if (dir == 1)  // update node (i.e. u ) is located at p.left
    {
      s = p.right;
    }

    // find colors of sibling subtree

    if (s)
    {

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
    }

    else
    {
      return resolve("");
    }


    if (sibColor === 0)
    {
      // CASE:  sibling black and black children

      if (sibColorLeft == 0 && sibColorRight == 0)
      {
        // recolor sibling to red
        s.color = 1;

        // red parent recolor
        if (p.color == 1)
        {
          p.color = 0;

          return resolve(callbackMessage);
        }

        // black parent

        else if (p.color == 0)
        {
          u = p;

          p = this.findParent(p);

          if (p.left == u )
          {
            dir = 1;
          }

          if (p.right == u)
          {
            dir = -1;
          }

          return resolve (this.removeHelperBalance(u, dir, p));
        }
      }

      else if (sibColorLeft == 1 && sibColorRight == 1)
      {
        if (dir == -1)   // left left
        {

          // swap colors or parent and sibling
          {
            let tmp = s.color;
            s.color = p.color;
            p.color = tmp;
          }

          // set sibling child black
          s.left.color = 0;

          // right rotate parent
          p.rightRotate( this.findParent(p), this );

          return resolve(callbackMessage);

        }

        if (dir == 1)
        {

          // swap colors or parent and sibling
          {
            let tmp = s.color;
            s.color = p.color;
            p.color = tmp;
          }

           // set sibling child black
           s.right.color = 0;

          // left rotate parent
           p.leftRotate(  this.findParent(p), this );

          return resolve(callbackMessage);
        }
      }

      // CASE: sibling black w / red child
      else if (sibColorLeft === 1)
      {

        if (dir == -1 )   // left left case
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

          return resolve(callbackMessage);

        }

        if (dir == 1)  // right left case
        {
          // set sibling  red
          s.color = 1;

          // set sibling child black
          s.left.color = 0;

          /// right rotate sibling
          s.rightRotate(p, this);

          // case recursion
          return  resolve(this.removeHelperBalance(u, dir, p ));
        }
      }


      // CASE: sibling black w / red child

      else if (sibColorRight === 1 )
      {

        if (dir == 1) // right right case
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

          return resolve(callbackMessage);

        }

        if (dir == -1)  // left right case
        {
          // set sibling red
          s.color = 1;

          // set sibling child black
          s.right.color = 0;

          // left rotate sibling
          s.leftRotate(p, this);

          // case recursion
          return  resolve (this.removeHelperBalance(u, dir, p));
        }
      }
    }

    // CASE : sibling red

    else if (sibColor === 1)
    {
      // swap colors of parent and sibling
      {
        let tmp = s.color;
        s.color = p.color;
        p.color = tmp;
      }

      if (dir == 1)  // sibling on right of parent
      {
        // left rotate
        p.leftRotate( this.findParent(p), this );

        // recursion
        return resolve(this.removeHelperBalance(p.left, 1, p));
      }

      if (dir == -1)  // sibling on left of parent
      {
        // right rotation
        p.rightRotate(this.findParent(p), this);

        // case recursion
        return resolve(this.removeHelperBalance(p.right, -1, p));
      }

    }

    return resolve(callbackMessage);
  });

};



 RBTree.prototype.remove =  async function (value, node = null, parent = null)
{

  return new Promise ( (resolve, reject) => {

    if (!node)
    {
      parent = node = this.root;
    }

    if (node)
    {

      if (value == node.value)
      {
        if ( node.count > 1)
        {
          node.count--;
          return resolve("multiple occurence of value decrementing count ");
        }
        else
        {
          return resolve (this.removeHelper(node, parent));
        }
      }

      else if (value < node.value)
      {
        if (node.left)
        {
          resolve (this.remove (value, node.left, node)); // recursion
        }
        else
        {
          resolve (`warning, value not found (probably removed already )`);
        }
      }

      else if (value > node.value)
      {
        if (node.right)
        {
          resolve (this.remove(value, node.right, node)); // recursion
        }
        else
        {
          resolve (`wanring, value not found (probably removed already )`);
        }
      }

    }

    else
    {
      reject("err, tree does not exist");
    }

  })

};



RBNode.prototype.heights = function (collection = [], curr = [],  count = 0)
{

  count += this.color == 0;

  if (this.left == null  && this.right == null)  // leaf
  {
    count += 1;
    collection.push(count)
    curr.push(this.value);
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
    return collection;
  }
};

RBTree.prototype.isValidRedBlackTree = function ()
{
  return this.root.heights().every((element, noop, collection) => {return element == collection[0]}  );
};


RBTree.prototype.removeTest = function( num_elements = 200 /* number of values to add to tree */)
{
  let tree = new RBTree();
  let randomPushedDataFromTestData = [];
  let treeValues = [];

  // load arrays
  for (let i = 0; i < num_elements; i++)
  {
    let data = Math.round(Math.random() * 1000);

    treeValues.push(data);

    // load random data to test tree
    if (Math.round(Math.random()) )
    {
      randomPushedDataFromTestData.push(data);
    }
  }


  // chain insertion promises
  treeValues.reduce( (noop, value, index, array) =>{
    array[index] = Promise.resolve(tree.add(value));  //insertion
  }, 0)

  // insert values to tree (async)
  Promise.all(treeValues)

  // chain remove tree calls
  randomPushedDataFromTestData.reduce((noop, value, index, array) => {
     array[index] = Promise.resolve( tree.remove(value));  // remove
     return null;
  }, 0)


  // remove values from tree  and validate tree (async)

   return Promise.all(randomPushedDataFromTestData)

   .then( (resp) => {

    // console.log(resp); // response/ack per deletion of value

    if (tree.isValidRedBlackTree())
    {
      return Promise.resolve("valid tree");
    }
    else
    {
      return Promise.reject("error: tree is not valid");
    }

   })

   .catch( err => {return Promise.reject(err) } );

};



// // RED BLACK TREE TEST REMOVAL
// (
//   function()
//   {

//     let tree = new RBTree;
//     tree.removeTest(1000)  //load 1000 random values to tree
//     .then( x => console.log(x))
//     .catch( x => console.log(x));
//   }()
// )


function SplayNode(value)
{
  this.value = value;
  this.left = null;
  this.right = null;

  this.display = function()
  {
    if (this.left)
    {
      this.left.display();
    }

    console.log(this.value);

    if (this.right)
    {
      this.right.display();
    }
  };
}

function SplayTree()
{
  this.root = null;

  this.display = function()
  {
    if (this.root)
    {
      this.root.display();
    }
  }


  this.remove = function(value, node = null, parent = null )
  {
    var removeDriver = function (value, node, parent)
    {
      if (!node)
      {
        node  = this.root;
      }

      if (node)
      {
        if (value == node.value)
        {
          removeTarget.call (this, node, parent);
        }

        else if (value < node.value && node.left)
        {
          removeDriver.call(this, value, node.left, node);
        }

        else if (value > node.value && node.right)
        {
          removeDriver.call(this, value , node.right, node);
        }
      }
    };

    var splay = function(value, node, parent)
    {
       if (value == node.value )
       {
         return
       }

       else if (value < node.value && node.left)
       {
          splay.call(this, value, node.left, node );

         if (node.left.value != value)
         {
           node.rightRotate(parent, this);
         }
       }

       else if (value > node.value && node.right)
       {
         splay.call(this, value, node.right, node) ;

         if (node.right.value != value)
         {
           node.leftRotate(parent, this);
         }
       }
    };

    var removeTarget  = function (target, parent)
    {
      if (target.right && target.left)
      {
        successor = target.successor();
        this.remove(successor);
        target.value = successor;
      }

      else if (target.right)
      {
        target.copy(target.right)
      }

      else if (target.left)
      {
        target.copy(target.left)
      }

      else if ( ! target.right && ! target.left)
      {
        if (!parent)
        {
          this.root = null;
        }

        else if (parent.left == target)
        {
          parent.left = null;
        }

        else if (parent.right == target)
        {
          parent.right = null;
        }
      }
    };

    splay.call(this, value, this.root, null);
    removeDriver.call(this, value, this.root, null);

  };

}


SplayTree.prototype.add = function(value)
{
  let newRoot = new SplayNode(value);

  if ( ! this.root )
  {
    this.root = newRoot;
  }

  else if (this.root.value < value)
  {
    newRoot.left = this.root;
  }

  else
  {
    newRoot.right = this.root;
  }

  this.root = newRoot;

 };

 SplayNode.prototype.successor = function()
 {
   let runner = this.right;
   while (runner.left)
   {
     runner = runner.left;
   }
   return runner.value;
 };

 SplayNode.prototype.copy = function (src)
 {
  if (src)
  {
    this.right = src.right;
    this.left = src.left;
    this.value = src.value;
  }
 };

 SplayNode.prototype.leftRotate = function(parent, splayTreeClass)
 {
   let c, t;

   c = this.right;
   t = c.left;

   c.left = this;
   this.right = t;

   if ( ! parent )
   {
     splayTreeClass.root = c;
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

 SplayNode.prototype.rightRotate = function(parent, splayTreeClass)
 {
   let c;
   let t;

   c = this.left;
   t = c.right;

   c.right = this;
   this.left = t;

   if ( ! parent )
   {
     splayTreeClass.root = c;
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





 (
  function()
  {
    tree = new SplayTree;
    tree.add(1);
    tree.add(2);
    tree.add(3);
    tree.add(1);
    tree.add(6);
    tree.remove(2);

    tree.display();
    console.log("ROOT", tree.root.value);

  }()
 )
