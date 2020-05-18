const checkE=(input, arr)=>{
  if(input==='e' || input==='u'){
    arr.push(input);
  }
}

const input='Everyone blames talent and hides the hardwork, with the sweet lie that is equality';
input.toLowerCase();

const vowels=['a','e','i','o,','u',' ',','];
let resultArray=[];

for(let i=0; i< input.length; i++){
  for(let j=0;j < vowels.length; j++){
    if(vowels[j]===input[i]){
      resultArray.push(input[i]);
    }    
  }
  checkE(input[i], resultArray);  
  //console.log(vowels[i]);
}
console.log((resultArray.join('')).toUpperCase());
