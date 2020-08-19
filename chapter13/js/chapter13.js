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

const test = function()
{
  a = [1,2,3,4];
  b = [5,6,7,8];
  mergeSortedArrays(a,b);
}

test();