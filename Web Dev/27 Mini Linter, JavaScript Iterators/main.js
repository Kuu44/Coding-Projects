let story = 'Last weekend, I took literally the most beautiful bike ride of my life. The route is called "The 9W to Nyack" and it actually stretches all the way from Riverside Park in Manhattan to South Nyack, New Jersey. It\'s really an adventure from beginning to end! It is a 48 mile loop and it basically took me an entire day. I stopped at Riverbank State Park to take some extremely artsy photos. It was a short stop, though, because I had a really long way left to go. After a quick photo op at the very popular Little Red Lighthouse, I began my trek across the George Washington Bridge into New Jersey.  The GW is actually very long - 4,760 feet! I was already very tired by the time I got to the other side.  An hour later, I reached Greenbrook Nature Sanctuary, an extremely beautiful park along the coast of the Hudson.  Something that was very surprising to me was that near the end of the route you actually cross back into New York! At this point, you are very close to the end.';

function lintParagraph(paragraph){
  let overusedWords = ['really', 'very', 'basically'];
  let unnecessaryWords = ['extremely', 'literally', 'actually' ];

  const storyWords=paragraph.split(' ');

  console.log('Total Words in Story: '+storyWords.length);

  let betterWords=storyWords.filter((word)=>{
    if(unnecessaryWords.includes(word)) return false;
    else return true;
  });
  const necessaryWords=betterWords.length;
  console.log('Necessary Word Count: '+necessaryWords);

  // console.log('Over Used Word Count: '+betterWords.reduce((acc,word)=>{
  //   if(overusedWords.includes(word)) return acc+1;
  //   else return acc;
  // },0));
  betterWords=betterWords.filter((word)=>{
    if(overusedWords.includes(word)) return false;
    else return true;
  });

  console.log('Over Used Word Count: '+(necessaryWords-betterWords.length));

  console.log('Total Sentences Used: '+ storyWords.reduce((acc,word)=>{
    if(word[word.length-1]==='.'||word[word.length-1]==='!') return acc+1;
    else return acc;
  }, 0));

  findMostUsedWords(betterWords);

  return betterWords.join(' ');
}

const findMostUsedWords=(paragraphWords)=>{  
  //Remove puncstuations
  const cleanedWords=paragraphWords.map((word)=>{
    const punctuations=['.',',','!','"',];
    for(let i=0; i< word.length; i++){
      for(let j=0;j< punctuations.length; j++){
        word=word.replace(punctuations[j],'');
      }
    }    
      return word;
  });
  
  //Lowercase words
  cleanedWords.forEach(word=>word.toLowerCase());
  
  //Find most used Word
  let mostUsedWord='', current=0;
  for(let i=0, n=0; i< cleanedWords.length; i++){
    if(mostUsedWord===cleanedWords[i]) continue;

    for(let j=0; j< cleanedWords.length; j++){
      if(cleanedWords[i]===cleanedWords[j]) n++;
    }
    if(n>current){
      mostUsedWord=cleanedWords[i];
      current=n;
    }
    n=0;
  }
  console.log('  The Most Used Word: '+mostUsedWord);
  console.log('          Times Used: '+current);
}
console.log('\nFormatted Paragraph:\n'+lintParagraph(story));