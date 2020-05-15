let raceNumber = Math.floor(Math.random() * 1000);
let registeredEarly =Math.floor(Math.random() * 2);
let runnerAge=Math.floor(Math.random() * 50);

if(runnerAge>18 && registeredEarly){
  raceNumber+=1000;
}

if(runnerAge>18 && registeredEarly){
  console.log(`Early Adult ${raceNumber}'s race starts at 9:30am`);
}
else if(runnerAge > 18 && !registeredEarly){
  console.log(`Late Adult ${raceNumber}'s race starts at 11:00am`);
}
else if (runnerAge < 18){
console.log(`Young Runner ${raceNumber}'s race starts at 12:20pm`);
}
else{
  console.log(`Runner No. ${raceNumber} is requested at the desk`);
}