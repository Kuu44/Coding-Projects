// max is the maximum size(length) of the snake
# define max 15
#define limobst 2
#include<stdio.h>
#include<conio.h>
#include<bios.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
int snake[max][max];
int egg[limobst]={30,15};
int obsx[limobst]={29,54};
int obsy[limobst]={8,16};
int obsz[limobst]={2,2};
int galf[limobst]={1,1};
int gend=0;
int obspd=0,ospd;
int boundux=75,bounduy=20,bounddx=4,bounddy=4;
int data;//stores the user input data from keyboard
int hlsnak[max][2];// snake vector
void printsnk();//prints snake(matrix)
void printhlsnk(int (*)[2]);//given hlsnk prints hlsnk's data
int initlcn[2]={30,12};//initial location of the (0,0) element of snake
int crnlcn[2]={initlcn[0],initlcn[1]};//location of the (0,0) element of snake
int len=0;  //initial length of snake
void xshift(int); //xmax=79=" "*79
void yshift(int); // ymax=24="\n"*24
void add(int(*)[2],int,int);//given vecx,vecy,hlsnak adds a vector to hlsnak
int headx(int ,int (*)[2]);//returns head x cord given len,hlsnak
int heady(int ,int (*)[2]);//returns head y cord given len,hlsnak
void drawsnk(int,int,int);//draws the snake given x,y,len
void hlml(int ,int (*)[2]);// given len,hlsnk remakes snake acrdng to hlsnak
void modsnk(int ,int (*)[2],char* );//given len, hlsnak,u or d or l or r changes hlsnak data to new orientation
char snkmov(int);//given spd(1 or 2) moves snake along dat and returns e if boundary problem
void resetsnk(int );//given i resets snake and hlsnak if i=1, only snak if i=0
void gmend(char);//after gameover returns 1 to play again 0 to end
void gminfo();//displays game controls information
//..................................................................
void main(){
   while(gend==0){
      randomize();
      clrscr();
      int spdd;
      resetsnk(1);
      clrscr();
      printf("\nEnter Difficulty.\n\tPress 1 for easy or press 2 for hard and then press enter. ");
      scanf("%d",&spdd);
      if(spdd>=3) spdd=3;
      else if(spdd<=1) spdd=1;
      ospd=4-spdd;
      gminfo();
      drawsnk(39,15,len);
      char cor=snkmov(spdd);
      if(cor=='e')   gmend('e');
      else if(cor=='q') gmend('q');
      else if(cor=='h') gmend('h');
      else if(cor=='a') gmend('a');
   }
}
//...................................................................
int xx,yy;
void drawsnk(int xr,int yr,int l){
   int x=xr-headx(l,hlsnak);
   int y=yr-heady(l,hlsnak);
   for(int iy=1;iy<=23;iy++){
      yshift(1);
      for(int ix=1;ix<=78;ix++){
	 if(iy==3&&ix==10) {printf("Position(%2d,%2d),Score:%3d",xx,yy,len);ix+=(24+0);}
	 else if(ix==egg[0]&&iy==egg[1]){printf("\4");}
	 else if(ix==bounddx||ix==boundux){printf("|");}
	 else if(iy==bounddy||iy==bounduy){printf("_");}
	 //print a part of snake
	 else if((ix>=x)&&(ix<=(x+l))&&(iy>=y)&&(iy<=(y+l))){
		if(snake[iy-y][ix-x]==1) printf("\4");
		else if(snake[iy-y][ix-x]==2) printf("\1");
		//if the obstacle reached the snake array location then even if there is no snake body at that location the obstacle would disappear.
		// print the obstacle
		else if(ix==obsx[0]&&iy==obsy[0]){printf("\6");}
		else if(ix==obsx[0]&&iy==obsy[0]+1){printf("\6");}
		// print the obstacle
		else if(ix==obsx[1]&&iy==obsy[1]){printf("\6");}
		else if(ix==obsx[1]&&iy==obsy[1]+1){printf("\6");}
		else printf(" ");
	 }
	 // print the obstacle
	 else if(ix==obsx[0]&&iy==obsy[0]){printf("\6");}
	 else if(ix==obsx[0]&&iy==obsy[0]+1){printf("\6");}
	 // print the obstacle
	 else if(ix==obsx[1]&&iy==obsy[1]){printf("\6");}
	 else if(ix==obsx[1]&&iy==obsy[1]+1){printf("\6");}
	 else xshift(1);
      }
   }
}
//.....................................................................
void add(int(*hlsnk)[2],int x,int y){
   static int i=0;
   hlsnk[i][0]=x;
   hlsnk[i][1]=y;
   len++;
   hlml(len,hlsnk);
   i++;
   //printsnk();
}
//....................................................................
void xshift(int x){
   for(int i=0;i<x;i++){
      printf(" ");
   }
}
//.....................................................................
void yshift(int y){
   for(int j=0;j<y;j++){
      printf("\n");
   }
}
//......................................................................
int headx(int l,int (*hlsnk)[2]){
   int temp1=0,temp2=0;
   if (l==0) return 0;
   for(int i=0;i<l;i++){
      temp1+=hlsnk[i][0];
      if (temp1<temp2)  temp2=temp1;
   }
   return (-temp2);
}
//......................................................................
int heady(int l,int (*hlsnk)[2]){
   int temp1=0,temp2=0;
   if(l==0) return 0;
   for(int i=0;i<l;i++){
      temp1+=hlsnk[i][1];
      if (temp1<temp2)  temp2=temp1;
   }
   return (-temp2);
}
//......................................................................
void modsnk(int l,int (*hlsnk)[2],char* wh){
   if(l>1){
      for(int i=l-1;i>0;i--){
	 hlsnk[i][0]=hlsnk[i-1][0];
	 hlsnk[i][1]=hlsnk[i-1][1];
      }
   }
   char temp=wh[0];
   if(temp=='u'){
      crnlcn[1]-=1;
      hlsnk[0][0]=0;
      hlsnk[0][1]=1;
   }
   else if(temp=='d'){
      crnlcn[1]+=1;
      hlsnk[0][0]=0;
      hlsnk[0][1]=-1;
   }
   else if(temp=='r'){
      crnlcn[0]+=1;
      hlsnk[0][0]=-1;
      hlsnk[0][1]=0;
   }
   else if(temp=='l'){
      crnlcn[0]-=1;
      hlsnk[0][0]=1;
      hlsnk[0][1]=0;
   }
   hlml(len,hlsnk);
}
//......................................................................
void resetsnk(int hl){
   int temp=len;
   for(int i=0;i<=len;i++){
      if(hl==1){
	 hlsnak[i][0]=7;
	 hlsnak[i][1]=7;
	 len=0;
	 xx=crnlcn[0]=initlcn[0];
	 yy=crnlcn[1]=initlcn[1];
	 data=0;
      }
      for(int j=0;j<=temp;j++){
	 snake[i][j]=0;
      }
   }
}
//......................................................................
void hlml(int l,int (*hlsnk)[2]){
   int x=headx(l,hlsnk);
   int y=heady(l,hlsnk);
   resetsnk(0);
   snake[y][x]=2;
   if (l>0){
      for (int k=0;k<l;k++){
	 x+=hlsnk[k][0];
	 y+=hlsnk[k][1];
	 snake[y][x]=1;
      }
   }
}
//.....................................................................
char snkmov(int spd){
      while(0==0){
	 if(len==max) return 'h';
	 xx=crnlcn[0];
	 yy=crnlcn[1];
	 // for the obstacles
	 obspd+=1;obspd%=ospd;
	 if(obspd==0){
	    {for(int i=0;i<limobst;i++) {
	       galf[i]=((obsy[i]>bounddy)&&(obsy[i]<(bounduy-obsz[i])))?(galf[i]):(1-(galf[i]));
	       galf[i]=(galf[i]==0)?-1:1;
	       obsy[i]+=galf[i];
	       galf[i]=(galf[i]==-1)?0:1;
	    }}
	 }
	 //
	 //to check for game over
	 for(int j=0;j<=len;j++){
	     for(int i=0;i<limobst;i++){
		 if(xx==obsx[i]&&(yy==obsy[i]||yy==(obsy[i]+1)))  return 'a';
	     }
	     if(len>0){
		 xx+=hlsnak[j][0];
		 yy+=hlsnak[j][1];
	     }
	 }
	 if(!((xx<boundux)&&(xx>bounddx))) return'e';
	 if(!((yy<bounduy)&&(yy>bounddy))) return 'e';
	 if(xx==egg[0]&&yy==egg[1]){
	    egg[0]=rand()%79;
	    while((egg[0]<=(bounddx+5))||egg[0]>=(boundux-5)){
	      if(egg[0]<=(bounddx+5)) egg[0]++;
	      else if(egg[0]>=(boundux-5)) egg[0]--;
	    }
	    egg[1]=rand()%23;
	    while((egg[1]<=(bounddy+2))||egg[1]>=(bounduy-2)){
	      if(egg[1]<=(bounddy+2)) egg[1]++;
	      else if(egg[1]>=(bounduy-2)) egg[1]--;
	    }
	    if(len==0)   add(hlsnak,1,0);
	    else add(hlsnak,hlsnak[len-1][0],hlsnak[len-1][1]);
	 }
	 clrscr();
	 char cr[1]={data};
	 modsnk(len,hlsnak,cr);
	 drawsnk(crnlcn[0],crnlcn[1],len);
	 delay(100/spd);
	 if(data=='u'||data=='d') delay(20*spd);
	 if(_bios_keybrd(1)!=0) {
	    char tmpdata=_bios_keybrd(_KEYBRD_READ);
	    //.........tmprry
	    if (tmpdata==0){
		do{tmpdata=getch();}while(tmpdata==data||tmpdata==0);
	    }
	    switch(tmpdata){
	       case 'A':
	       case 'a':
	       case'K'://for left arrow
		  data='l';
		  break;
	       case 's':
	       case 'S':
	       case 'P'://for down arrow
		  data='d';
		  break;
	       case 'd':
	       case 'D':
	       case 'M'://for right arrow
		  data='r';
		  break;
	       case 'w':
	       case 'W':
	       case 'H': //for up arrow
		  data='u';
		  break;
	       case 'q':
	       case'Q':
		  return 'q';
	    };
	 }
      }
}
//.......................................................................
void gmend(char rd){
   char inp;
   if(rd=='e') printf("\n\tGame Over. Press enter.");
   else if(rd=='q') printf("\n\tYou quit. Press enter.");
   else if(rd=='h') printf("\nYou won.");
   else if(rd=='a') printf("\nOh! I crashed.Please  play more carefully, my life is at stake.");
   getch();
   printf("\n\tPress p to play again, any other key to end.");
   inp=getch();
   if(inp=='p'||inp=='P') gend=0;
   else gend=1;
}
//.......................................................................
void printsnk(){
   for(int j=0;j<=len;j++){
      for(int k=0;k<=len;k++){
	printf("%d ",snake[j][k]);
     }
     printf("\n");
   }
}
//.........................................................................
void printhlsnk(int (*hlsnk)[2]){
   for(int i=0;i<len;i++){
      printf("x%d y%d\n",hlsnk[i][0],hlsnk[i][1]);
   }
}
//..........................................................................
void gminfo(){
   for(int i=1;i<73;i+=2){
      clrscr();
      printf("\n\n\n\tGame Controls:\n\t\t\t\t'w' to go up \n\n\t\t'a' to go left\t\t\t\t'd' to go right\n\n\t\t\t\t's' to go down\n");
      printf("\n\n");
      for(int j=0;j<i;j++){printf(" ");}
      printf("_____");
      printf("\n\t\t\tJust keep the head inside the box! \n\t\t\tAnd avoid touching the moving obstacles.\n");
      for(int k=0;k<i;k++){printf(" ");}
      printf("_____");
      printf("\n\n\n\t\t\t");
      printf("You");
      printf(" can");
      printf(" press q");
      printf(" at any");
      printf(" time");
      printf(" to quit.");
      delay(250);
   }
}