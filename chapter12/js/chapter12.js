var bubbleSort = function(collection = [])
{
  for (let i = 0; i < collection.length - 1; i++)
  {
    for (let k = 0; k < collection.length - i - 1; k++)
    {
      if (collection[k] > collection[k + 1])
      {
        let tmp = collection[k];
        collection[k] = collection[k + 1];
        collection[k + 1] = tmp;
      }
    }
  }
};


function bubbleSort_test()
{
  let collection  = [5, 4,3,2,1];
  bubbleSort(collection);
  console.log(collection);
};



bubbleSort_test()


