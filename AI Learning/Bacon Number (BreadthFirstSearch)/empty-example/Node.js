function Node(value) {
    this.value = value;
    this.edges = [];
    this.searched = false;
    this.parent = null;
}

Node.prototype.addEdge = function (neighbour) {
    //Link current node to neighbour
    this.edges.push(neighbour);
    //Link neighbour to current node
    neighbour.edges.push(this);
}