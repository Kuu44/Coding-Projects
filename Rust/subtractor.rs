//Binary Subtractor
fn and(a: i32, b: i32)->i32{a*b}
fn or(a: i32, b: i32)->i32{if (a+b)>0 {1} else {0}}
fn not(a: i32)->i32{if a==0 {1} else {0}}
fn nand(a: i32, b: i32)->i32{not(and(a,b))}
fn nor(a: i32, b: i32)->i32{not(or(a,b))}
fn xor(a: i32, b: i32)->i32{if a==b {0} else {1}}
fn xnor(a: i32, b: i32)->i32{not(xor(a,b))}

use std::convert::TryInto;
//alternative to Python's rjust
fn adjustNumber(pair : (String,String))->(String, String){
    let l1 =pair.0.len();
    let l2 =pair.1.len();
    let mut n1 : String=String::from("");
    let mut n2 : String=String::from("");
    if l1>l2
        {
            n1=pair.0;
            n2 = fill(pair.1, l1-l2);
        }
    else if l2>l1 {
        n1 = fill(pair.0, l2-l1);
        n2=pair.1;
    }
    else {
        n1=pair.0; n2=pair.1;
    }
    return (n1,n2);
}
//fills zeros before numbers to make them equal in digits
fn fill(s : String, n: usize) -> String{
    let mut l1 = String::from("");
    for i in 0..n{
        l1.push('0');
    }
    l1.push_str(&s);
    return l1;
}
//A single digit subtractor
fn fullSubtractor(i1 : i32, i2 : i32, b : i32)->(i32, i32){
    let diff : i32 = xor(xor(i1,i2),b);
    let burrOut : i32= or(and(not(i1),i2),
                    and(b,xnor(i1,i2)));
    return (diff, burrOut);
}
//n-Bit Subtractor
fn binarySubtractor(n1 :String, n2 :String)->String{
    let mut burrow : i32 = 0;
    let mut diff :String = String::from("");
    let mut bitDiff : String = String::from("");
    let l = n1.len()-1;
    for i in 0..=l{
        let ii= l-i;
        let mut tempChar = n1.chars().nth(ii).unwrap();
        let i1 : i32 = tempChar.to_digit(10).unwrap().try_into().unwrap();
        tempChar = n2.chars().nth(ii).unwrap();
        let i2 : i32 = tempChar.to_digit(10).unwrap().try_into().unwrap();

        let out : (i32, i32) = fullSubtractor(i1,i2,burrow);
        bitDiff = out.0.to_string();
        burrow = out.1;
        diff.push_str(&bitDiff);
    }
    return diff;
}
//Some Helper functions
fn remLast(value: &str) -> &str {
    let mut chars = value.chars();
    chars.next_back();chars.next_back();
    chars.as_str()
}
fn correctPlacement(i1: String, i2: String) -> (String, String, bool){
    let mut n1 : i32 = i1.parse::<i32>().unwrap();
    let mut n2 : i32 = i2.parse::<i32>().unwrap();
    let mut inp1=i1;
    let mut inp2=i2;
    let mut sign : bool = false;
    if n1<n2 {
        let mut temp : String = inp1;
        inp1 = inp2;
        inp2 = temp;
        sign = true;
    }
    return (inp1,inp2, sign);
}
fn main(){
    let mut s1 : String = String::new();
    println!("Enter the first Number: ");
    std::io::stdin().read_line(&mut s1).unwrap();
    s1 = remLast(&s1).to_string();

    let mut s2 : String = String::new();
    println!("Enter the second Number: ");
    std::io::stdin().read_line(&mut s2).unwrap();
    s2 = remLast(&s2).to_string();

    let checked : (String, String, bool) =
            correctPlacement(s1, s2);
    s1= checked.0; s2 = checked.1;

    println!("{} - {}",s1.clone(),s2.clone());

    let finalS : (String, String)= adjustNumber((s1.clone(), s2.clone()));

    let mut result : String = binarySubtractor(finalS.0.clone(), finalS.1.clone());
    if checked.2 {
        let mut signedRes=String::from("-");
        signedRes.push_str(&result);
        result = signedRes;
        println!("{} - {} is ",finalS.1,finalS.0);
    } else {
    println!("{} - {} is ",finalS.0,finalS.1);
    }
    println!("{}",result);
}
