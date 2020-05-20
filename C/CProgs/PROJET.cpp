// max is the maximum size(length) of the snake
# define max 15
#define limobst 2
#include<stdio.h>
#include<conio.h>
#include<bios.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>
void maina();
void mains();
void main(){
printf("Press '1' to satisfy your hunger for fun. \n\tPress '2' to be poisoned with fun.");
char c;
c=getch();
clrscr();
if (c=='1') maina();
else if(c=='2') mains();
}
//%*& aaluchross

int winner; //this variable denotes the winner through chkwin()'s return value.
int drawchk;//this variable eill check for draw.
int diff;//this variable stores the difficulty level.
int game[3][3]={0,0,0,0,0,0,0,0,0};
int irowchk(int i,int[][3]);//chsum for ith row  i=0,1,2
int icolchk(int i,int[][3]);//chsum for ith column i=0,1,2
int dgnlchk(int i,int[][3]);//if i is 1 then chsum for principal diagonal or if i=-1 then chsum for subordinate diagonal
void dismat(int[][3]);//display the matrix  Game[3][3]
int chkwin(int[][3]);//returns 1,-2 or 0 as player_1 wins,player_2 wins or no one has won respectively
void multiplayer();//runs multiplayer mode of the game
void vcmp();//runs v/s computer mode of the game
void resetmat(int[][3]);//reset matrix game to all zero
int canalI();//returns first stage computer's analysis result.the result is the cell ehich the computer will choose.It will return zero if it cannot find a location.
int* canalII(int[][3]); //returns an array[4] of first 1 if player1 multiway win and second 1 if computer multiway win and third is the free position for player1 and fourth is the free position for computer
int chvac(char*,int[3][3]);//returns an unchose position at the line of its arg 'd1'(principal),'d2(subordinate)','r1','r2','r3','c1','c2','c3'
int randor(int (*game)[3]);//returns a random vacant position in the argument
//..........................................................................
void maina(){
   int ctrl=0;
   do{
      drawchk=0;
      resetmat(game);
      clrscr();
      ctrl=0;
      printf("Press 'M' for multiplayer mode.\n\tPress 'C' for playing against this computer.\n\n-->");
      char i=getch();
      if(i=='m'||i=='M')
	 multiplayer(); //multiplayer mode
      else if (i=='c'||i=='C')
	 vcmp();  //vs computer mode
      printf("Press p to play again. Press any other key to end.");
      char temp=getch();
      if(temp=='p'||temp=='P') ctrl=1;
   }while(ctrl==1);
}
//........................................................................
void multiplayer(){
   char name1[10],name2[10];
   printf("\nEnter player_1's name: ");
   scanf("%s",name1);
   printf("\nEnter player_2's name: ");
   scanf("%s",name2);
   int end=0,player=1;
   while(!end){
      clrscr();
      printf("Multiplayer mode\t%s(X) v/s %s(O)\n\n",name1,name2);
      dismat(game);
      if(player%2==1) {
	 drawchk++;
	 int temp,temp1=0,temp2=0;
	 do{
	    if (temp2==0)printf("%s's turn : ",name1);
	    else printf("Try again.");
	    scanf("%d",&temp);
	    if(game[(temp-1)/3][(temp-1)%3]==0) temp1=1;
	    temp2++;
	 }while(temp1==0);
	 game[(temp-1)/3][(temp-1)%3]=1;
      }
      else{
	 drawchk++;
	 int temp,temp1=0,temp2=0;
	 do{
	    if (temp2==0)printf("%s's turn : ",name2);
	    else printf("Try again.");
	    scanf("%d",&temp);
	    if(game[(temp-1)/3][(temp-1)%3]==0) temp1=1;
	    temp2++;
	 }while(temp1==0);
	 game[(temp-1)/3][(temp-1)%3]=-2;
      }
      player++;
      winner=chkwin(game);
      if (winner!=0) end=1;
      else if (drawchk==9) end=1;
   }
   clrscr();
   dismat(game);
   if (winner==1) printf("\n\t%s wins.",name1);
   else if(winner==-2) printf("\n\t%s wins.",name2);
   else printf("It is a draw.");
}
//........................................................................
void vcmp(){
   char name1[10],name2[10]="Computer";
   printf("Enter your name : ");
   scanf("%s",name1);
   int tempp;
   diff=tempp%2;
   int end=0,player=1;
   while(!end){
      clrscr();
      printf("Computer mode\t%s(X) is playing against Computer(O)\n\n",name1);
      dismat(game);
      if(player%2==1) {
	 drawchk++;
	 int temp,temp1=0,temp2=0;
	 do{
	    if (temp2==0)printf("%s's turn : ",name1);
	    else printf("Try again.");
	    fflush(stdin);
	    scanf("%d",&temp);
	    if(game[(temp-1)/3][(temp-1)%3]==0) temp1=1;
	    temp2++;
	 }while(temp1==0);
	 game[(temp-1)/3][(temp-1)%3]=1;
      }
      else{
	 drawchk++;
	 int temp,temp1=0,temp2=0;
	 do{
	    if (temp2==0)printf("%s says : ",name2);
	    else printf("Try again.");
	    temp=canalI();
	    if(temp==0) temp=randor(game);
	    if(game[(temp-1)/3][(temp-1)%3]==0) temp1=1;
	    temp2++;
	 }while(temp1==0);
	 game[(temp-1)/3][(temp-1)%3]=-2;
	 temp=0;
	 printf("%s, press enter.",name1);
	 getch();
      }
      player++;
      winner=chkwin(game);
      if (winner!=0) end=1;
      else if (drawchk==9) end=1;
   }
   clrscr();
   dismat(game);
   if (winner==1) printf("\n\t%s wins.",name1);
   else if(winner==-2) printf("\n\t%s wins.",name2);
   else printf("It is a draw.");

}
//..........................................................................
int canalI(){
   int asd[8]={
      dgnlchk(1,game),dgnlchk(-1,game),
      irowchk(0,game),irowchk(1,game),irowchk(2,game),
      icolchk(0,game),icolchk(1,game),icolchk(2,game)
   };
   if (asd[0]==2||asd[0]==-4)
      return chvac("d1",game);//for(int i=0;i<3;i++) if (game[i][i]==0) return (4*i+1);
   if(asd[1]==2||asd[1]==-4)
      return chvac("d2",game);//for(int i=0;i<3;i++) if (game[i][2-i]==0) return (2*i+3);
   if(asd[2]==2||asd[2]==-4)
      return chvac("r1",game);//for(int i=0;i<3;i++) if (game[0][i]==0) return (i+1);
   if(asd[3]==2||asd[3]==-4)
      return chvac("r2",game);//for(int i=0;i<3;i++) if (game[1][i]==0) return (i+4);
   if(asd[4]==2||asd[4]==-4)
      return chvac("r3",game);//for(int i=0;i<3;i++) if (game[2][i]==0) return (i+7);
   if(asd[5]==2||asd[5]==-4)
      return chvac("c1",game);//for(int i=0;i<3;i++) if (game[i][0]==0) return (3*i+1);
   if(asd[6]==2||asd[6]==-4)
      return chvac("c2",game);//for(int i=0;i<3;i++) if (game[i][1]==0) return (3*i+2);
   if(asd[7]==2||asd[7]==-4)
      return chvac("c3",game);//for(int i=0;i<3;i++) if (game[i][2]==0) return (3*i+3);
   return 0;
}
//.........................................................................
int* canalII(int vgame[][3]){
   int asd[8]={
	 dgnlchk(1,vgame),dgnlchk(-1,vgame),
	 irowchk(0,vgame),irowchk(1,vgame),irowchk(2,vgame),
	 icolchk(0,vgame),icolchk(1,vgame),icolchk(2,vgame)
   };
   int posn1=0,posn2=0;
   int ch1=0,ch2=0,chtmp,reci1=-1,reci2=-1;
  //This checks for multiway victory
   for(int i=0;i<8;i++){
      for(int j=0;j<i;j++){
	    if(((i+1)/3)!=((j+1)/3)||(i+j<2)){
	       if (i+j>2)  chtmp=asd[i]+asd[j]-vgame[(i-2)%3][(j-2)%3];
	       else if(j==0) chtmp=asd[i]+asd[j]-vgame[(i-2)%3][(i-2)%3]; //Fortunately this is valid for j=0 and i=1 too.
	       else if(j==1) chtmp=asd[i]+asd[j]-vgame[(i-2)%3][2-(i-2)%3];
	    }
	    if (chtmp==3||chtmp==-6) {
	       if(chtmp==3){
		  ch1=1;
		  reci1=i;
	       }
	       else{
		  ch2=1;
		  reci2=j;
	       }
	    }
      }
   }
   char tmpstr[2];
   switch(reci1){
      case 0:
	 tmpstr[0]='d';
	 tmpstr[1]='1';
	 break;
      case 1:
	 tmpstr[0]='d';
	 tmpstr[1]='2';
	 break;
      case 2:
	 tmpstr[0]='r';
	 tmpstr[1]='1';
	 break;
      case 3:
	 tmpstr[0]='r';
	 tmpstr[1]='2';
	 break;
      case 4:
	 tmpstr[0]='r';
	 tmpstr[1]='3';
	 break;
      case 5:
	 tmpstr[0]='c';
	 tmpstr[1]='1';
	 break;
      case 6:
	 tmpstr[0]='c';
	 tmpstr[1]='2';
	 break;
      case 7:
	 tmpstr[0]='c';
	 tmpstr[1]='3';
	 break;
      case -1:
	 tmpstr[0]='z';
	 tmpstr[1]='7';
   };
   posn1=chvac(tmpstr,vgame);
   switch(reci2){
      case 0:
	 tmpstr[0]='d';
	 tmpstr[1]='1';
	 break;
      case 1:
	 tmpstr[0]='d';
	 tmpstr[1]='2';
	 break;
      case 2:
	 tmpstr[0]='r';
	 tmpstr[1]='1';
	 break;
      case 3:
	 tmpstr[0]='r';
	 tmpstr[1]='2';
	 break;
      case 4:
	 tmpstr[0]='r';
	 tmpstr[1]='3';
	 break;
      case 5:
	 tmpstr[0]='c';
	 tmpstr[1]='1';
	 break;
      case 6:
	 tmpstr[0]='c';
	 tmpstr[1]='2';
	 break;
      case 7:
	 tmpstr[0]='c';
	 tmpstr[1]='3';
	 break;
      case -1:
	 tmpstr[0]='z';
	 tmpstr[1]='7';
   };
   posn2=chvac(tmpstr,vgame);
   int array[4]={ch1,ch2,posn1,posn2};   //1 for defence and 2 for attack.
   return array;
}
//.........................................................................
/*int help(int (*game)[3]){

} */
//.........................................................................
int chkwin(int (*game)[3]){
   int temp1=dgnlchk(1,game);
   if(temp1==3||temp1==-6) return (temp1==3)?1:-2;
   temp1=dgnlchk(-1,game);
   if(temp1==3||temp1==-6) return (temp1==3)?1:-2;
   for(int i=0;i<3;i++){
      int temp1;
      temp1=irowchk(i,game);
      if(temp1==3||temp1==-6) return (temp1==3)?1:-2;
      temp1=icolchk(i,game);
      if(temp1==3||temp1==-6) return (temp1==3)?1:-2;
   }
   return 0;
}
//..........................................................................
int irowchk(int i,int (*game)[3]){
  if(i>=0 && i<3){
     int chsum=0;
     for(int j=0;j<3;j++){
	chsum+=game[i][j];
     }
     return chsum;
  }
  return 7777;
}
//..........................................................................
int icolchk(int i,int (*game)[3]){
  if(i>=0 && i<3){
     int chsum=0;
     for(int j=0;j<3;j++){
	chsum+=game[j][i];
     }
     return chsum;
  }
  return 7777;
}
//.........................................................................
int dgnlchk(int i,int (*game)[3]){
   if(i==1){
      int j=0,chsum=0;
      while(j<3){
	 chsum+=game[j][j];
	 j++;
      }
      return chsum;
   }
   else if(i==-1){
      int j=0,chsum=0;
      while(j<3){
	 chsum+=game[2-j][j];
	 j++;
      }
      return chsum;
   }
   return 7777;
}
//.........................................................................
void dismat(int (*game)[3]){
   printf("\n\n");
   printf("Press the number in a cell as shown in the table under 'Location hint' to choose that cell.\n");
   printf("The table under 'Game' is the state of this game.\n");
   printf("\n\t\t    Game\t\t\tLocation Hint.\n\t\t  ........\t\t     ...................\n");
   for(int i=0;i<3;i++){
      printf("\t\t");
      for(int j=0;j<3;j++){
	 if(game[i][j]==0) printf("[.] ");
	 if(game[i][j]==1) printf("[X] ");
	 if(game[i][j]==-2) printf("[O] ");
      }
      printf("\t\t\t");
      for(int k=0;k<3;k++){
	 if(i==0) printf("[%d] ",k+1);
	 if(i==1) printf("[%d] ",3+k+1);
	 if(i==2) printf("[%d] ",6+k+1);
      }
      printf("\n");
   }
   printf("\n\n");
}
//..........................................................................
void resetmat(int (*game)[3]){
   for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
	 game[i][j]=0;
      }
   }
}
//...........................................................................
int chvac(char* c,int (*game)[3]){
   if (c[0]=='d'||c[0]=='D'){
      if((c[1]-'0')==1){
	 for(int i=0;i<3;i++)
	    if (game[i][i]==0) return (4*i+1);
      }
      else if((c[1]-'0')==2){
	 for(int i=0;i<3;i++)
	    if (game[i][2-i]==0) {return (2*i+3);}
      }
   }
   else if (c[0]=='r'||c[0]=='R'){
      if((c[1]-'0')==1){
	 for(int i=0;i<3;i++)
	    if (game[0][i]==0) return (i+1);
      }
      else if((c[1]-'0')==2){
	 for(int i=0;i<3;i++)
	    if (game[1][i]==0) return (i+4);
      }
      else{
	 for(int i=0;i<3;i++)
	    if (game[2][i]==0) return (i+7);
      }
   }
   else if (c[0]=='c'||c[0]=='C'){
      if((c[1]-'0')==1){
	 for(int i=0;i<3;i++)
	    if (game[i][0]==0) return (3*i+1);
      }
      else if((c[1]-'0')==2){
	 for(int i=0;i<3;i++)
	    if (game[i][1]==0) return (3*i+2);
      }
      else{
	 for(int i=0;i<3;i++)
	    if (game[i][2]==0) return (3*i+3);
      }
   }
   return 0;
}
//........................................................................
int randor(int game[3][3]){
   static int rndm;
   rndm=(random(77)+random(rndm)+random(77)/7)%9+1;
   if(game[(rndm-1)/3][(rndm-1)%3]==0) return rndm;
   else randor(game);
   return 0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//%&* snake

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
void mains(){
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
