 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <signal.h>
 
 void show_screen(void);
 void left(void);
 void right(void);

 char out_screen[10][10];
 int y,x,countx=0;
 
 int main(void)
{
 signal(SIGINT,(void *)left);
 signal(SIGTSTP,(void *)right);

 /* frame */
 for(y=0;y<10;y++){
  for(x=0;x<10;x++){
   if(y==0 || y==9){
    out_screen[y][x]='*';
   }
   else{
    if(x==0 || x==9){
     out_screen[y][x]='*';
    }
    else{
     out_screen[y][x]=' ';
    }
   }
  }
 }

 
 
 /* ennemie position */
 for(y=1;y<3;y++){
  for(x=1;x<9;x++){
   out_screen[y][x]='0';
  }
 }
 
 out_screen[8][4]='9'; 
 
 while(1){
  sleep(1);
  show_screen();
 }
 return 0;
}

 void show_screen(void)
{
 for(y=0;y<10;y++){
  for(x=0;x<10;x++){
   printf("%c",out_screen[y][x]);
  }
  printf("\n");
 }

 return;
}

 void left(void)
{
 /* 壁に当たった場合はこれ以上移動できない*/
 if(4+countx==1){
  return;
 }
 /* kesu */
 out_screen[8][4+countx]=' ';  
 /* atarasiiiti */
 countx--;
 out_screen[8][4+countx]='9';  
 return;
}

 void right(void)
{
 /* 壁に当たった場合はこれ以上移動できない*/
 if(4+countx==8){
  return;
 }
 /* kesu */
 out_screen[8][4+countx]=' '; 
 /* atarasiiiti */
 countx++;
 out_screen[8][4+countx]='9';  
 return;
}
