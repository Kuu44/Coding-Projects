const menu={
  _courses: {
    appetizers: [],
    mains: [],
    desserts: [],
  },
  get appetizers(){
    return this._courses.appetizers;
  },
  set appetizers(value){
    this._courses.appetizers=value;
  },
  get mains(){
    return this._courses.mains;
  },
  set mains(value){
    this._courses.mains=value;
  },
  get desserts(){
    return this._courses.desserts;
  },
  set desserts(value){
    this._courses.desserts=value;
  },
  get courses(){
    return Object.entries(this._courses);
  },
  addDishToCourse(courseName, dishName, dishPrice){
    const dish={
      name: dishName, price: dishPrice,
    };
    this[courseName].push(dish);
  },
  getRandomDishFromCourse(courseName){
    const dishes=this[courseName];
    return dishes[Math.floor(Math.random()*dishes.length)];  
  },
  generateRandomMeal(){
    const appetizer=this.getRandomDishFromCourse('appetizers');
  const main=this.getRandomDishFromCourse('mains');
  const dessert=this.getRandomDishFromCourse('desserts');
  const totalPrice=main.price+appetizer.price+dessert.price;
  console.log(`Meal:\n\nAppetizer: ${appetizer.name}\nMain Dish: ${main.name}\nDessert: ${dessert.name}\nwith the total price being Rs.${totalPrice}`);
  },
};
menu.addDishToCourse('appetizers','Gai ko Dudh',300);
menu.addDishToCourse('appetizers','MilkShake',250);
menu.addDishToCourse('appetizers','FrenchFries',350);
menu.addDishToCourse('mains','Chicken Tandoori',1500);
menu.addDishToCourse('mains','Steak',2500);
menu.addDishToCourse('mains','Momo',1000);
menu.addDishToCourse('desserts','King Yoggurt',300);
menu.addDishToCourse('desserts','Prince Choco',250);
menu.addDishToCourse('desserts','Queen Paan',320);

menu.generateRandomMeal();

//console.log(menu);
