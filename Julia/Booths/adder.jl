module Adder
    include("gates.jl")
    function Sum(a, b, c)
        XOR(XOR(a,b), c)
    end
    function Carry(a, b, c)
        OR(AND(a, b), AND(XOR(a, b), c))
    end
end
