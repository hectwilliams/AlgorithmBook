
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
          if (node.balance != 0)
          {
            return 1;
          }
        }
      }
      else
      {
        node.left = new AVLNode(value);
        node.balance++;
        return 1
      }
    }
    else  if (value > node.value)
    {
      if (node.right)
      {
        if (this.add(value, node.right ) )
        {
          node.balance--;
          if (node.balance != 0)
          {
            return 1;
          }
        }
      }
      else
      {
        node.right = new AVLNode(value);
        node.balance--;
        return 1;
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

    console.log(node.value + '-' + 'bal ' + node.balance );

    if (node.right)
    {
      this.display.call(this, node.right);
    }
  }
};

AVLTree.prototype.removeHelper = function(parent, node)
{
  let runner = null, ancestor = null;
  if (node.count > 1)
  {
    node.count--;
    return true;
  }

  if (!node.left && !node.right)
  {
    if (parent == null)
    {
      this.head = null;
    }
    else if (parent.left == node)
    {
      parent.left = null;
    }
    else if (parent.right == node)
    {
      parent.right = null;
    }
  }

  else if (node.left != null && node.right == null)
  {
    if (parent == null)
    {
      this.head = node.left;
    }
    else if (parent.left == node)
    {
      parent.left = node.left;
    }
    else if (parent.right == node)
    {
      pareent.right = node.left;
    }
  }

  else if (node.right != null && node.left == null)
  {
    if (parent == null)
    {
      this.head = node.right;
    }
    else if (parent.left == node)
    {
      parent.left = node.right;
    }
    else if (parent.right == node)
    {
      parent.right = node.right;
    }
  }
  else if (node.right && node.left)
  {
    if (node.right.left == null)
    {
      node.right.left = node.left;
      if (parent == null)
      {
        this.head = node.right;
      }
      else if (parent.left == node)
      {
        parent.left = node.right;
      }
      else if (parent.right == node)
      {
        parent.right = node.right;
      }
    }
    else
    {
      runner = node.right;
      while (runner.left.left)
      {
        runner = runner.left;
      }
      ancestor = runner.left;
      runner.left = runner.left.left;

      ancestor.left = node.left;
      ancestor.right = node.right;

      if (parent == null)
      {
        this.head = ancestor;
      }
      else if (parent.left == node)
      {
        parent.left = ancestor;
      }
      else if (parent.right == node)
      {
        parent.right = ancestor;
      }
     }
  }


  return true;
};


AVLTree.prototype.remove = function(value = null, node = null)
{

  if (!node)
  {
    node = this.head;
  }

  if (node)
  {

    if (node.value == value )
    {
      return this.removeHelper(null, node);
    }

    else if (value < node.value)
    {
      if (node.left)
      {
        if (node.left.value == value)
        {
          return this.remove_helper(node, node.left);
        }
        else
        {
          return this.remove.call(this , value, node.left);
        }
      }
    }

    else if (value > node.value)
    {
      if (node.right)
      {
        if (node.right.value == value)
        {
          return this.removeHelper(node, node.right);
        }
        else
        {
          return this.remove.call(this , value, node.right);
        }
      }
    }
  }

  return false;
};


AVLNode.prototype.height = function(node = null)
{
  let lheight = 0;
  let rheight = 0;

  if (node == null)
  {
    node =  this;
  }

  if (node)
  {
    if (node.left)
    {
      lheight = 1 + this.height(node.left);
    }

    if (node.right)
    {
      rheight = 1 + this.height(node.right);
    }
  }

  if (lheight > rheight)
  {
    return lheight;
  }
  else
  {
    return rheight;
  }
};


AVLTree.prototype.height = function()
{

  return this.head.height();
};


AVLNode.prototype.isBalanced = function(node = null)
{
  let left = 0;
  let right = 0;

  if (node == null)
  {
    node = this;
  }

  if (node)
  {
    if (node.left)
    {
      left = node.left.height();
    }
    if (node.right)
    {
      right = node.right.height();
    }
  }

  if (Math.abs(left - right) > 1)
  {
    return false;
  }

  return true;

};

AVLTree.prototype.isBalanced = function(node = null)
{
  if (this.head)
  {
    return this.head.isBalanced();
  }
  return false;
};

(
  function() {
    let tree = new AVLTree();
    tree.add(10);
    tree.add(8);
    tree.add(12);

    // tree.remove(10);
    // tree.display(); // 8 12

    // tree.remove(12);
    // tree.display(); // 8 10

    //  tree.remove(8);
    // tree.display(); // 10 12

    // tree.add(11);
    // tree.add(14);
    // tree.add(4);
    // tree.add(6);

  // tree.remove(8);
  // tree.display(); // 4 6 10 11 12 14

  // tree.add(1);

  // tree.remove(4);
  // tree.display(); // 1 6 8 10 11 12 14


  // tree.remove(10);
  tree.display(); // 1 4 6 8 11 12 14
  console.log(tree.isBalanced());
  }()

)