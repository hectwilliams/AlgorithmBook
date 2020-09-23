const OCTAL = 8;
const HEXADECIIMAL =  16;
const BINARY = 2;
const dec2OctStr = function (value)
{
  let str = "";
  while (value > 0)
  {
    str = (value % OCTAL) + str;
    value = parseInt(value / OCTAL);
  }
  return "0o" + str;
}

const octStr2Val = function(str)
{
  let sum = 0;
  for (let i = 0; i < str.length; i++)
  {
    sum += parseInt(str[str.length - 1 - i]) * Math.pow(OCTAL, i);
  }
  return sum;
}

const dec2HexStr = function (value)
{
  let str = "";
  let tmp;
  while (value > 0)
  {
    tmp = value % HEXADECIIMAL;
    if (tmp > 9)
    {
      switch(tmp)
      {
        case 10:
          tmp = 'A';
          break;
        case 11:
          tmp = 'B';
          break;
        case 12:
          tmp = 'C';
          break;
        case 13:
          tmp = 'D';
          break;
        case 14:
          tmp = 'E';
          break;
        case 15:
          tmp = 'F';
          break;
      }
    }
    str = tmp + str;
    value = parseInt(value / HEXADECIIMAL);
  }
  return str;
}

const hexStr2Val = function(str)
{
  let sum = 0;
  let c, num;

  for (let i = 0; i < str.length; i++)
  {
    c =  str[str.length - 1 - i].toString().toUpperCase();
    switch(c)
    {
      case 'F':
        num = 15;
        break;
      case 'E':
        num = 14;
        break;
      case 'D':
        num = 13;
        break;
      case 'C':
        num = 12;
        break;
      case 'B':
        num = 11;
        break;
      case 'A':
        num = 10;
        break;
      default:
        num = parseInt(c);
    }
    sum += (num) * parseInt(Math.pow(HEXADECIIMAL, i));
  }
  return sum;
}

const dec2BinStr = function(value)
{
  let string = "";
  while (value  > 0 )
  {
    string += value % 2;
    value = parseInt(value/2);
  }
  return "0b" + string;
}

const binStr2Val = function(str)
{
  let sum = 0;
  for (let i = 0; i < str.length; i++)
  {
    sum += parseInt(str[str.length - 1 - i] ) * parseInt(Math.pow(BINARY, i))
  }
  return sum;
}
const swap = function(collection, i, j)
{
  let temp = collection[i];
  collection[i] = collection[j];
  collection[j] = temp;
}
const reorderWordFragment = function (arr)
{
  let minChar;
  let len = arr[0].length;
  let pos;

  for (let i = 0; i < len; i++)  //  iterate letter
  {
    minChar = 'A';
    for (let k = 0; k < arr.length; k++) //  iterate word
    {
      if (i == 0)   // first column words
      {
        if (arr[k][i] == '?')
        {
          arr[k] = arr[k].slice(0, i) +  minChar + arr[k].slice(i + 1);
        }
        // order element at k
        pos = k;
        while (pos > 0)
        {
          if (arr[pos - 1] > arr[pos])
          {
            swap (arr, pos - 1, pos)
          }
          pos--;
        }
      }
      else
      {
        if (arr[k][i] == '?')
        {
          arr[k] = arr[k].slice(0, i) +  minChar + arr[k].slice(i + 1);
        }
        else
        {
          minChar = arr[k][i]; // update min char
        }
      }

      //test for order
      if (k > 0)
      {
        if (arr[k - 1][i] > arr[k][i]  )
        {
          return null;
        }
      }
    }
  }
  return arr;
}

console.log( reorderWordFragment( ["XD?E","BDE?","?A?E"]) );
console.log (reorderWordFragment( ["BQX?","XD?E"]) );

// console.log(octStr2Val("37"));
