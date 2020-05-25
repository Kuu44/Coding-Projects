const imageSize = 784;

let cat, train, rainbow;
let takenImg;
const CAT = 0;
const RAINBOW = 1;
const TRAIN = 2;

let nn;
let position = 0;
let training = [],
  testing = [];
let trainingMode = false, justCleared=true;
let trainButton, testButton, guessButton, clearButton;
let epochCounter = 0;
let data;
let bp='Aryan';
function Print(string){
  document.getElementById('answer').innerHTML=string;
}
function createNewNN(){
  let mn = new NeuralNetwork(data.input_nodes, data.hidden_nodes, data.output_nodes);
      mn.weights_ih = Matrix.deserialize(data.weights_ih);
      mn.weights_ho = Matrix.deserialize(data.weights_ho);
      mn.bias_h = Matrix.deserialize(data.bias_h);
      mn.bias_o = Matrix.deserialize(data.bias_o);
      console.log("Loaded NN");
      console.log(mn);
      nn=mn;
}

function trainOnce() {
  shuffle(training, true);
  position = 0;
  trainingMode = true;
  Print("Training...");
}
function trainNetwork() {
  let inputs = [];
  inputs = Array.from(training[position]).map(j => j / 255.0);
  let label = training[position].label;
  let targets = [0, 0, 0];
  targets[label] = 1;

  let img = createImage(28, 28);
  img.loadPixels();
  for (let i = 0; i < imageSize; i++) {
    let val = 255 - training[position][i];
    img.pixels[i * 4 + 0] = val;
    img.pixels[i * 4 + 1] = val;
    img.pixels[i * 4 + 2] = val;
    img.pixels[i * 4 + 3] = 255;
  }
  img.updatePixels();
  img.resize(280, 0)
  image(img, 0, 0);

  nn.train(inputs, targets);

  if (position < training.length) position++;
}
function testAll() {
  let percent = 0;
  testing.map((testData) => {
    let inputs = [];
    inputs = Array.from(testData).map(j => j / 255.0);
    let label = testData.label;
    let guess = nn.predict(inputs);
    const classification = guess.indexOf(max(guess));
    if (classification == label) percent++;
  });
  percent = (percent * 100) / testing.length;
  Print('% Correct: ' + nf(percent, 2, 2) + '%');
}
function trainEpoch() {
  //Randomizing
  shuffle(training, true);

  training.map((trainData) => {
    let inputs = [];
    inputs = Array.from(trainData).map(j => j / 255.0);
    let label = trainData.label;
    let targets = [0, 0, 0];
    targets[label] = 1;

    nn.train(inputs, targets);
  });
  console.log("Trained for one epoch");
}
const CreateSubArray = (obj, label) => {
  for (let i = 0; i < 1600; i++) {
    const offset = i * imageSize;
    if (i < 1280) {
      obj.training[i] = obj.data.bytes.subarray(offset, offset + imageSize);
      obj.training[i].label = label;
    } else {
      obj.testing[i - 1280] = obj.data.bytes.subarray(offset, offset + imageSize);
      obj.testing[i - 1280].label = label;
    }
  }
}
const DrawImage = function(obj) {
  const hNoOfImages = 20;
  const total = hNoOfImages * hNoOfImages;

  for (let n = 0; n < total; n++) {
    let img = createImage(28, 28);
    img.loadPixels();
    const offset = n * imageSize;
    for (let i = 0; i < imageSize; i++) {
      let val = 255 - obj.data.bytes[i + offset];
      img.pixels[i * 4 + 0] = val;
      img.pixels[i * 4 + 1] = val;
      img.pixels[i * 4 + 2] = val;
      img.pixels[i * 4 + 3] = 255;
    }
    img.updatePixels();
    const x = (n % hNoOfImages) * 28;
    const y = floor(n / hNoOfImages) * 28;
    image(img, x, y);
  }
}
function dataDummy() {
  return {
    training: [],
    testing: [],
    _data: null,
    get data() {
      return this._data;
    }
  }
}
