const imageSize = 784;

let catData, trainData, rainbowData;
let catTraining, trainTraining, rainbowTraining;

function preload() {
  catData = loadBytes('./data/cat.bin');
  trainData = loadBytes('./data/train.bin');
  rainbowData = loadBytes('./data/rainbows.bin');
}

function setup() {
  createCanvas(560, 560);
  background(0);

  catTraining = CreateSubArray(catData);
  trainTraining = CreateSubArray(trainData);
  rainbowTraining = CreateSubArray(rainbowData);

  DrawImage(trainData);
}

const CreateSubArray = (data, amount = 1280) => {
  let result = [];
  for (let i = 0; i < amount; i++) {
    const offset = i * imageSize;
    result[i] = data.bytes.subarray(offset, offset + imageSize);
  }
  return result;
}

const DrawImage = function(array) {
  const hNoOfImages = 20;
  const total = hNoOfImages * hNoOfImages;

  for (let n = 0; n < total; n++) {
    let img = createImage(28, 28);
    img.loadPixels();
    const offset = n * imageSize;
    for (let i = 0; i < imageSize; i++) {
      let val = 255 - array.bytes[i + offset];
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
