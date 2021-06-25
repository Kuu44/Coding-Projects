include("nBitAdder.jl")
function decimalToBinary(decimal)
    str=string(decimal,base=2)
    binary=parse(Int64,str)
end
println("Enter 1st decimal number: ")
    a = parse(Int64, readline())
println("Enter 2nd decimal number: ")
    b = parse(Int64, readline())
c=a*b
if c>=0
    println(string("Product(binary): ", decimalToBinary(c) ))
else
    println(string("Product(binary): ", nBitAdder.twosComplement(decimalToBinary(parse(Int64,string(c)[2:end])), length(string(decimalToBinary(c)))) ))
end
println(string("Product(decimal): ", c))
