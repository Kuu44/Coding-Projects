const Print=(string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};

const getUserChoice = userInput => {
  userInput.toLowerCase();
  if(userInput==='rock'||userInput==='scissors'||userInput==='paper'||userInput==='bomb'){
      return userInput;
  }
  else{
      return 'Error: Invalid input';
  }
}
const getComputerChoice =() =>{
  const randomNumber=Math.floor(Math.random()*3);
  switch(randomNumber){
    case 0:
      return 'rock';
      break;
    case 1:
      return 'paper';
      break;
    case 2:
      return 'scissors';
      break;
    default:
      Print('Error: Computer Error');
      break;
  }
}
const determineWinner = (userChoice,computerChoice)=>{
  if(userChoice===computerChoice){
    return 'It\'s a tie!';
  }
  else if(userChoice==='bomb'){
    return 'User Won';
  }
  else if(userChoice==='rock'){
    if(computerChoice==='paper'){
      return 'Computer Won';
    }
    else{
      return 'User Won';
    }
  }
  else if(userChoice==='paper'){
    if(computerChoice==='scissors'){
      return 'Computer Won';
    }
    else{
      return 'User Won';
    }
  }
  else if(userChoice==='scissors'){
    if(computerChoice==='rock'){
      return 'Computer Won';
    }
    else{
      return 'User Won';
    }
  }
}

const playgame=()=>{
  const userChoice=getComputerChoice();
  //const userChoice=getUserChoice('rock');
  Print('User picks: '+userChoice)

  const computerChoice=getComputerChoice();
  Print('Computer picks: '+computerChoice)

  Print(determineWinner(userChoice,computerChoice));
}

playgame();
