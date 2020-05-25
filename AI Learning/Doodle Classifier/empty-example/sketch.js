function preload() {
  cat = dataDummy();
  train = dataDummy();
  rainbow = dataDummy();
  cat._data = loadBytes('./data/cat.bin');
  train._data = loadBytes('./data/train.bin');
  rainbow._data = loadBytes('./data/rainbows.bin');

  //Making Neural Network
  nn = new NeuralNetwork(784, 64, 3);
  //LoadData
  data=(loadJSON('NNData.json',createNewNN));
}
function setup() {
  createCanvas(280, 280);
  background(0);

  trainButton = select('#train');
  testButton = select('#test');
  guessButton = select('#guess');
  clearButton = select('#clears');
  trainButton.mousePressed(() => {
    epochCounter++;
    trainOnce();
  });
  testButton.mousePressed(testAll);
  clearButton.mousePressed(() => {
    background(0);
    Print('Draw either a Cat, a Train or a Rainbow!')
  });
  guessButton.mousePressed(() => {
    let inputs = [];
    let img = get();
    img.resize(28, 28);
    img.loadPixels();
    for (let i = 0; i < imageSize; i++) {
      let bright = img.pixels[i * 4];
      inputs[i] = bright / 255.0;
    }
    let guess = nn.predict(inputs);
    const classification = guess.indexOf(max(guess));
    console.log(classification);
    switch (classification) {
      case CAT:
        Print("I think it's a Cat!");
        break;
      case TRAIN:
        Print("I think it's a Train!");
        break;
      default:
        Print("I think it's a Rainbow!");
        break;
    }
  });

  //Preparing Data
  CreateSubArray(cat, CAT);
  CreateSubArray(train, TRAIN);
  CreateSubArray(rainbow, RAINBOW);

  training = training.concat(cat.training);
  training = training.concat(rainbow.training);
  training = training.concat(train.training);

  testing = testing.concat(cat.testing);
  testing = testing.concat(train.testing);
  testing = testing.concat(rainbow.testing);

  //Randomizing
  shuffle(training, true);
  console.log("Setup Done");
}
function draw() {
  if (mouseIsPressed) {
    strokeWeight(10);
    stroke(255);
    line(pmouseX, pmouseY, mouseX, mouseY);
  }
  //Training
  if (trainingMode) {
    trainNetwork();
    if (position == training.length) {
      trainingMode = false;
      //SaveData
      save(nn, './NNData.json',true);
      Print("Training Done! Clear and Draw!");
      console.log("Epoch: " + epochCounter);
    }
  }
}
