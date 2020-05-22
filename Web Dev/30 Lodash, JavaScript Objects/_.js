const _={
  clamp(number,lower,upper){
    number=Math.max(number, lower);
    number=Math.min(number, upper);
    return number;
  },
  inRange(number,start,end=0){
    if(start>end){
      const temp=end;
      end=start;
      start=temp;
    }
    return (number>=start && number< end);
  },
  words(string){
    return string.split(' ');
  },
  pad(str, len){
    if(str.length> len) return str;
    else{
      const padFront=Math.floor((len-str.length)*0.5);
      let result='';
      for(let i=0; i< padFront;i++){
        result+=' ';
      };
      result+=str;
      const padEnd=len-result.length;
      for(let i=0; i< padEnd; i++){
        result+=' ';
      };
      return result;
    }
  },
  has(obj, key){
    return obj[key]?true:false;
  },
  invert(obj){
    let newObj={};
    for(let key in obj){
      newObj[obj[key]]=key;
    };
    return newObj;
  },
  findKey(obj, predicate){
    for(let key in obj){
      if(predicate(obj[key])) return key;
    };
    return undefined;
  },
  drop(array, number=1){
    number=Math.max(number,1);
    return array.slice(number,array.length);
  },
  dropWhile(array, predicate){
    const i=array.findIndex((element,index)=>{return !predicate(element,index,array);});
    return this.drop(array, i); 
  },
  /*dropWhile(array, predicate){
    result=array;
    for(let i=0; i< array.length; i++){
      //predicate(element,index,array)
      result.shift();
      if(!predicate(array[i],i,array)){
        return result;
      }
    }
    return result;
  },*/
  chunk(array,size=1){
    size=Math.max(1,size);
    result=[];
    for(let i=0; i< array.length;i+=size){
      result.push(array.slice(i,i+size));
    };
    return result;
  },
};
// Do not write or modify code below this line.
module.exports = _;

