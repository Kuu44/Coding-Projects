// Information to reach API
const url='https://api.datamuse.com/words?';
const queryParams='rel_rhy=';

// Selecting page elements
const inputField = document.querySelector('#input');
const submit = document.querySelector('#submit');
const responseField = document.querySelector('#responseField');

// AJAX function
const getSuggestions = () => {
  const wordQuery=inputField.value;
  const endpoint=url+queryParams+wordQuery;

  const xhr=new XMLHttpRequest();
  xhr.responseType='json';

  xhr.onreadystatechange=()=>{
    if(xhr.readyState===XMLHttpRequest.DONE){
      renderResponse(xhr.response);
    }
  };

  xhr.open('GET',endpoint);
  xhr.send();
};

// Clear previous results and display results to webpage
const displaySuggestions = (event) => {
  event.preventDefault();
  while(responseField.firstChild){
    responseField.removeChild(responseField.firstChild);
  };
  getSuggestions();
}

submit.addEventListener('click', displaySuggestions);
