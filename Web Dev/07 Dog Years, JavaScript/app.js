/*
Time moves quickly for dogs — 8 years in a human’s life equates to 45 years in a dog’s life. How old would you be if you were a dog?

Here’s how you convert your age from “human years” to “dog years”:

The first two years of a dog’s life count as 10.5 dog years each.
Each year following equates to 4 dog years.
*/
//Creates a varibale and sets its value to my age
let myAge=20;
//Creates a varibale and sets its value to 2
let earlyYears=2;
//Creates a varibale and sets its value to 2 less than my age
let laterYears=myAge-2;

//Calculation
earlyYears*=10.5;
laterYears*=4;
console.log(`Early years equivalent in Dog years is ${earlyYears} years`);
console.log(`Later years equivalent in Dog years is ${laterYears} years`);

//Calculates my age in dog Years
let myAgeInDogYears=earlyYears+laterYears;

//Creates a string and assigns my name to it in lowercase
let myName='Kuu'.toLowerCase();

//Prints out "My name is NAME. I am HUMAN AGE years old in human years which is DOG AGE years old in dog years."

console.log(`My name is ${myName}. I am ${myAge} years old in human years which is ${myAgeInDogYears} years old in dog years.`);
