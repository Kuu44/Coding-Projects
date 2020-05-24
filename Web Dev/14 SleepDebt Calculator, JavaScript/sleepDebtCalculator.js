const Print=(string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};
const getSleepHours=function(day){
  switch(day.toLowerCase()){
    case 'sunday':
      return 6;
      break;
    case 'monday':
      return 7;
      break;
    case 'tuesday':
      return 5;
      break;
    case 'wednesday':
      return 8;
      break;
    case 'thursday':
      return 6;
      break;
    case 'friday':
      return 7;
      break;
    case 'saturday':
      return 10;
      break;
    default:
      return 0;
      break;
  }

}
const getActualSleepHours=()=>{
  let totalSleepHours=0;
  totalSleepHours+=getSleepHours('Sunday');
  totalSleepHours+=getSleepHours('Monday');
  totalSleepHours+=getSleepHours('Tuesday');
  totalSleepHours+=getSleepHours('Wednesday');
  totalSleepHours+=getSleepHours('Thursday');
  totalSleepHours+=getSleepHours('Friday');
  totalSleepHours+=getSleepHours('Saturday');
  return totalSleepHours;
}
const getIdealSleepHours=()=>{
  const idealHours=8;
  return idealHours*7;
}
const calculateSleepDebt=()=>{
  let message='';
  const actualSleepHours=getActualSleepHours();
  const idealSleepHours=getIdealSleepHours();

  if(actualSleepHours===idealSleepHours){
    message+='You have the perfect amount of Sleep!';
  }
  else if(actualSleepHours>idealSleepHours){
    message+='You Lazy bum! You got more sleep than needed!';
  }
  else message+='Poor thing, you need more rest.';
  if(idealSleepHours>actualSleepHours){
    message+='You are '+(idealSleepHours-actualSleepHours)+' hours undersleeping!';
  }
  else if(idealSleepHours < actualSleepHours){
    message+='You are '+(-idealSleepHours+actualSleepHours)+' hours oversleeping!';
  }
  return message;
}

Print(calculateSleepDebt());
