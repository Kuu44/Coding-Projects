module nBitAdder
    include("gates.jl")
    include("adder.jl")
    function Add(num1::Int64, num2::Int64)
        s = ""
        cOut = 0
        n1 = string(num1)
        n2 = string(num2)
        n = length(n1) > length(n2) ? length(n1) : length(n2)
        n1 = string(num1,base=10,pad=n)
        n2 = string(num2,base=10,pad=n)

        for i in [1:n;]
         j=n+1-i
         s = string(string(Adder.Sum(parse(Int64, n1[j]), parse(Int64,n2[j]), cOut)), s)
         cOut = Adder.Carry(parse(Int64, n1[j]), parse(Int64, n2[j]), cOut)
        end
        return string(string(cOut), string(parse(Int64,s), base=10, pad=n))
    end
    function Sum(num1::Int64, num2::Int64)
        return Add(num1, num2)[2:end]
    end
    function twosComplement(num::Int64, length::Int64)
        n=string(num,base=10,pad=length)
        numb=""
        for i in n
            numb=string(numb, string(NOT(parse(Int64, i))))
        end
        oneComp = parse(Int64, numb)
        twoComp = Sum(oneComp, 1)
        return twoComp
    end
end
