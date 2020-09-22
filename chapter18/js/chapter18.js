const OCTAL = 8;

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

console.log(dec2OctStr(31));
console.log(octStr2Val("37"));
