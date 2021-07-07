package main

import (
  kuu "fmt"
  adi "os"
  C "strconv"
  "strings"
)

func main()  {
  // kuu.Println("Hello little boi")
  // kuu.Println(filePrint("You are ~~shit~~ a good man", "Nisan.txt"))
  //
  // var arr [4]int
  // _=arr
  // //a5 := [...]char{'H','e','l','l','o',' ','T','h','e','r','e'}
  //
  // p, r := pointerTaime()
  // defer kuu.Printf("P is: %d and R is %d",*p,*r)
  // kuu.Println("Nisan is a _Good man_")
  // defer kuu.Println("To not mod a number: ",
  //   func(a,b int) int{
  //     return a-(a/b)
  //   }(10,2))
  // kuu.Println("I am 15 yrs young")
  for i, j := range []string{"Y","Are","You","Reading","This"} {
    kuu.Println(i,": ",j)
  }
  str:=""
  for _,j := range "Hello" {
    str+=string(j)
    kuu.Println(str)
  }
  a:="1"
  b:="2"
  A, _:=C.Atoi(a)
  B, _:=C.Atoi(b)
  kuu.Println(C.Itoa(A+B)+" is the result")
  kuu.Println(strings.Repeat("0",5))
  stri:="HelloThere"
  for i,_ := range stri {
    k:=stri[i]
    kuu.Printf("%c: %x %v %T %d\n",k,k,k,k,k)
  }
}
func filePrint(s string, fileName string) (str string){
file, _ := adi.Create(fileName)
    kuu.Fprint(file, s)
    file.Close()
  str=s
  return
}
func pointerTaime()(p, r *int){
  p=new(int) //Bruh, new nai bhando rahexa
  r1 := -2
  r = &r1
  return
}
