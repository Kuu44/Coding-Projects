def AND(input1, input2):
    return input1 * input2    

def OR(input1, input2):
    if input1 + input2 > 0:
        return 1
    else:
        return 0

def NOT(input1):
    return 1 if input1 == 0 else 0

def XOR(input1, input2):
    return 1 if input1 != input2 else 0

def NAND(input1, input2):
    return NOT(AND(input1, input2))

def NOR(input1, input2):
    return NOT(OR(input1, input2))

