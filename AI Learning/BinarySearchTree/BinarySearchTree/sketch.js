var tree;

function setup() {
    createCanvas(600, 400);
    background(51);
    tree = new Tree();

    for (var i = 0; i < 100; i++) {
        tree.addValue(floor(random(0,100)));
    }
   
    console.log(tree);
    tree.traverse(); 
}

function draw() {
    
    }