const OCTAL = 8;
const HEXADECIIMAL =  16;

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

console.log(hexStr2Val("1F"));
// console.log(octStr2Val("37"));
