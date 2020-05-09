function Point(x, y) {
    this.x = x;
    this.y = y;
    this.fCost = 0;
    this.gCost = 0;
    this.hCost = 0;
    this.neighbours =[];
    this.parent = null;
}

Point.prototype.Show = function (gridColor) {
    noStroke();
    fill(gridColor);
    rect(this.x * gridWidth, this.y * gridHeight, gridWidth - 1, gridHeight - 1);
}
Point.prototype.GetNeighbours = function (grid) {
    var i = this.x; var j = this.y;

    if (i > 0)
        this.neighbours.push(grid[i - 1][j]);
    if (i < rows - 1)
        this.neighbours.push(grid[i + 1][j]);
    if (j > 0)
        this.neighbours.push(grid[i][j - 1]);
    if (j < cols - 1)
        this.neighbours.push(grid[i][j + 1]);
    return this.neighbours;

}