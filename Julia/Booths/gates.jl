function AND(a, b)
    a * b == 1 ? 1 : 0
    end
function OR(a, b)
    a + b > 0 ? 1 : 0
    end
function NOT(a)
    a == 0 ? 1 : 0
    end
function XOR(a, b)
    a != b ? 1 : 0
    end
function NAND(a, b)
    NOT(AND(a, b))
    end
function NOR(a, b)
    NOT(OR(a, b))
    end
function XNOR(a, b)
    NOT(XOR(a, b))
    end
