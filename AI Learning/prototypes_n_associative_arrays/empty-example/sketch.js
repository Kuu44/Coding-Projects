function Particle() {
    this.x = 100;
    this.y = 99;
}

function Confetti() {
    Particle.call(this);
    this.col = color(255, 255, 0);
}

Particle.prototype.show = function () {
    stroke(255);
    strokeWeight(8);
    point(this.x, this.y);
}

Particle.prototype.update = function () {
    this.x += random(-5, +5);
    this.y += random(-5, +5);
}

Confetti.prototype = Object.create(Particle.prototype);
Confetti.prototype.constructor = Confetti;

Confetti.prototype.show = function () {
    stroke(this.col);
    noFill();
    strokeWeight(8);
    square(this.x, this.y, 50);
}


var p;
var v;
var c;

p5.Vector.prototype.double = function () {
    this.x *= 2;
    this.y *= 2;
    this.z *= 2;
}

function setup() {
  // put setup code here
    createCanvas(640, 480);

    p = new Particle();
    v = createVector(3, 4);
    c = new Confetti();
    
    console.log(p);
    console.log(c);
    console.log(dict);
}

function draw() {
    background(0);
    p.update();
    p.show();
    c.update();
    c.show();
}

//-------------------------//
//Associative Arrays
//Different ways to assign values to objects in JavaScript

var dict = {}; //Simplest object creation method
dict.rainbow = 6;
dict["can't"] = 69;
dict[96] = 696;
dict['69'] = 44;
var word = "heart";
dict.word = 6969;
dict[word] = 6969;//element name is actually "heart"
