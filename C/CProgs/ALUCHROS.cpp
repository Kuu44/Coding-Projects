#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
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
int canalIII();//returns a suitable position after exhaustively using canalII for all possibilities
int chvac(char*,int[3][3]);//returns an unchose position at the line of its arg 'd1'(principal),'d2(subordinate)','r1','r2','r3','c1','c2','c3'
int randor(int (*game)[3]);//returns a random vacant position in the argument
//..........................................................................
void main(){
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
   //printf("\n\tChoose the difficulty level.\n\t\t Press for easy for hard and then press enter.");
   //scanf("%d",&tempp);
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
	    if(temp==0) temp=canalIII();
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
int help(int (*game)[3]){

}
//.........................................................................
int canalIII(){
   int tmpgame[3][3];
   for(int i=0;i<3;i++){for(int j=0;j<3;j++){tmpgame[i][j]=game[i][j];}}
   {for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
	 if(tmpgame[i][j]==0){
	    tmpgame[i][j]=1;
	    int *tmpint=canalII(tmpgame);
	    if(tmpint[0]==1) return tmpint[2];
	    else if(tmpint[1]==1) return tmpint[3];
	    tmpgame[i][j]=0;
	 }
      }
   }}
   return 0;
}
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

void clrscr()
{
    ("cls");
}
