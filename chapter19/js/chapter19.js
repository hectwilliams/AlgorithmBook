
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
  this.balamce = 0;
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
        return this.add(value, node.left);
      }
      else
      {
        node.left = new AVLNode(value);
      }
    }
    else  if (value > node.value)
    {
      if (node.right)
      {
        return this.add(value, node.right );
      }
      else
      {
        node.right = new AVLNode(value);
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
    console.log(node.value);
    if (node.right)
    {
      this.display.call(this, node.right);
    }
  }
};

(
  function() {
    let tree = new AVLTree();
    tree.add(8);
    tree.add(10);
    tree.add(12);
    tree.display();
  }()
)