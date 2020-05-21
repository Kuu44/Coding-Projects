int imgWidth=28;
int hNoOfImages=40;
size(1120,1120); //set value to hNoOfImages^2

byte[] data=loadBytes("train.npy");
//println(data.length);

//int total= (data.length-80)/(imgWidth*imgWidth);
//println(total);
int noOfImages = hNoOfImages * hNoOfImages;

byte[] outdata= new byte[noOfImages*imgWidth*imgWidth];
int outIndex=0;

PImage img=createImage(imgWidth,imgWidth,RGB);
img.loadPixels();
for(int n=0; n<noOfImages; n++){
  int start=80+ n*imgWidth*imgWidth;
  for(int i=0;i< 784; i++){
    int index=i+start;
    outdata[outIndex++]=data[index];
    img.pixels[i]= color(255-outdata[outIndex-1] & 0xff);
  }
  img.updatePixels();
  int x=imgWidth*(n%hNoOfImages);
  int y=imgWidth*(n/hNoOfImages);
  image(img,x,y);
}

saveBytes("train.bin", outdata);
