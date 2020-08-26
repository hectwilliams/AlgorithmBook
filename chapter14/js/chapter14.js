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

}

const testclass = new HashMap();
testclass.add("hello", 21);
testclass.add("pick", 25);