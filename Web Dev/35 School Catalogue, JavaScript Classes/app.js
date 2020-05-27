const Print = (string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};
class School{
  constructor(name, level,numberOfStudents){
    this._name=name;
    this._level=level;
    this._numberOfStudents=numberOfStudents;
  }
  get name(){
    return this._name;
  }
  get level(){
    return this._level;
  }
  get numberOfStudents(){
    return this._numberOfStudents;
  }
  set numberOfStudents(value){
    if(typeof value=='number'){
    this._numberOfStudents=value;
    }
    else{
      console.log('Invalid input: numberOfStudents must be set to a Number');
    }
  }
  quickFacts(){
    Print(`${this._name} educates ${this._numberOfStudents} students at the ${this._level} school level`);
  }
  static pickSubstituteTeacher(arr){
    return arr[Math.floor(Math.random()*arr.length)];
  }
}
class Primary extends School{
  constructor(name, numberOfStudents, pickupPolicy){
    super(name,'primary',numberOfStudents);
    this._pickupPolicy=pickupPolicy;
  }
  get pickupPolicy(){
      return this._pickupPolicy;
  }
}
class Middle extends School{
  constructor(name, numberOfStudents){
    super(name,'middle',numberOfStudents);
  }
}

class High extends School{
  constructor(name, numberOfStudents,sportsTeams=[]){
    super(name,'high',numberOfStudents);
    this._sportsTeams=sportsTeams;
  }
  get sportsTeams(){
      Print(`Available sports: `);
      this._sportsTeams.forEach((sport)=>{Print(sport);});
      return this._sportsTeams;
  }
}

const lorrainHansbury=new Primary('Lorraine Hansbury',514,'Students must be picked up by a parent, guardian, or a family member over the age of 13.');
lorrainHansbury.quickFacts();
Print(Primary.pickSubstituteTeacher(['Jamal Crawford', 'Lou Williams', 'J. R. Smith', 'James Harden', 'Jason Terry', 'Manu Ginobli']));

const alSmith=new High('Al E. Smith',415,['Baseball', 'Basketball', 'Volleyball', 'Track and Field']);
Print(alSmith.sportsTeams);