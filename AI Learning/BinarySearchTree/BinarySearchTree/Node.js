var space = 40;

function Node(value,x,y,level) {
    this.value = value;
    this.left = null;
    this.right = null;
    this.x = x;
    this.y = y;
    this.level = level;
}

Node.prototype.addNode = function (n) {
    if (n.value < this.value) {
        if (this.left == null) {
            this.left = n;
            this.left.level = (this.level + 1);
            this.left.x = this.x - width / pow(2,this.left.level);
            this.left.y = this.y + space / 2;
        }
        else {
            this.left.addNode(n);
        }
    }
    else if (n.value > this.value) {
        if (this.right == null) {
            this.right = n;            
            this.right.level = (this.level + 1);
            this.right.x = this.x + width / pow(2,this.right.level);
            this.right.y = this.y + space / 2;
        }
        else {
            this.right.addNode(n);
        }
    }
}

Node.prototype.visit = function (parent) {
    if (this.left != null) {
        this.left.visit(this);
    }
    console.log(this.value);
    fill(255);
    noStroke();
    textAlign(CENTER);
    text(this.value, this.x, this.y);

    stroke(255);
    noFill();
    ellipse(this.x, this.y, 20, 20);
    line(parent.x, parent.y, this.x, this.y);
    if (this.right != null) {
        this.right.visit(this);
    }
}

Node.prototype.search = function (val) {
    if (this.value == val) {
        return this;
        console.log("found" + val);
    }
    else if (val< this.value && this.left != null) {
        return this.left.search(val);
    }
    else if (val>this.value && this.right != null) {
        return this.right.search(val);
    }
}