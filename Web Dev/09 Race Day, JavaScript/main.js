const Print = (string) => {
  const element = document.createElement('h4');
  element.innerHTML = string;
  document.body.appendChild(element);
};

let raceNumber = Math.floor(Math.random() * 1000);
let registeredEarly = Math.floor(Math.random() * 2);
let runnerAge = Math.floor(Math.random() * 50);

if (runnerAge > 18 && registeredEarly) {
  raceNumber += 1000;
}

if (runnerAge > 18 && registeredEarly) {
  Print(`Early Adult ${raceNumber}'s race starts at 9:30am`);
} else if (runnerAge > 18 && !registeredEarly) {
  Print(`Late Adult ${raceNumber}'s race starts at 11:00am`);
} else if (runnerAge < 18) {
  Print(`Young Runner ${raceNumber}'s race starts at 12:20pm`);
} else {
  Print(`Runner No. ${raceNumber} is requested at the desk`);
}
