var d;

var gridSize = 25;
var mazeFindingSpeed = 144;
var pathfindingSpeed = 20;

var grid = [];
var stack = [];
var current;

var openSet = [], closedSet = [];
var path = [];
var start, end;

var foundPath = false;
var mazeComplete = false;

function setup() {
    createCanvas(800, 800);

    d = floor(width / gridSize);

    for (var i = 0; i < gridSize; i++) {
        for (var j = 0; j < gridSize; j++) {
            var point = new Point(i, j);
            grid.push(point);
        }
    }
    
    current = grid[0];
    current.visited = true;

    start = grid[0];
    end = grid[index(gridSize - 1, gridSize - 1)];
    openSet.push(start);

    //CreateObstacles();
    console.log(grid);
}
function draw() {

    background(51);

    //print Grid
    for (var i = 0; i < grid.length; i++) {
        grid[i].show();
    }

    //
    if(!mazeComplete) {
        frameRate(mazeFindingSpeed);

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
        else {
            mazeComplete = true;
            //save grid
        }
    }
    else {
        //Pathfinding
        frameRate(pathfindingSpeed);
        current = FindPath(openSet, closedSet, foundPath, start, end);
        if (current == null || current == undefined) current = end;
               
        DrawPath(path, current);
        if (current == end) {
            var colour = color(0, 0, 255, 100);
            current.highlight(colour);
            noLoop();
        }
    }
    var colour = color(0, 0, 255, 100);
    current.highlight(colour);
    
}
