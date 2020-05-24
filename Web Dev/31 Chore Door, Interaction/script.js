//Declarations
const doorImage1 = document.getElementById('door1');
const doorImage2 = document.getElementById('door2');
const doorImage3 = document.getElementById('door3');
const scoreCount = document.getElementById('score');
const startButton = document.getElementById('start');
let numClosedDoors = 3;
let openDoor1, openDoor2, openDoor3;
let currentlyPlaying = true;
let score = 0;

const botDoorPath = "https://s3.amazonaws.com/codecademy-content/projects/chore-door/images/robot.svg";
const beachDoorPath = 'https://s3.amazonaws.com/codecademy-content/projects/chore-door/images/beach.svg';
const spaceDoorPath = 'https://s3.amazonaws.com/codecademy-content/projects/chore-door/images/space.svg';
const closedDoorPath = 'https://s3.amazonaws.com/codecademy-content/projects/chore-door/images/closed_door.svg';

const randomChoreGenerator = () => {
  const choreDoor = Math.floor(Math.random() * 3);
  switch (choreDoor) {
    case 0:
      openDoor1 = botDoorPath;
      openDoor2 = beachDoorPath;
      openDoor3 = spaceDoorPath;
      break;
    case 1:
      openDoor2 = botDoorPath;
      openDoor1 = beachDoorPath;
      openDoor3 = spaceDoorPath;
      break;
    default:
      openDoor3 = botDoorPath;
      openDoor2 = beachDoorPath;
      openDoor1 = spaceDoorPath;
      break;
  }
};

const isBot = (door) => (door.src === botDoorPath);
const isntClicked = (door) => (door.src === closedDoorPath);
const gameOver = (status) => {
  if (status === 'win') {
    score++;
    startRound(score);
  } else if (status === 'lose') {
    startButton.innerHTML = "Game Over! Play Again?";
    currentlyPlaying = false;
  }
};
const playDoor = (door) => {
  numClosedDoors--;
  if (numClosedDoors === 0) gameOver('win');
  else if (isBot(door)) gameOver('lose');
};
const startRound = (count) => {
  doorImage1.src = closedDoorPath;
  doorImage2.src = closedDoorPath;
  doorImage3.src = closedDoorPath;

  numClosedDoors = 3;
  startButton.innerHTML = "Good Luck!";
  currentlyPlaying = true;
  score = count;
  scoreCount.innerHTML = "Score: " + count;
  randomChoreGenerator();
};

//Implementations
startRound(0);
doorImage1.onclick = () => {
  if (isntClicked(doorImage1) && currentlyPlaying) {
    doorImage1.src = openDoor1;
    playDoor(doorImage1);
  };
};
doorImage2.onclick = () => {
  if (isntClicked(doorImage2) && currentlyPlaying) {
    doorImage2.src = openDoor2;
    playDoor(doorImage2);
  };
};
doorImage3.onclick = () => {
  if (isntClicked(doorImage3) && currentlyPlaying) {
    doorImage3.src = openDoor3;
    playDoor(doorImage3);
  };
};
startButton.onclick = () => {
  if (!currentlyPlaying) {
    startRound(0);
  }
};
