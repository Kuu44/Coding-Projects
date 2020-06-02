// Foursquare API Info
const clientId = '0045YNJ2VT2HWS2D11GG5UHTGSDDVIU2140XPCBPNFVRJ2BZ';
const clientSecret = 'DZ3Q0JJXC4NI4QZFVE2SNSDAG3UEOCD521J43ADU43GY5Z0L';
const url = 'https://api.foursquare.com/v2/venues/explore?near=';

// OpenWeather Info
const openWeatherKey = 'ca6188e377ee61330d1210eb0c0927c5';
const weatherUrl = 'https://api.openweathermap.org/data/2.5/weather';

// Page Elements
const $input = $('#city');
const $submit = $('#button');
const $destination = $('#destination');
const $container = $('.container');
const $venueDivs = [$("#venue1"), $("#venue2"), $("#venue3"), $("#venue4")];
const $weatherDiv = $("#weather1");
const weekDays = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday'];

const getVenues =async () => {
  const city=$input.val();
  //Today's Date Required
  const urlToFetch=`${url}${city}&limit=10&client_id=${clientId}&client_secret=${clientSecret}&v=20200602`;
try{
  const response=await fetch(urlToFetch);
  if(response.ok){
    const jsonResponse=await response.json();
    //console.log(jsonResponse);

    const venues=jsonResponse.response.groups[0].items.map(item=>item.venue);
    console.log(venues);
    return venues;
    }
    throw new Error('Request failed!');
  }catch(e){
    console.log(e);
  }
}

const getForecast = async() => {
  const urlToFetch=`${weatherUrl}?&q=${$input.val()}&APPID=${openWeatherKey}`;
  //console.log(urlToFetch);
  try{
    const response=await fetch(urlToFetch);
    if(response.ok){
      const jsonResponse=await response.json();
      console.log(jsonResponse);
      return jsonResponse;
    }
  }catch(e){
    console.log(e);
  }
}


// Render functions
const renderVenues = (venues) => {
  const indexes=getRandomNumbers(venues.length,$venueDivs.length);
  for(let i=0; i< indexes.length; i++){
    const venue=venues[indexes[i]];
    const venueIcon=venue.categories[0].icon;
    const venueImgSrc = `${venueIcon.prefix}bg_64${venueIcon.suffix}`;
    const venueContent=createVenueHTML(venue.name, venue.location, venueImgSrc);
    $venueDivs[i].append(venueContent);
  }
  $destination.append(`<h2>${venues[0].location.city}</h2>`);
}

const renderForecast = (day) => {
  let weatherContent = createWeatherHTML(day);
  $weatherDiv.append(weatherContent);
}

const executeSearch = () => {
  $venueDivs.forEach(venue => venue.empty());
  $weatherDiv.empty();
  $destination.empty();
  $container.css("visibility", "visible");
  getVenues().then(venues=>renderVenues(venues));
  getForecast().then(forecast=>renderForecast(forecast));
  return false;
}

$submit.click(executeSearch)