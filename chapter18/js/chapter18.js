const OCTAL = 8;
const HEXADECIIMAL =  16;
const BINARY = 2;
const WORD_SIZE = 32;
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
    string = value % 2 + string;
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

const countInBinary = function(value)
{
  let counter = 0;
  let max = parseInt (Math.log2(value));
  max = Math.pow(2, value);

  while (counter < max)
  {
    console.log( counter ,dec2BinStr(counter++));

  }
}

const countSetBits = function(value)
{
  let acc = 0;
  while (value > 0)
  {
    acc += value % 2;
    value = parseInt(value / 2);
  }
  return acc;
}

const reverseBits = function (value)
{
  let lb, rb;
  for (let i = 0; i < parseInt(WORD_SIZE / 2); i++)
  {
    lb = !!((1 << (WORD_SIZE - 1 - i)) & value) ;
    rb = !!((1 << i) & value) ;

    value &= ~(1 << (WORD_SIZE - 1 - i) ) & ~(1 << i);

    value |= (lb << i);
    value |= (rb << (WORD_SIZE - 1 - i));
  }
  return value;
}

const encode32 = function (arr)
{
  let sum = 0;
  for (let i = 0 ; i < 4; i++)
  {
    sum |= ( arr[i] ) << (4 - 1 - i)*8;
  }
  return sum;
}

const decode32 = function(value)
{
  let arr = [];
  for (let i = 0; i < 4; i++)
  {
    arr.unshift(  (value & (0xFF << 8 * i) ) >> 8 * i    );
  }
  return arr;
}

const encodeBit = function(bit, bitPosition, value)
{
  if (bitPosition < 32 && bitPosition>=0)
  {
    value &= ~(1 << bitNumber);
    value |= (bit << bitNumber);
  }
  return value;
}


const decodeBit = function (bitPosition,  value)
{
  let bit = -1;

  if (bitPosition < 32 && bitPosition >=0 )
  {
    bit = (value & (1 << bitNumber)) >> bitNumber;
  }
  return bit;
}

const radixSort2 = function (arr = [])
{
  let collection = [], bucket = [];

  for (let i = 0; i < 32; i++)
  {
    collection.push([]);
  }
  collection[0] = collection[0].concat(arr);

  for (let bitPos = 0; bitPos < 32; bitPos++)
  {
    for (let i = 0; i < 32; i++)
    {
      bucket.push([]);
    }
    for (let row = 0; row < collection.length ;  row++)
    {
      for (let j = 0; j < collection[row].length; j++)
      {
        if (!! ( collection[row][j] & (1 << bitPos) ) )
        {
          bucket[bitPos].push( collection[row][j]);
        }
        else
        {
          bucket[row].push( collection[row][j]);
        }
      }
    }
    collection = bucket;
    bucket = [];
  }

  collection = collection.reduce( (acc, ele) => {
    return acc.concat(ele);
  }, []);

  for (let i = 0; i < collection.length; i++)
  {
    arr[i] = collection[i];
  }
}

const sevenSegment = {
  0b01110111: 0,
  0b00100100: 1,
  0b01011101: 2,
  0b01101101: 3,
  0b00101110: 4,
  0b01101011: 5,
  0b01111011: 6,
  0b00100101: 7,
  0b01111111: 8,
  0b00101111: 9
};


const LED2Numeral = function(ledByte)
{
  return sevenSegment[ledByte];
}

const Int2LED = function(twoByyte)
{
  let res = [];
  let tmp;

  while (twoByyte > 0)
  {
    tmp = twoByyte % 10;
    for (let key in sevenSegment  )
    {
      if (tmp === sevenSegment[key])
      {
        res.push(key)
      }
    }
    twoByyte = parseInt(twoByyte / 10);
  }
  return res;
}

console.log(Int2LED(85210) );