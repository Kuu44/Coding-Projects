const Print = (string)=>{
  const element=document.createElement('h4');
  element.innerHTML=string;
  document.body.appendChild(element);
};
class Media{
  constructor(title){
    this._title=title;
    this._isCheckedOut=false;
    this._ratings=[];
  }
  get title(){
    return this._title;
  }
  get isCheckedOut(){
    return this._isCheckedOut;
  }
  get ratings(){
    return this._ratings;
  }
  set isCheckedOut(value){
    this._isCheckedOut=value;
  }
  addRating(rating){
    this._ratings.push(rating);
  }
  getAverageRating(){
    if(this._ratings.length>0){
      const total=this._ratings.reduce(
        (acc,rate)=> acc + rate, 0
      );
      return total/this._ratings.length;
    }
   else return 'Not rated';
  }
  toggleCheckedOutStatus(){
    this._isCheckedOut= !this._isCheckedOut;
  }
}
class Book extends Media{
  constructor(title, author, pages){
    super(title);
    this._author=author;
    this._pages=pages;
  }
  get author(){
    return this._author;
  }
  get pages(){
    return this._pages;
  }
}
class Movie extends Media{
  constructor(title, director, runTime){
    super(title);
    this._director=director;
    this._runTime=runTime;
  }
  get director(){
    return this._director;
  }
  get runTime(){
    return this._runTime;
  }
}
class CD extends Media{
  constructor(title, artist, songs){
    super(title);
    this._artist=artist;
    this._songs=songs;
  }
  get artist(){
    return this._artist;
  }
  get songs(){
    return this._songs;
  }
}
const historyOfEverything=new Book('A Short History of Nearly Everything','Bill Bryson',544);
historyOfEverything.toggleCheckedOutStatus();
Print(historyOfEverything.isCheckedOut);
historyOfEverything.addRating(4);
historyOfEverything.addRating(5);
historyOfEverything.addRating(5);
Print(historyOfEverything.getAverageRating());

const speed=new Movie('Speed','Jan de Bont',116);
speed.toggleCheckedOutStatus();
Print(speed.isCheckedOut);
speed.addRating(1);
speed.addRating(1);
speed.addRating(5);
Print(speed.getAverageRating());
