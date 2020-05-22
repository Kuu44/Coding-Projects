const imageSize = 784;

let cat, train, rainbow;

function preload() {
  cat=dataDummy(); train=dataDummy(); rainbow=dataDummy();
  cat._data = loadBytes('./data/cat.bin');
  train._data = loadBytes('./data/train.bin');
  rainbow._data = loadBytes('./data/rainbows.bin');
}

function setup() {
  createCanvas(560, 560);
  background(0);

  CreateSubArray(cat);
  CreateSubArray(train);
  CreateSubArray(rainbow);

  DrawImage(rainbow);
}

const CreateSubArray = (obj) => {
  for (let i = 0; i < 1600; i++) {
    const offset = i * imageSize;
    if(i<1280) obj.training[i] = obj.data.bytes.subarray(offset, offset + imageSize);
    else obj.testing[i-1280] = obj.data.bytes.subarray(offset, offset + imageSize);
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
function dataDummy(){
  return {
    training:[], testing:[],_data: null,
    get data(){ return this._data;}
  }
}
