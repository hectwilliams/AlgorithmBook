String.prototype.hashCode = function()
{
  let hash = 0;
  let code;

  for (let i = 0; i < this.length; i++)
  {
    code = this.charCodeAt(i);
    hash += code;
  }

  return hash;
}

class HashMap
{
  constructor(cap = 10)
  {
    this.capacity = cap;
    this.size = 0;
    this.table = [];
    while(cap-- > 0)
    {
      this.table.push([]);
    }
  }

  add(key, value)
  {
    let index = key.hashCode() % this.capacity;
    let collection = this.table[index];
    let pair = {key, value};

    if (!collection)
    {
      this.table[index] = [];
      this.table[index].push(pair);
    }
    else
    {
      for (obj of collection)
      {
        if (obj.key == key && obj.value == value)
        {
          return;
        }
      }
      collection.push(pair)
    }
  }

  empty ()
  {
    return this.size == 0;
  }

  find (key)
  {
    let index = key.hashCode() % this.capacity;
    let collection = this.table[index];
    let result = [];

    for (obj of collection)
    {
      result.push(obj.value);
    }
    return result;
  }

  remove (key)
  {
    let index = key.hashCode() % this.capacity;
    let collection = this.table[index];
    let pos = 0;
    let result = null;

    for (; pos < collection.length ; pos++)
    {
      if (collection[pos].key == key)
      {
        this.size--;
        result = collection[pos].value;
        break;
      }
    }

    if (pos < collection.length)
    {
      collection.splice(pos,1)
    }
    return result;
  }

  loadFactor()
  {
    return this.size  / this.capacity;
  }

  grow ()
  {
    let increase = this.capacity - Math.floor(this.capacity * 0.50);
    let buckent_index;
    let code;
    let pair;

    this.capacity += increase;
    while (increase-- > 0)
    {
      this.table.push([]);
    }

    for (let i = 0; i < this.capacity; i++)
    {
      buckent_index = 0;
      while (buckent_index < this.table[i].length)
      {
        pair = this.table[i][buckent_index];
        code = pair.key.hashCode();
        if (code % this.capacity != i )
        {
          this.table[i].splice(buckent_index, 1);
          this.add(pair.key, pair.value);
        }
        else
        {
          buckent_index++;
        }
      }
    }

  }

}

const testclass = new HashMap();
testclass.add("hello", 21);
testclass.add("pick", 25);
console.log(testclass.table);
console.log();
testclass.grow();
console.log(testclass.table);
