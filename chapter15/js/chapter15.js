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

  addNode(targetNode, node = null)
  {
    node = !node && this.root || node;

    if (!node)
    {
      this.root = targetNode;
    }
    else
    {
      if (targetNode.value < node.value)
      {
        if (node.left)
        {
          this.addNode.call(this, targetNode, node.left);
        }
        else
        {
          node.left = targetNode;
        }
      }
      else
      {
        if (node.right)
        {
          this.addNode.call(this, targetNode, node.right);
        }
        else
        {
          node.right = targetNode;
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

  isFull(node = null)
  {
    let isfull = false;
    node = !node && this.root || node;
    if (node)
    {
      isfull = (node.right && node.leeft) ^ (!node.right && !node.left) ;
      if (node.left)
      {
        isfull &= this.height(node.left);
      }
      if (node.right)
      {
        isfull &= this.height(node.right);
      }
    }
    return isfull;
  }

  isComplete (node = null)
  {
    let right = 0, left = 0;
    let iscomplete = false;
    node = !node && this.root || node;
    if (node)
    {
      if (node.left)
      {
        left = this.height(node.left);
      }
      if (node.right)
      {
        right = this.height(node.right);
      }
      iscomplete = left >= right;

      if (node.left)
      {
        iscomplete &= this.isComplete(node.left);
      }
      if (node.right)
      {
        iscomplete &= this.isComplete(node.right);
      }
    }
    return iscomplete;
  }


  bstRepairReinsert (node = null)
  {
    let insertNode;

    node = !node && this.root || node;

    if (node)
    {
      if (node.left)
      {
        insertNode = node.left;
        node.left = null;
        this.bstRepairReinsert.call(this, insertNode);
      }
      if (node.right)
      {
        insertNode = node.right;
        node.right = null;
        this.bstRepairReinsert.call(this, insertNode);
      }
    }


    this.addNode.call(this, node, this.root);
  }

  repair (node = null)
  {
    let repaired = false;
    let subtree = null;

    node = !node && this.root || node;

    if (node)
    {
      if (node.left)
      {
        if (node.left.value >= node.value)
        {
          repaired = true;
          subtree = node.left;
          node.left = null;
          this.bstRepairReinsert.call(this, subtree);
        }
      }

      if (node.right)
      {
        if (node.right.value < node.value)
        {
          repaired = true;
          subtree = node.right;
          node.right = null;
          this.bstRepairReinsert.call(this, subtree);
        }
      }

      if (node.left)
      {
        repaired |= this.repair.call(this, node.left);
      }
      if (node.right)
      {
        repaired |= this.repair.call(this, node.right);
      }
    }
    return repaired;
  }

  smallestDifference (node = null, min = [Number.MAX_SAFE_INTEGER])
  {
    let curr;
    node = !node && this.root || node;

    if (node.left) {
      curr = Math.abs(node.left.value - node.value);
      if (curr < min[0] )
      {
        min[0] = curr;
      }
    }
    if (node.right)
    {
      curr = Math.abs(node.right.value - node.value);
      if (curr < min[0])
      {
        min[0] = curr;
      }
    }
    if (node.left)
    {
      this.smallestDifference.call(this, node.left, min);
    }


    if (node.right)
    {
      this.smallestDifference.call(this, node.right,  min);
    }
    return min[0];
  }


  closestValue(value, node = null, closest = [0])
  {

    let diff;

    node = !node && this.root || node;

    if (node)
    {
      diff = Math.abs(value - node.value);

      if (diff < Math.abs(closest[0] - value))
      {
        closest[0] = node.value;
      }

      if (node.left)
      {
        this.closestValue(value, node.left, closest);
      }

      if (node.right )
      {
        this.closestValue(value, node.right, closest);
      }
    }
    return closest[0];
  }

  partitionAroundValue (value, node = null , prev = null)
  {
    let result;
    node = !node && this.root || node;
    if (node)
    {
      if (value < node.value)
      {
        if (node.left)
        {
          return this.partitionAroundValue(value, node.left, node);
        }
        else
        {
          result = node;
        }
      }
      else if (value > node.value)
      {
        if (node.right)
        {
          return this.partitionAroundValue(value, node.right, node);
        }
        else
        {
          result = node;
        }
      }
      else
      {
        if (prev)
        {
          if (prev.left == node)
          {
            result = node;
            prev.left = null;
          }
          if (prev.right == node)
          {
            result = node;
            prev.right = null;
          }
        }
        else
        {
          result = node;
          this.root = NULL;
        }
      }
    }
    return result;
  }

  partitionEvenly(node = null, partitionA = null, partitionB = null, count = 0)
  {
    node = !node ? this.root : node;

    if (!partitionA)
    {
      partitionA = new BST();
      partitionB = new BST();
    }

    if (node)
    {
      if (node.left)
      {
        this.partitionEvenly(node.left, partitionA, partitionB, ++count);
        node.left = null;
      }
      if (node.right)
      {
        this.partitionEvenly(node.right, partitionA, partitionB, ++count);
        node.right = null;
      }

      if (count % 2 == 0)
      {
        partitionA.addNode(node);
      }
      else
      {
        partitionB.addNode(node);
      }
    }

    if (node == this.root)
    {
      this.root = partitionA.root;
    }

    return partitionB;
  }

}

let  tree = new BST();
tree.add(32);
tree.add(17);
tree.add(28);
tree.add(23);
tree.add(29);
tree.add(49);
tree.add(2);

tree.display();

tree.root.left.right.value = 1;
tree.repair()
console.log()
// tree.display();
console.log();

tree.partitionEvenly().display();