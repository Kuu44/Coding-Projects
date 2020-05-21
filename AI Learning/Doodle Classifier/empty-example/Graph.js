function Graph() {
    this.graph = {};
    this.nodes = [];
    this.start = null;
    this.end = null;
}
Graph.prototype.addNode = function (n) {
    //Node into array
    this.nodes.push(n);

    var title = n.value;
    //Node into hash
    this.graph[title] = n;
}
Graph.prototype.getNode = function (n) {
    var node = this.graph[n];
    return node;
}
Graph.prototype.setStart = function (title) {
    this.start = this.graph[title];
    return this.start;
}
Graph.prototype.setEnd = function (title) {
    this.end = this.graph[title];
    return this.end;
}
Graph.prototype.reset = function () {
    for (i = 0; i < this.nodes.length; i++) {
        this.nodes[i].searched = false;
        this.nodes[i].parent = null;
    }
}