
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

class TrieMapNode extends TrieNode
{
  constructor(key, value)
  {
    super(value);
    this.key = key;
  }
}

class TrieMap
{
  constructor()
  {
    this.root = new TrieMapNode("", "");
  }

  add(key, value)
  {
    let curr, node = this.root;
    let pos = 0;
    let result = null;

    while (pos <  key.length)
    {
      curr = node;
      pos++;

      for (let i = 0; i < node.children.length; i++)
      {

        if (key.indexOf(node.children[i].key.slice(0, pos) ) == 0 )
        {
          node = node.children[i];
          break;
        }
      }

      if (node.key == key)
      {
        result = node.string;
        node.string = value;
        return result;
      }

      if (curr == node)
      {
        node.children.push(new TrieMapNode(key.slice(0, pos) , "") ) ;
        node = node.children[node.children.length - 1];
        if (node.key == key)
        {
          node.string = value;
        }
      }
    }
    return result;
  }

  remove(key, node = null)
  {
    let found = false;

    node = !node && this.root || node;

    if (!node)
    {
      return 0;
    }

    if (node.key == key)
    {
      return true;
    }

    for (let i = 0 ; i < node.children.length && !found; i++)
    {
      if ( key.indexOf(node.children[i].key) == 0 )
      {
        found |= this.remove(key, node.children[i]);

        console.log( node.key, node.string   )

        if (found)
        {
          if (node.children[i].key == key)
          {
            node.children.splice(i, 1);
          }
          else if (node.children.length == 1)
          {
            if (node.children[0].children.length == 0 && node.children[0].string.length == 0 )
            {
              node.children = [];
            }
          }
        }
      }
    }
    return found && true || false; ;
  }

  contains(key, node = null)
  {
    node = !node && this.root || node;

    if (!node)
    {
      return null;
    }

    if (node.key == key)
    {
      return node.string;
    }

    for(let child of node.children)
    {
      if (key.indexOf(child.key) == 0)
      {
        return this.contains(key, child);
      }
    }

    return null;
  }

  size (node = null)
  {
    let count = 0;
    node = !node && this.root || node;

    for (let i = 0; i < node.children.length; i++)
    {
      count += 1 + this.size(node.children[i]);
    }
    return count;
  }

  first()
  {
    let node = this.root;
    let currChar, minChar;
    let pos = -1;
    let result = {key: null, value: null};
    let curr = null;

    while (node != curr)
    {
      curr = node;
      pos++;
      for (let child of node.children)
      {
        currChar = child.key[pos];
        if (minChar == undefined || currChar <= minChar)
        {
          node = child;
          minChar = currChar;
        }
      }
    }
    result.key = node.key;
    result.string = node.string;
    return result;
  }

}

let trie = new TrieMap();

console.log(trie.add("hello", 'world' ));
console.log(trie.add("hello", 'world' ));
console.log("");
console.log(trie.first());
// console.log(trie.remove("hello"));

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


  // console.log(trie.remove('hello'));
  // console.log(trie.remove('hellw'));
  // console.log(trie.remove('hellw'));

}