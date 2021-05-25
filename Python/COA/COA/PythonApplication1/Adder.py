from logic import *

class Adder:
    def Sum(self, a, b, c):
        return XOR(XOR(a, b), c)

    def Carry(self, a, b, c):
        return OR(AND(a, b), AND(XOR(a, b), c)

