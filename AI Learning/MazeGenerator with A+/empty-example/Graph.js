function RemoveFromArray(array, element) {
    for (i = array.length - 1; i >= 0; i--) {
        if (array[i] == element) {
            array.splice(i, 1);
        }
    }
}
function GetDistanceEuclidean(pointA, pointB) {
    return dist(pointA.x, pointA.y, pointB.x, pointB.y);
}
function GetDistanceManhattan(pointA, pointB) {
    return (abs(pointA.x - pointB.x) + abs(pointA.j - pointB.j));
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

    if (!(a.neighbours.includes(b)))
        a.neighbours.push(b);
    if (!(b.neighbours.includes(a)))
        b.neighbours.push(a);
}
function FindPath(openSet, closedSet, foundPath, start, end) {
    var current;
    //while openSet not empty
    if (openSet.length > 0 && !foundPath) {

        //current = node in openSet with lowest fScore
        current = openSet[0];
        for (i = 1; i < openSet.length; i++) {
            if (openSet[i].fCost < current.fCost) {
                current = openSet[i];
            }
        }

        //if current node is end node; path is found
        if (current == end) {
            console.log("Path length is: " + path.length);
            foundPath = true;
            console.log("DONE!!");            
        }

        //remove current from openset and add to closed
        RemoveFromArray(openSet, current);
        closedSet.push(current);
        //check neighbours. if they are closed else update path
        var neighbours = current.neighbours;
        for (i = 0; i < neighbours.length; i++) {
            var neighbour = neighbours[i];

            //ignore neighbour if closed
            if (!(closedSet.includes(neighbour))) {
                var tempGCost =
                    current.gCost + GetDistanceEuclidean(neighbour, current);

                //add neighbour to openSet if not present
                if (openSet.includes(neighbour)) {
                    if (tempGCost < neighbour.gCost) {
                        neighbour.gCost = tempGCost;
                        neighbour.hCost = GetDistanceEuclidean(neighbour, end);
                        neighbour.fCost = neighbour.gCost + neighbour.hCost;
                        neighbour.parent = current;
                    }
                }
                else {
                    neighbour.gCost = tempGCost;
                    openSet.push(neighbour);
                    neighbour.hCost = GetDistanceEuclidean(neighbour, end);
                    neighbour.fCost = neighbour.gCost + neighbour.hCost;
                    neighbour.parent = current;
                }
            }
        }
    }
    return current;
}
function DrawPath(path, current) {
    path = [];
    var temp = current;
    path.push(temp);
    while (temp.parent != null) {
        path.push(temp.parent);
        temp = temp.parent;
    }
    for (var p = 0; p < path.length; p++) {
        var colour = color(255, 165, 0, 150);
        path[p].highlight(colour);
    }
}