var d;
var gridSize=40;
var grid = [];
var stack = [];
var current;

function setup() {
    createCanvas(400, 400);
    frameRate(80);

    d = floor(width / gridSize);

    for (var i = 0; i < gridSize; i++) {
        for (var j = 0; j < gridSize; j++) {
            var point = new Point(i, j);
            grid.push(point);
        }
    }
    current = grid[0];
    current.visited = true;
}

function draw() {
    background(51);
    
    for (var i=0; i < grid.length; i++) {
        grid[i].show();
    }
    current.highlight();
    //Step 1
    var next = current.checkNeighbours();
    if (next) {
        next.visited = true;
        //Step 2
        stack.push(current);
        //Step 3
        removeWalls(current, next);
        //Step 4
        current = next;
    }
    else if (stack.length > 0) {
        current = stack.pop();
    }
}