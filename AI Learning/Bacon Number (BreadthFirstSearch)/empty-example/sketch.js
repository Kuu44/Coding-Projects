var data;
var graph;
var dropdown;

function preload() {
    data = loadJSON('kevinbacon.json');
}

function setup() {
    noCanvas();

    graph = new Graph();

    dropdown = createSelect();
    dropdown.changed(bfs);

    var movies = data.movies;

    for (var i = 0; i < movies.length; i++) {
        var movie = movies[i].title;
        var casts = movies[i].cast;
        var movieNode = new Node(movie);
        graph.addNode(movieNode);

        for (var j = 0; j < casts.length; j++) {
            var actor = casts[j];
            var actorNode = graph.getNode(actor);
            if (actorNode == undefined) {
                actorNode = new Node(actor);
                dropdown.option(actor);
            }
            graph.addNode(actorNode);            
            movieNode.addEdge(actorNode);
        }
    }
    console.log(graph);

   
}

function draw() {
    
}

function bfs() {
    graph.reset();
    var start = graph.setStart(dropdown.value());
    var end = graph.setEnd("Kevin Bacon");

    var queue = [];    
    start.searched = true;
    queue.push(start);

    while (queue.length > 0) {
        var current = queue.shift();

        if (current == end) {
            console.log("Found: ");
            console.log(current);
            break;
        }
        var edges = current.edges;
        for (i = 0; i < edges.length; i++) {
            var neighbour = edges[i];
            var search = neighbour.searched;
            if (!search) {
                neighbour.searched = true;
                neighbour.parent = current;
                queue.push(neighbour);
            }
        }
    }

    var path = [];

    path.push(end);
    var next = end.parent;
    while (next != null) {
        path.push(next);
        next = next.parent;
    }

    var text = '';
    for (i = path.length - 1; i >= 0; i--) {
        var n = path[i];
        text += n.value;
        if (i != 0) text += ' --> ';
    }
    text += "<br>BaconNumber =" + (path.length - 1) / 2;
    createP(text);
}