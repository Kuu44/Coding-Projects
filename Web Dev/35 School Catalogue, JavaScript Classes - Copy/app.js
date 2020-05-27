import {Print, countCharacter, capitalizeFirstCharacterOfWords, reverseWord, reverseAllWords, replaceFirstOccurence, replaceAllOccurrences, encode, palindrome, pigLatin} from './messageMixer.js';
//import MessageMixer from './messageMixer';
//const MessageMixer=require('./messageMixer.js');

function displayMessage() {
  console.log(countCharacter("What is the color of the sky?", "t"));
  Print(capitalizeFirstCharacterOfWords("What is the color of the sky?"));
  Print(reverseWord("What is the color of the sky?"));
  Print(reverseAllWords("What is the color of the sky?"));
  Print(replaceFirstOccurence("What is the color of the sky?", "sky", "water"));
  Print(encode("What is the color of the sky?"));
  Print(palindrome('What is the color of the sky?'));
  Print(pigLatin('What is the color of the sky?','ay'));
}

displayMessage();
