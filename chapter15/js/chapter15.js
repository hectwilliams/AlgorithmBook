class BSTNode
{
  constructor(value)
  {
    this.value = value;
    this.parent = null;
    this.left = null;
    this.right = null;
  }
}

class BST
{
  constructor()
  {
    this.root = null;
  }

  display(node = null)
  {
    node = (!!node && node) || this.root;

    if (node)
    {
      if (node.left)
      {
        this.display.call(this, node.left);
      }

      console.log(' %d | ', node.value)


      if (node.right)
      {
        this.display.call(this, node.right);
      }
    }
  }

  add(value, node = null)
  {
    node = !!node && node || this.root;

    if (node == null)
    {
      this.root =new BSTNode(value);
    }
    else
    {
      if (value < node.value )
      {
        if (node.left)
        {
          this.add.call(this, value, node.left);
        }
        else
        {
          node.left = new BSTNode(value);
        }
      }
      else
      {
        if (node.right)
        {
          this.add.call(this, value, node.right);
        }
        else
        {
          node.right = new BSTNode(value);
        }
      }
    }
  }

  static removeSuccessor (node = null)
  {
    let prev = node;

    if (node == null)
    {
      return null;
    }
    if (node.right)
    {
      node = node.right;
      while (node.left)
      {
        prev = node;
        node = node.left;
      }
    }

    if (prev.left == node)
    {
      prev.left = null;
    }
    else
    {
      prev.right = null;
    }

    return node;
  }

  remove(value, node = null, prev = null)
  {

    let successor;
    node = (!!node && node) || this.root;

    if (!node)
    {
      return null;
    }

    if (node.value == value )
    /* found target */
    {
      if (node.left && node.right)
      /*  full node */
      {
        successor = BST.removeSuccessor(node);
        successor.left = node.left;
        successor.right = node.right;
        if (prev == null)
        {
          this.root = successor;
        }
        else
        {
          if (prev.left == node)
          {
            prev.left = successor;
          }
          else
          {
            prev.right = successor;
          }
        }
      }
      else if (!!node.left ^ !!node.right)
      /*  1 child */
      {
        if (prev == null)
        {
          this.root =  !node.left && node.right || node.left;
        }
        else
        {
          if (prev.left == node)
          {
            prev.left = !node.left && node.right || node.left;
          }
          else
          {
            prev.right = !node.left && node.right || node.left;
          }
         }
      }
      else if (node.left === null && node.right === null)
      /*  0 child */
      {
        if (prev == null)
        {
          this.root = null;
        }
        else
        {
          if (prev.left == node)
          {
            prev.left = null;
          }
          else
          {
            prev.right = null;
          }
        }
        node = null;

      }
    }
    else
    {
      if (value < node.value)
      {
        if (node.left)
        {
          this.remove.call(this, value, node.left, node);
        }
      }
      else if ( value >= node.value)
      {
        if (node.right)
        {
          this.remove.call(this, value ,node.right, node);
        }
      }
    }
  }

  height(node = null)
  {
    let left = 0, right = 0;
    node = !!node && node || this.root;
    if (node.left)
    {
      left = 1 + this.height.call(this, node.left);
    }
    if (node.right)
    {
      right = 1 + this.height.call(this,node.right);
    }
    return left == right && right || left;
  }

 }

var bst = new BST();
bst.add(30);
bst.add(21);
bst.add(17);
bst.add(68);
bst.display();
bst.remove(68);

console.log()

bst.display();
