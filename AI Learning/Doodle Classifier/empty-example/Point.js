function Point(x, y) {
    this.x = x;
    this.y = y;
    this.fCost = 0;
    this.gCost = 0;
    this.hCost = 0;
    this.neighbours =[];
    this.parent = null;
    this.wall = false;

    if (random(1) < 0.3 && !(this.x==(rows-1)&&this.y==(cols-1))) {
        this.wall = true;
    }
}

Point.prototype.Show = function (gridColor) {
    noStroke();
    fill(gridColor);

    rect(this.x * gridWidth, this.y * gridHeight, gridWidth,gridHeight);
    //circle(this.x * gridWidth + gridRadius, this.y * gridHeight + gridRadius, gridRadius*2);
}
Point.prototype.GetNeighbours = function (grid) {
    var i = this.x; var j = this.y;

    for (k = i-1; k <= i+1; k++) {
        for (l = j-1; l <= j+1; l++) {
            if ((k >= 0 && k < rows) && (l >= 0 && l < cols)) {
                if (!(l == j && k == i)) {
                    this.neighbours.push(grid[k][l]);
                }
            }
        }
    }
    return this.neighbours;

}