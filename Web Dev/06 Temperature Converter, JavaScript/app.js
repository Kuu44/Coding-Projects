//Creates a variable kelvin and sets its value to 293
let kelvin=0;
//Converts Kelvin to Celsius
let celsius=kelvin-273;
//Converts Celsius to fahrenheit and rounds it down
let fahrenheit=Math.floor(celsius *(9/5)+32);
let newton=Math.floor(celsius*(0.33));
console.log(`The temperatire is ${fahrenheit} degrees 
Fahrenheit.`);
console.log(`The temperatire is ${newton} degrees 
Newton.`);
