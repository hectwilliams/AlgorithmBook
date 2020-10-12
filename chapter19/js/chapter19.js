
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


AVLTree.prototype.display = function(node = null)
{
  if (!node)
  {
    node = this.head;
  }

  if (node)
  {
    if (node.left)
    {
      this.display.call(this, node.left);
    }

    console.log( 'value: ' + node.value + ' ' + 'balance: ' + node.balance );

    if (node.right)
    {
      this.display.call(this, node.right);
    }
  }
};

AVLTree.prototype.removeHelper = function(parent, node)
{
  let parentOfSuccessor = null, successor = null;

  if (node.count > 1)
  {
    node.count--;
    return false; // no updates to upstream nodes
  }

  if (!node.left && !node.right)
  {
    successor = null;
    if (parent == null)
    {
      this.head = successor;
    }
    else if (parent.left == node)
    {
      parent.left = successor;
    }
    else if (parent.right == node)
    {
      parent.right = successor;
    }

    if (parent)
    {
      return true; // update upstream node balance
    }
  }

  else if (node.left != null && node.right == null)
  {
    successor = node.left;
    if (parent == null)
    {
      this.head = successor;
    }
    else if (parent.left == node)
    {
      parent.left = successor;
    }
    else if (parent.right == node)
    {
      parent.right = successor;
    }

    if (parent)
    {
      return true; // update upstream node balance
    }
  }

  else if (node.right != null && node.left == null)
  {
    successor = node.right;
    if (parent == null)
    {
      this.head = successor;
    }
    else if (parent.left == node)
    {
      parent.left = successor;
    }
    else if (parent.right == node)
    {
      parent.right = successor;
    }

    if (parent)
    {
      return true; // update upstream node balance
    }
  }

  else if (node.right && node.left)
  {
    // NOTE: successor connected to predecessor

    if (node.right.left == null)
    {

      successor = node.right;

      // update successors's parent's balance
      {
        node.balance++;
      }

      // promote successor
      {
        if (parent == null)
        {
          this.head = successor;
        }
        else if (parent.left == node)
        {
          parent.left = successor;
        }
        else if (parent.right == node)
        {
          parent.right = successor;
        }
      }

      // copy predecessor attributes (omit right and value attributes)
      {
        successor.left = node.left;
        successor.balance = node.balance;
      }

      // tree balance adjust ??
      if (successor.balance == 0)
      {
        return true; // update upstream node balance
      }

    }

    else
    {
      // NOTE:  successor is always a leaf node

      // find successor
      {
        parentOfSuccessor = node.right;
        while (parentOfSuccessor.left.left)
        {
          parentOfSuccessor = parentOfSuccessor.left;
        }
        successor = parentOfSuccessor.left;
      }

      // update successor's parent's balance
      {
        if (parentOfSuccessor.left == successor)
        {
          parentOfSuccessor.balance--;
        }

        if (parentOfSuccessor.right == successor)
        {
          parentOfSuccessor.balance++;
        }
      }

      // update path balance  (from: predecessor(include)   -->  to: successor(exclude))
      {
        if (parentOfSuccessor.right == null)
        {
          update_path_balance(node, parentOfSuccessor);
        }
      }

      // remove successor from successor's parent
      {
        parentOfSuccessor.left = parentOfSuccessor.left.left;
      }

      // promote successor
      {
        if (parent == null)
        {
          this.head = successor;
        }
        else if (parent.left == node)
        {
          parent.left = successor;
        }
        else if (parent.right == node)
        {
          parent.right = successor;
        }

        // copy attributes (omit value)
        successor.left = node.left;
        successor.right = node.right;
        successor.balance = node.balance;
        successor.count = node.count;
      }

      if (parentOfSuccessor.balance == 0)
      {
        return true;  // return upstream node balance
      }

    }
  }

  return false;
};

const update_path_balance = function(currNode, stopNode)
{
  if (currNode && stopNode)
  {
    while (currNode != stopNode)
    {
      if (stopNode.value < currNode.value)
      {
        currNode.balance--;
        return update_path_balance(currNode.left, stopNode);
      }
      else
      {
        currNode.balance++;
        return update_path_balance(currNode.right, stopNode);
      }
    }
  }
};



AVLTree.prototype.remove = function(value = null, node = null)
{
  let balanceFeedback = 0;

  if (!node)
  {
    node = this.head;
  }

  if (node)
  {
    if (node.value == value )
    {
      balanceFeedback =  this.removeHelper.call(this, null, node);
    }

    else if (value < node.value)
    {
      if (node.left)
      {
        if (node.left.value == value)
        {
          balanceFeedback =  this.removeHelper.call(this, node, node.left);
        }
        else
        {
          balanceFeedback =  this.remove.call(this, value, node.left);
        }

        if (balanceFeedback)
        {
          node.balance--;
        }
      }
    }

    else if (value > node.value)
    {
      if (node.right)
      {
        if (node.right.value == value)
        {
          balanceFeedback =  this.removeHelper.call(this, node, node.right);
        }
        else
        {
          balanceFeedback =  this.remove.call(this, value, node.right);
        }

        if (balanceFeedback)
        {
          node.balance++;
        }
      }
    }
  }

  return balanceFeedback;
};


AVLNode.prototype.height = function(node = null)
{
  if (!node)
  {
    node = this;
  }

  if (node)
  {
    if( (node.balance > 0) || (node.balance == 0 && node.left) )
    {
      return 1 + this.height.call(this, node.left);
    }

    if ( (node.balance < 0) || (node.balance == 0 && node.right) )
    {
      return 1 + this.height.call(this, node.right);
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


AVLNode.prototype.setBalance = function()
{
  if (this.left && this.right)
  {
    this.balance = this.left.height() - this.right.height();
  }

  else if (this.right)
  {
    this.balance = -(1 + this.right.height());
  }

  else if (this.left)
  {
    this.balance = (1 + this.left.height());
  }

  else if (this.left == null && this.right == null)
  {
    this.balance = 0;
  }
};

AVLNode.prototype.grandchildPromote = function()
{
  let c, gc, tree;

  if (this.balance > 0)    // PARENT -> LEFT
  {
    if (this.left.balance > 0)  // PARENT  -> LEFT  -> LEFT
    {
      // c = this.left;
      // gc = c.left;
      // tree = gc.right;

      // gc.right = c;
      // c.left = tree;
      // this.left = gc;

      // c.setBalance();
      // gc.setBalance();
      // this.setBalance();
    }
    else if (this.left.balance < 0)  // PARENT  -> LEFT  -> RIGHT
    {
      c = this.left;
      gc = c.right;
      tree = gc.left;

      gc.left = c;
      c.right = tree;
      this.left = gc;

      c.setBalance();
      gc.setBalance();
      this.setBalance();
    }
  }

  else if (this.balance < 0)  // PARENT -> RIGHT
  {
    if (this.right.balance > 0)   // PARENT  -> RIGHT  -> LEFT
    {
      c = this.right;
      gc = c.left;
      tree = gc.right;

      gc.right = c;
      c.left = tree;
      this.right = gc;

      c.setBalance();
      gc.setBalance();
      this.setBalance();
    }

    else if (this.right.balance < 0)   // PARENT  -> RIGHT  -> RIGHT
    {
      // c = this.right;
      // gc = c.right;
      // tree = gc.left;

      // gc.left = c;
      // c.right = tree;
      // this.right = gc;

      // c.setBalance();
      // gc.setBalance();
      // this.setBalance();
    }
  }

};

AVLTree.prototype.leftRotate = function(target, node = null)
{
  let parentOfTarget = null;
  let targetRef = null;
  let tree = null;
  let child = null;

  if (node == null)
  {
    node = this.head;
  }

  if (node)
  {
    if (node == target)
    {
      targetRef = node;
    }
    else if (node.left == target)
    {
      parentOfTarget = node;
      targetRef = node.left;
    }
    else if (node.right == target)
    {
      parentOfTarget = node;
      targetRef = node.right;
    }
    else if (target.value < node.value)
    {
      return this.leftRotate.call(this, target, node.right);
    }
    else if (target.value > node.value)
    {
      return this.leftRotate.call(this, target, node.right);
    }
  }


  if (targetRef)
  {
    targetRef.grandchildPromote();

    child = targetRef.right;
    tree = child.left;

    child.left = targetRef;
    targetRef.right = tree;

    targetRef.setBalance();
    child.setBalance();

    if (parentOfTarget == null)
    {
      this.head = child;
    }
    else if (parentOfTarget.left == targetRef)
    {
      parentOfTarget.left = child;
      parentOfTarget.setBalance();
    }
    else if (parentOfTarget.right == targetRef)
    {
      parentOfTarget.right = child;
      parentOfTarget.setBalance();
    }
  }
};

AVLTree.prototype.rightRotate = function(target, node = null)
{
  let parentOfTarget = null;
  let targetRef = null;
  let tree = null;
  let child = null;

  if (node == null)
  {
    node = this.head;
  }

  if (node)
  {
    if (node == target)
    {
      targetRef = node;
    }
    else if (node.left == target)
    {
      parentOfTarget = node;
      targetRef = node.left;
    }
    else if (node.right == target)

      parentOfTarget = node;
      targetRef = node.right;
    }
    else if (target.value < node.value)
    {
      return this.leftRotate.call(this, target, node.right);
    }
    else if (target.value > node.value)
    {
      return this.leftRotate.call(this, target, node.right);
    }

  if (targetRef)
  {
    targetRef.grandchildPromote();
    child = targetRef.left;
    tree = child.right;

    child.right = targetRef;
    targetRef.left = tree;

    targetRef.setBalance();
    child.setBalance();

    if (parentOfTarget == null)
    {
      this.head = child;
    }
    else if (parentOfTarget.left == targetRef)
    {
      parentOfTarget.left = child;
      parentOfTarget.setBalance();
    }
    else if (parentOfTarget.right == targetRef)
    {
      parentOfTarget.right = child;
      parentOfTarget.setBalance();
    }
  }

};


AVLTree.prototype.balancedAdd = function (value)
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
        if (this.balancedAdd.call(this, value, node.left))
        {
          if (node.left.balance < -1)
          {
            this.leftRotate.call(this, node.left);
            node.setBalance();
          }
          else if (node.left.balance > 1)
          {
            this.rightRotate.call(this, node.left);
            node.setBalance();
          }
          else
          {
            node.balance++;
          }
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
        if (this.balancedAdd.call(this, value, node.right ) )
        {
          if (node.right.balance < -1)
          {
            this.leftRotate.call(this, node.right);
            node.setBalance();
          }
          else if (node.right.balance > 1)
          {
            this.rightRotate.call(this, node.right);
            node.setBalance();
           }
           else
           {
            node.balance--;
           }
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

    // root node
    if (node.balance < -1)
    {
      this.leftRotate.call(this, node);
    }
    else if (node.balance > 1)
    {
      this.rightRotate.call(this, node);
    }

  }

};


AVLTree.prototype.balancedRemove = function (value, node = null)
{
  let balanceFeedback = 0;

  if (!node)
  {
    node = this.head;
  }

  if (node)
  {
    if (node.value == value )
    {
      balanceFeedback =  this.removeHelper.call(this, null, node);
    }

    else if (value < node.value)
    {
      if (node.left)
      {
        if (node.left.value == value)
        {
          balanceFeedback =  this.removeHelper.call(this, node, node.left);
        }
        else
        {
          balanceFeedback =  this.balancedRemove.call(this, value, node.left);
        }

        if (balanceFeedback)
        {
          if (node.left)
          {
            if (node.left.balance > 1)
            {
              this.rightRotate.call(this, node.left);
              node.setBalance();
            }
            else if (node.left.balance < -1)
            {
              this.leftRotate.call(this, node.left);
              node.setBalance();

            }
            else
            {
              node.balance--;
            }
           }
           else
           {
             node.balance--;
           }

        }
      }
    }

    else if (value > node.value)
    {
      if (node.right)
      {
        if (node.right.value == value)
        {
          balanceFeedback =  this.removeHelper.call(this, node, node.right);
        }
        else
        {
          balanceFeedback =  this.balancedRemove.call(this, value, node.right);
        }

        if (balanceFeedback)
        {
          if (node.right)
          {
            if (node.right.balance < -1)
            {
              this.leftRotate.call(this, node.right);
              node.setBalance();

            }
            else if (node.right.balance > 1)
            {
              this.rightRotate.call(this, node.right);
              node.setBalance();
            }
            else
            {
              node.balance++;
            }
          }
          else
          {
            node.balance++;
          }
        }
      }
    }
  }

  if (node == this.head)
  {
    if (node.balance > 1)
    {
      this.rightRotate.call(this, node);
    }
    else if (node.balance < -1)
    {
      this.leftRotate.call(this, node );
    }
  }

  return balanceFeedback;
};


AVLTree.prototype.repair = function(node  = null)
{
  if (node == null)
  {
    node = this.head;
  }

  if (node)
  {

    if (node.balance > 0 )
    {
      this.repair.call(this, node.left);

      if (node.left.balance > 1)
      {
        this.rightRotate.call(this, node.left);
        node.setBalance();
      }
      else if (node.left.balance < -1)
      {
        this.leftRotate.call(this, node.left);
        node.setBalance();
      }
    }

    else if (node.balace < 0)
    {
      this.repair.call(this, node.right);

      if (node.right.balance > 1)
      {
        this.rightRotate.call(this, node.right);
        node.setBalance();
      }
      else if (node.right.balance < -1)
      {
        this.leftRotate.call(this, node.right);
        node.setBalance();
      }
    }

    if (node == this.head)
    {
      if (node.balance > 1)
      {
        this.rightRotate.call(this, node);
      }
      else if (node.balance < -1)
      {
        this.leftRotate.call(this, node);
      }
    }
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

(
  function()
  {

    let tree = new RBTree();

    tree.add(3);
    tree.add(1);
    tree.add(5);
    tree.add(7);
    tree.add(6)
    tree.add(8)
    tree.add(9)
    tree.add(10)

    tree.display();

    // console.log(tree.isBalanced());
  }()

)