import Adder

class nBitAdder(Adder.Adder):
    def __init__(self, n):
        self.n = n
        self.sum = None
        self.carry = None

    def Sum(self, input1, input2):
        input1 = str(input1).zfill(self.n) #pad input with zeros if small
        input2 = str(input2).zfill(self.n)
        carry = 0
        result = ""
        for i in range(self.n-1, -1, -1):
            sum = super().Sum(int(input1[i]), int(input2[i]), carry)
            carry = super().Carry(int(input1[i]), int(input2[i]), carry)
            result = str(sum)+result
        self.sum=int(result)        
        return int(result)

    def Carry(self, input1, input2):
        input1 = str(input1).zfill(self.n) #pad input with zeros if small
        input2 = str(input2).zfill(self.n)
        carry = 0
        result = ""
        for i in range(self.n-1, -1, -1):
            sum = super().Sum(int(input1[i]), int(input2[i]), carry)
            carry = super().Carry(int(input1[i]), int(input2[i]), carry)
            result = str(sum)+result
        self.carry=carry
        return int(carry)

    def Result(self, input1, input2):
        Sum(self, input1, input2)
        Carry(self, input1, input2)
        return self.sum, self.carry

if __name__=="__main__":
    nba = nBitAdder(4)
    print(nBitAdder.Result(10101, 1010))

