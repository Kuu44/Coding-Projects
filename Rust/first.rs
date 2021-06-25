// let x : i32 = {
//     let y :i32 = 69;
//     let z : i32 = 69;
//     y + z
// };
// there's i8, i16, i32, i64, i128
//    also u8, u16, u32, u64, u128 for unsigned

struct Info {
    x : char,
    y : i32,
}

fn main(){
    let pair : (char, u64) = ('k', 69);
    println!("{}", greet(pair));

    let mut v1 = vec![1, 2,3];
    v1.push(4);

    let i1 = Info{x : 'j', y : 5};
    let i2 = Info{ y: 69, ..i1};

    for i in v1{
        println!("Nisan is a bitch");
    }
}
fn greet(pair: (char, u64)) -> u64 {
    println!("{}", pair.0);
    pair.1
}
