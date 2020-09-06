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

  reverse(node = null)
  {
    let left, right;
    node = !node ? this.root : node;
    if (node)
    {
      left = node.left;
      right = node.right
      node.left = right;
      node.right = left;

      if (node.left )
      {
        this.reverse(node.left);
      }
      if (node.right)
      {
        this.reverse(node.right);
      }
    }
  }

  kthBiggest(k, node = null, count = [0], result = [null])
  {
    node = !node ? this.root: node;

    if (node)
    {
      if (node.right)
      {
        this.kthBiggest(k, node.right, count, result);
      }

      count[0]++;
      if (count[0] == k)
      {
        result[0] = node.value;
      }

      if (node.left)
      {
        this.kthBiggest(k, node.left, count, result);
      }
    }

    return result;

  }

  valueForLayer(layer, node)
  {
    let result = [];
    let queueModel = [];
    let curr, depth;

    node = !node && this.root || node;
    queueModel.push( [  node, 0] );

    while (queueModel.length )
    {
      curr = queueModel[0][0] ;
      depth = queueModel[0][1];

      if (depth == layer)
      {
        result.push(curr.value);
      }

      if (curr.left)
      {
        queueModel.push([curr.left, depth + 1]);
      }
      if (curr.right)
      {
        queueModel.push([curr.right , depth + 1]);
      }
      queueModel.shift();
    }
    return result;
  }

  layerArrays (node = null)
  {
    let result = [[]];
    let queueModel = [];
    let curr = 0;
    let depth = 0;

    node = !node && this.root || node;
    queueModel.push([node , 0]);

    while (queueModel.length)
    {
      curr = queueModel[0][0];
      depth = queueModel[0][1];

      if (depth > result.length)
      {
        result.push([]);
      }

      result[depth - 1 < 0 ? 0 : depth - 1].push(curr.value);

      if (curr.left)
      {
        queueModel.push([curr.left, depth + 1]);
      }
      if (curr.right)
      {
        queueModel.push([curr.right, depth  + 1]);
      }
      queueModel.shift();
    }
    return result;
  }

}

class TrieNode
{
  constructor(value)
  {
    this.string = value;
    this.children = [];
    this.count = 0;
  }
}

class Trie
{

  constructor()
  {
    this.root = new TrieNode("");
  }

  add (str)
  {
    let pos = 0;
    let node = this.root;
    let curr;
    let inserted = 0;

    while (node.string.length != str.length)
    {
      curr = node;
      pos++;

      node.children.forEach((child) => {
        if (child.string == str.slice(0, pos).toLowerCase())
        {
          inserted |= 1;
          node = child;
        }
      });

      if (curr == node)
      {
        node.children.push( new TrieNode( (str.slice(0, pos)).toLowerCase()  ) );
        node = node.children[node.children.length - 1];
      }

    }
    return inserted == 0;
  }
  contains (str)
  {
    let node = this.root;
    let curr;
    let pos = 0;

    while (curr != node)
    {
      curr = node;
      node.children.forEach((child) => {
        if (child.string == str.slice(0, pos + 1).toLowerCase() )
        {
          pos++;
          node = child;
        }
      });
    }
    return pos == str.length;
  }

  first()
  {
    let curr, node = this.root;
    let minChar = '', currChar;
    let pos = 0;
    while (node != curr)
    {
      curr = node;
      node.children.forEach((elementNode) => {
        currChar = elementNode.string[pos];
        if (minChar == '' || currChar <= minChar)
        {
          minChar = currChar;
          node = elementNode;
        }
      });
      pos++;
    }
    return node.string;
  }

  last ()
  {
    let curr, node = this.root;
    let maxString, currString;
    let pos = 0;
    while (node!= curr)
    {
      curr = node;
      pos++;
      node.children.forEach((elementNode)=> {
        currString = elementNode.string;
        if (maxString == undefined || currString >= maxString)
        {
          node = elementNode;
          maxString = node.string;
        }
      });
    }
    return node.string;
  }

  removeAllChildNodes(node) {
    let queueModel = [node];

    while (queueModel.length)
    {
      // concat children to queue (nodes persist )
      queueModel = queueModel.concat(queueModel[0].children );
      // clear children array
      queueModel[0].children = [];
      // pop
      queueModel.shift();
    }
  }

  remove(word , node = null)
  {
    let found = 0;

    node = !node && this.root || node;

    if (!node)
    {
      return 0;
    }

    if (word == node.string)
    {
      return 1;
    }

    for (let i = 0; i < node.children.length && !found ; i++)
    {
      if (word.indexOf(node.children[i].string) == 0)
      {
        found = this.remove(word, node.children[i]);

        if (found)
        {
          if (node.children[i].string == word)  // remove target node
          {

            node.children.splice(i, 1);
          }
          else if (node.children.length == 1 && node.children[0].children.length == 0) // single child + zero nephews
          {
            node.children = [];
          }
        }
      }
    }

    return found;
  }

  size (node = null)
  {
    let count = 0;

    node = !node && this.root || node;

    if (node.children.length == 0)
    {
      return 0;
    }

    for (let i = 0; i < node.children.length; i++)
    {
      count += +(node.string.length > 0) + this.size(node.children[i]);
    }
    return count;
  }

  next (string, node = null)
  {
    let next;

    node = !node && this.root || node;

    for (let i = 0; i < node.children.length; i++)
    {
      if ( string.indexOf(node.children[i].string)  == 0)
      {
        return this.next(string, node.children[i]);
      }
    }

    for (let i = 0; i < node.children.length; i++)
    {
      if (next == undefined || node.children[i].string < next )
      {
        next = node.children[i].string;
      }
    }

    return next;
  }

}


class TrieMulti extends Trie
{
  constructor()
  {
    super();
  }
  add(string)
  {
    let node = this.root;
    let curr;
    let pos = 0;

    if (node )
    {
      while (string[pos])
      {
        curr = node;
        pos++;

        node.children.forEach( (elementNode) => {

        if (elementNode.string == string.slice(0, pos))
        {
          node = elementNode;
          node.count++;
        }

        });

        if(curr == node)
        {
          node.children.push(new TrieNode(string.slice(0, pos)));
          node = node.children[node.children.length - 1];
          node.count++;
        }

      }
    }
  }
  remove (strData, node = null)
  {
    let valueFound = false;

    node = !node && this.root || node;

    if (!node)
    {
      return;
    }

    if (node.string == strData)
    {
      return true;
    }

    for (let i = 0; i < node.children.length; i++)
    {
      if (strData.indexOf(node.children[i].string) == 0)
      {
        valueFound = this.remove(strData, node.children[i]);

        if (valueFound)
        {
          if (node.count > 1)
          {
            --node.count;
          }
          else  if (node.count == 1)
          {
            if (strData.indexOf(node.children[i])  == 0)
            {
              node.children.splice(i,1)
            }
            else if (node.children.length == 1)
            {
              if (node.children[0].children.length == 0)
              {
                node.children.splice(0,1)
                node.children = [];
              }
            }
          }
        }
      }
    }
    return valueFound;
  }

  size(node = null)
  {
    let count = 0;

    node = !node && this.root || node;

    if (!node)
    {
      return 0;
    }

    if (node)
    {
      count += node.count;
    }

    for (let i = 0; i < node.children.length; i++)
    {
      count += this.size(node.children[i]);
    }

    return count;
  }

  contains(string, node = null)
  {
    node = !node ? this.root : node;

    if (node)
    {
      if (node.string == string)
      {
        return node.count;
      }
      for (let i = 0; i < node.children.length; i++)
      {
        if (string.indexOf(node.children[i].string ) == 0 )
        {
          return this.contains(string, node.children[i]);
        }
      }
    }
    return 0;
  }

}


// let tree = new BST();
// tree.add(32);
// tree.add(17);
// tree.add(28);
// tree.add(23);
// tree.add(29);
// tree.add(49);
// tree.add(2);
// tree.display();
// console.log();

// // tree.partitionEvenly().display();
// let ll= tree.kthBiggest(3);
// console.log(tree.layerArrays());
{
  let trie = new TrieMulti();
  trie.add("hello");
  trie.add("hello");
  console.log( trie.contains("he") )

  // console.log(trie.remove('hello'));
  // console.log(trie.remove('hellw'));
  // console.log(trie.remove('hellw'));

}