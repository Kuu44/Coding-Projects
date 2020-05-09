function Point(x, y) {
    this.x = x;
    this.y = y;

    //top, right, bottom, left
    this.walls = [1, 1, 1, 1];

    this.visited = false;

    this.neighbours = [];
}
Point.prototype.highlight = function () {
    noStroke();
    fill(0, 0, 255, 100);
    rect(this.x*d, this.y*d, d, d);
}
Point.prototype.show=function() {
    var x = this.x * d;
    var y = this.y * d;

    stroke(255);

    if (this.walls[0]) {//top
        line(x    , y    , x + d, y    );
    }
    if (this.walls[1]) {//right
        line(x + d, y    , x + d, y + d);
    }
    if (this.walls[2]) {//bottom
        line(x + d, y + d, x    , y + d);
    }
    if (this.walls[3]) {//left
        line(x    , y + d, x    , y    );
    }

    if (this.visited) {

        noStroke();
        fill(255, 0, 255,100);
        rect(x, y, d, d);
    }
}

function index(i, j) {
    if (i < 0 || j < 0 || j > gridSize - 1 || i > gridSize - 1) {
        return -1;
    }
    return (j + i * gridSize);
}

Point.prototype.checkNeighbours = function () {
    var i = this.x;
    var j = this.y;
    var neighbours = [];

    var top    = grid[index(i, j - 1)];
    var right  = grid[index(i + 1, j)];
    var bottom = grid[index(i, j + 1)];
    var left   = grid[index(i - 1, j)];

    if (top && !top.visited) {
        neighbours.push(top);
    }
    if (right && !right.visited) {
        neighbours.push(right);
    }
    if (bottom && !bottom.visited) {
        neighbours.push(bottom);
    }
    if (left && !left.visited) {
        neighbours.push(left);
    }

    this.neighbours = neighbours;

    if (neighbours.length > 0) {
        var r = floor(random(0, neighbours.length));
        return neighbours[r];
    }
    else {
        return undefined;
    }
}
function removeWalls(a, b) {
    var x = a.x - b.x;
    var y = a.y - b.y;

    if (x === 1) {
        a.walls[3] = false;
        b.walls[1] = false;
    }
    else if (x === -1) {
        a.walls[1] = false;
        b.walls[3] = false;
    }
    if (y === 1) {
        a.walls[0] = false;
        b.walls[2] = false;
    }
    else if (y === -1) {
        a.walls[2] = false;
        b.walls[0] = false;
    }
}