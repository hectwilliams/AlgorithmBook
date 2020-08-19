const interleaveArrays = function (a,b)
{
  let result = [];
  let index = [0, 0] ;

  while (index[0] + index[1] < a.length + b.length)
  {
    if (index[0] < a.length)
    {
      result.push(a[index[0]++ ]);
    }
    if (index[1] < b.length)
    {
      result.push(b[index[1]++ ]);
    }
  }

  console.log(result);
  return result;
}

const mergeSortedArrays = function (a, b)
{
  let result = [];
  let idx_a = 0, idx_b = 0;

  while (idx_a + idx_b < a.length + b.length)
  {
    if (idx_a  < a.length && idx_b < b.length)
    {
      if (a[idx_a] < b[idx_b ])
      {
        result.push(a[idx_a++]);
      }
      else if (b[idx_b] < a[idx_a ])
      {
        result.push(b[idx_b++]);
      }
      else
      {
        result.push(b[idx_b++]);
        result.push(a[idx_a++]);
      }
    }
    else if (idx_a < a.length)
    {
      result.push(a[idx_a++]);
    }
    else if (idx_b < b.length)
    {
      result.push(b[idx_b++]);
    }
  }
}

const minThreeWayRange = function(collection)
{
  let mins = [null, null, null];
  let result = null;

  for (let i = 0; i< collection.length; i++)
  {
    for (let k = 0; k < collection[i].length; k++)
    {
      if (mins[i] == null || collection[i][k] < mins[i])
      {
        mins[i] = collection[i][k]
      }
    }
  }

  for (let i = 0; i < 3; i++) {
    let arr = collection[i];
    let min_set = mins.slice(0, i).concat(mins.slice(i + 1))

    arr.forEach( (num, index) =>{
      if (num > min_set[0] && num < min_set[1])
      {
        if (result == null)
        {
          result = min_set;
        }

        if (min_set[1] - min_set[0] < result[1] - result[1])
        {
          result = min_set;
        }
      }
    });
  }
  return result;
}

const intersectSortedArray = function(a,b, cb = ()=>{})
{
  let result = [];
  let pos = [0, 0];

  while (1)
  {

    cb (result, pos);
    if (pos[0] < a.length && pos[1] < b.length)
    {
      if ( a[pos[0]]  < b[pos[1]] )
      {
        pos[0] += 1;
      }
      else if ( b[pos[1]] < a[pos[0]] )
      {
        pos[1] += 1;
      }
      else
      {
        result.push(a[pos[0]]);
        pos[0] += 1;
        pos[1] += 1;
      }
    }
    else
    {
      break;
    }
  }

  return result;
}

const intersectSortedArrayDedupe = function(a,b)
{
  function callback(arr, pos)
  {
    if (arr.length)
    {
      if (pos[0] < a.length)
      {
        if (arr[arr.length - 1] == a[pos[0]] )
        {
          pos[0]++;
        }
      }

      if (pos[1] < b.length)
      {
        if (arr[arr.length - 1] == b[pos[1]] )
        {
          pos[1]++;
        }
      }
    }
  }

  return intersectSortedArray(a, b, callback);
}

const test = function()
{
  a = [1,2,2,2,7];
  b = [2,2,6,6,7];
  x = intersectSortedArrayDedupe(a,b);
  console.log(x);
}

test();