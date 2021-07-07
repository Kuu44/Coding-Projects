package main
import "fmt"

func AND(a, b string) (c string) {
  if a=="1" && b=="1" {
    c="1"
  } else {
    c="0"
  }
  return
}
func OR(a,b string) (c string) {
  if a=="0" && b=="0" {
    c="0"
  } else {
    c="1"
  }
  return
}
func XOR(a,b string) (c string) {
  if a==b {
    c="0"
  } else {
    c="1"
  }
  return
}
func NOT(a string)(c string){
  if a=="1" {
    c="0"
  } else {
    c="1"
  }
  return
}
func Reverse(s string) string {
    runes := []rune(s)
    for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
        runes[i], runes[j] = runes[j], runes[i]
    }
    return string(runes)
}
func OneComplement(num string) string{
  var res string
  for i := 0; i<len(num); i++ {
    res+=XOR(string(num[i]),"1")
  }
  return res
}
func TwoComplement(num string) string{
  var res string
  var j int
  for i := len(num)-1; i>=0; i-- {
    if(string(num[i])!="0"){
      res+=string(num[i])
      j=i-1
      break
    }
    res+=string(num[i])
  }
  for i:=j; i>=0; i-- {
    res+=XOR(string(num[i]),"1")
  }
  return Reverse(res)
}
func CheckBinary(num string) bool{
  for i:=0;i<len(num);i++ {
    if string(num[i])!="1" && string(num[i])!="0" {
      return false
    }
  }
  return true
}
func ZFill(str string, n int, filler ...string) (string) {
  zeros:=n-len(str)
  toFill:=""
  if len(filler)>0 {
    toFill=filler[0]
  } else {
    toFill="0"
  }
  final:=""
  for i:=0; i<zeros; i++ {
    final+=toFill
  }
  return (final+str)
}
func SameLength(str1, str2 string)(string, string){
  unequal := len(str1)-len(str2)
  if unequal<0 {
    str1=ZFill(str1, len(str2))
  } else {
    str2=ZFill(str2, len(str1))
  }
  return str1, str2
}
func Add(num1, num2 string)(string){
  size:=len(num1)
  sum:=""
  carry:="0"
  for j := size-1; j>=0; j-- {
    sum+=XOR( XOR( string(num1[j]), string(num2[j]) ), carry)
    carry=OR( AND( string(num1[j]), string(num2[j]) ),
    AND( XOR( string(num1[j]), string(num2[j]) ), carry ) )
  }
  return Reverse(sum)
}
func EqualLength(str1, str2 string) (string, string) {
  unequal:= len(str1)-len(str2)
  if unequal<0 {
    str1 = ZFill(str1, len(str2), string(str1[0]))
  } else {
    str2 = ZFill(str2, len(str1), string(str2[0]))
  }
  return str1, str2
}
func NegNumber(num string)(bool){
  if string(num[0])=="1" {
    return true
  } else {
    return false
  }
}
func ShiftLeft(acc, dividend string) (string, string) {
 acc=acc[1:len(acc)]+ string(dividend[0])
 dividend=dividend[1:len(dividend)]+"1"
 return acc, dividend
}
func Restoring(dividend, divisor string)(string, string) {
  acc:=""
  restore:=""
  acc=ZFill(acc, len(dividend))
  restore=ZFill(restore, len(dividend))
  negDivisor:=TwoComplement(divisor)
  for i:=len(divisor)-1; i>=0; i-- {
    acc, dividend = ShiftLeft(acc, dividend)
    restore=acc
    acc=Add(acc, negDivisor)
    if NegNumber(acc) {
      acc=restore
      dividend=dividend[0:len(dividend)-1]+"0"
    }
  }
  return acc, dividend
}
func AddSubtract(acc, divisor string, performSubtract bool) (res string) {
  if performSubtract {
    res=Add(acc, TwoComplement(divisor))
  } else {
    res = Add(acc, divisor)
  }
  return
}
func NonRestoring(dividend, divisor string) (accumulator, div string) {
  accumulator=""
  accumulator=ZFill(accumulator, len(dividend))
  performSubtract:=true
  for i:=0; i<len(divisor); i++ {
    accumulator, dividend = ShiftLeft(accumulator, dividend)
    accumulator = AddSubtract(accumulator, divisor, performSubtract)
    if NegNumber(accumulator) {
      performSubtract = false
      dividend = dividend[0:len(dividend)-1]+"0"
    } else {
        performSubtract = true
    }
    if (i==len(divisor)-1) && (NegNumber(accumulator)) {
      accumulator = Add(accumulator, divisor)
    }
  }
  div=dividend
  return
}
func main(){
  fmt.Println("Gib 🔪")
  num1:="1000"
  num2:="10"
  fmt.Scanln(&num1)
  fmt.Scanln(&num2)
  num1, num2 = SameLength(num1, num2)
  if CheckBinary(num1) && CheckBinary(num2) {
    remainder, quotient := Restoring(num1, num2)
    fmt.Println("Restoring:")
    fmt.Printf("Quotient: %s, Remainder: %s\n",quotient, remainder)
    remainder, quotient = NonRestoring(num1, num2)
    fmt.Println("Non Restoring:")
    fmt.Printf("Quotient: %s, Remainder: %s\n",quotient, remainder)
  } else {
    fmt.Println("Gib Binary 🔪")
  }
}
