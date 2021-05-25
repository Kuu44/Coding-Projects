from logic import *

class Adder:
    def Sum1(self, a, b, c):
        return XOR(XOR(a, b), c)

    def Carry1(self, a, b, c):
        return OR(AND(a, b), AND(XOR(a, b), c))

class nBitAdder(Adder):
    def __init__(self, n):
        super().__init__()
        self.n = n
        self.sum = None
        self.carry = None

    def Sum(self, input1, input2):
        input1 = str(input1).zfill(self.n) #pad input with zeros if small
        input2 = str(input2).zfill(self.n)
        carry = 0
        result = ""
        for i in range(self.n-1, -1, -1):
            sum = super().Sum1(int(input1[i]), int(input2[i]), carry)
            carry = super().Carry1(int(input1[i]), int(input2[i]), carry)
            result = str(sum)+result
        self.sum=int(result)        
        return int(result)

    def Carry(self, input1, input2):
        input1 = str(input1).zfill(self.n) #pad input with zeros if small
        input2 = str(input2).zfill(self.n)
        carry = 0
        result = ""
        for i in range(self.n-1, -1, -1):
            sum = super().Sum1(int(input1[i]), int(input2[i]), carry)
            carry = super().Carry1(int(input1[i]), int(input2[i]), carry)
            result = str(sum)+result
        self.carry=carry
        return int(carry)

    def Result(self, input1, input2):
        self.Sum(input1, input2)
        self.Carry(input1, input2)
        return self.sum, self.carry

if __name__=="__main__":
    size=input("Input the bit size of your adder: ")
    input1=input("Enter the first number: ")
    input2=input("Enter the second number: ")
    nba = nBitAdder(int(size))
    print(nba.Result(int(input1), int(input2)))


