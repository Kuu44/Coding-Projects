#Variable types

stringVar="Hello there!" # 'Hello'
intVar=123
#longVar=123L
floatVar=3.14
listVar=[0,12]
tupleVar=(0,1,2)
fileVar=open("PythonApplication1.py","r");

#adding shit
a="yo"
b="boi"
c=a+b
print(c)

# Commenting
""" This is how you do a multi
line comment
"""
#This is not recommended, this isn't acutally a comment
#But a text constant of the text between the quotes

##Keywords
#False	await	else	import	pass
#None	break	except	in	raise
#True	class	finally	is	return
#and	continue	for	lambda	try
#as	def	from	nonlocal	while
#assert	del	global	not	with
#async	elif	if	or	yield
#Details: https://www.programiz.com/python-programming/keyword-list

#To print the list of keywords
import keyword
print(keyword.kwlist)

#conditionals
a = 2
if a==1:
    print("less")
elif a<2:
    print("aww ye")
else:
    print("nawww")


#Math
a=5
b=10
print(a+b) #Add
print(a-b) #Subtract
print(a*b) #Multiply
print(a/b) #Divide
print(a**b)#Exponential

#Lists 

emptyList =[]
list1 = ["one, two, three, four, five"]
numList = [1,2,3,4,5]
mixList =["yellow","red","blue","green","black"]
print(mixList[0])
print(mixList[1])
print(mixList+numList)

#Set
a={1,2,3,4,4,2,7,8} #Doesn't care about order or repetition
print(a)

#Dictionary
c = {"name":"Kuu"}
print(c["name"])

#Loops
computerBrands =["apple","asus","dell","samsung"]

for brands in computerBrands:
    print(brands)

i=0    
while i<len(computerBrands):
    print(computerBrands[i])
    i=i+1

#functions
def shout():
    term=input("What do you want to call Nisan?")
    return "Nisan is a "+term

print(shout())

#Objects
class Bitch:
    def __init__(self): #constructor
        print("A Bitch has arrived")

class Nisan(Bitch): #Derived Class
    def __init__(self):
        super().__init__()
        print("This bitch is named Nisan")
        
p = Nisan()

#Libraries
import math

print(math.pi)


