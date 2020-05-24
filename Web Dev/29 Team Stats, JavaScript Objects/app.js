const Print=(string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};
const team={
  _players: [
    {firstName: 'Bruno',lastName: 'Fernandes', age: 25,},
    {firstName: 'Marcus',lastName: 'Rashford',age: 21,},
    {firstName: 'Antony',lastName: 'Martial',age: 24,},
  ],
  _games: [
    {opponent:'ManCity',teamPoints:2,opponentPoints:0,},
    {opponent:'Liverpool',teamPoints:0,opponentPoints:2,},
    {opponent:'Everton',teamPoints:1,opponentPoints:1,},
  ],
  get players(){
    return this._players;
  },
  get games(){
    return this._games;
  },
  addPlayer(firstName, lastName, age){
    this._players.push({
      firstName,lastName,age,
    });
  },
  addGame(opponent,teamPoints,opponentPoints){
    this._games.push({
      opponent,teamPoints,opponentPoints,
    });
  },
  printPlayers(){
    const players=this.players;
    for(let i=0; i< players.length; i++){
      Print(`Name: ${players[i].firstName} ${players[i].lastName}\nAge: ${players[i].age}`)
    };
  },
  printGames(){
    const games=this._games;
    for(let i=0; i< games.length; i++){
    Print(`ManUtd: ${games[i].teamPoints} - ${games[i].opponentPoints}: ${games[i].opponent}`);
    };
  },
};
team.addPlayer('Jessie','Lingard','25');
team.addPlayer('David','De Gea','26');
team.addPlayer('Scott','McTominay','19');

team.addGame('Chelsea',2,0);
team.addGame('Watford',3,0);
team.addGame('Burnley',2,0);

team.printPlayers();
team.printGames();
