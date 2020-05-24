const Print=(string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};

//Creates a variable kelvin and sets its value to 293
let kelvin=0;
//Converts Kelvin to Celsius
let celsius=kelvin-273;
//Converts Celsius to fahrenheit and rounds it down
let fahrenheit=Math.floor(celsius *(9/5)+32);
let newton=Math.floor(celsius*(0.33));
Print(`The temperatire is ${fahrenheit} degrees
Fahrenheit.`);
Print(`The temperatire is ${newton} degrees
Newton.`);
