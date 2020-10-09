
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

AVLTree.prototype.righttRotate = function(target, node = null)
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
  this.add(value);
  if (!this.head.isBalanced())
  {
    if (this.head.balance > 1)
    {
      this.righttRotate(this.head);
    }

    if (this.head.balance < -1)
    {
      this.leftRotate(this.head);
    }
  }
};
(
  function()
  {
    let tree = new AVLTree();

    tree.add(200);
    tree.add(100);
    tree.add(25);
    tree.add(120);
    tree.add(140);
    tree.add(110);
    tree.add(105);

    tree.display();
    console.log('\n');
    tree.remove(100);
    tree.display();

    console.log(tree.isBalanced());
  }()

)