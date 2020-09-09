class ELVertex
{
  constructor(value, id)
  {
    this.value = value;
    this.id = id;
  }
};

class ELGraph
{
  constructor()
  {
    this.vertexList = [];
    this.edgeList = [];
  }

  display()
  {
    console.log( "vertex ", this.vertexList);
    console.log( "edge ",  this.edgeList);
  }

  addVertex (value)
  {
    this.vertexList.push(new ELVertex(value, this.vertexList.length ));
    return this.vertexList.length - 1;
  }

  removeVertex(id)
  {
    let index = this.vertexList.findIndex( (ele) => ele.id == id );

    if (index != -1)
    {
      this.vertexList.splice(index, 1);
    }

    // TODO REEMOVE id in edge list array
    return index != -1;
  }

};

{
  let graph = new ELGraph ();
  graph.addVertex(200);
  graph.addVertex(2020);
  console.log(graph.removeVertex(2))
  // graph.display()

}