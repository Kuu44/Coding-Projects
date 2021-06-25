include("gates.jl")
include("adder.jl")
include("nBitAdder.jl")

function decimalToBinary(decimal)
    str=string(decimal,base=2)
    binary=parse(Int64,str)
end
function BinaryToDecimal(binary)
    decimal = 0
    i = 0
    str=string(binary)
    for n in [1:length(str);]
        j=length(str)+1-n
        decimal += (parse(Int64, str[j]) * 2) ^ i
        i += 1
    end
    return decimal
end
function unsignedBin(decimal, leng)
    binary = decimalToBinary(abs(decimal))
    if (decimal < 0)
        return nBitAdder.twosComplement(binary, leng)
    else
        return string(decimal, base=10, pad=leng)
    end
end
function rightShift(accumulator, q, qlast, leng)
    num = string(string(accumulator, q), qlast)
    rnum = num[1]
    for i in [1:length(num);]
        rnum = string(rnum, num[i])
    end
    return rnum[1:leng], rnum[n:(2 * leng)], rnum[end]
end
function booths(num1, num2, leng)
    accumulator= "0"^leng
    qlast="0"
    m=unsignedBin(num1, leng)
    m2s=string(parse(Int64, nBitAdder.twosComplement(parse(Int64,m), leng)), base=10, pad=leng)
    q=unsignedBin(num2,leng)

    for i in [1:leng+1;]
        if q[end] != qlast
            if string(q[end], qlast) == "01"
                accumulator = string(parse(Int64, nBitAdder.Sum(parse(Int64, accumulator), parse(Int64, m))),base=10, pad=leng)
            else
                accumulator = string(parse(Int64, nBitAdder.Sum(parse(Int64, accumulator), parse(Int64, m2s))),base=10, pad=leng)
            end
        end
        accumulator, q, qlast = rightShift(accumulator, q, qlast, leng)
    end
    return string(accumulator,q)
end

println("Enter 1st decimal number: ")
    a = parse(Int64, readline())
println("Enter 2nd decimal number: ")
    b = parse(Int64, readline())
println("Enter no of bits: ")
    n = parse(Int64, readline())
if (a / abs(a) != b / abs(b))
    result = nBitAdder.twosComplement(parse(Int64, booths(a, b, n), n))
    println(string("Product(binary): -", result))
    println(string("Product(decimal): -", BinaryToDecimal(parse(Int64, result))))
else
    result = booths(a, b, n)
    println(string("Product(binary): ", result))
    println(string("Product(decimal): ", BinaryToDecimal(parse(Int64, result))))
end
