 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include <signal.h>
 
 void show_screen(void);
 void left(void);
 void right(void);
 void shot(void);
 void move_ennemie(void);
 void move_right(int,int);
 void move_left(int,int);
 void check_game_over(int);
 void move_shot(void);
 int  touched(void);

 signal(SIGINT,(void *)shot);
 signal(SIGTSTP,(void *)right);
 signal(SIGQUIT,(void *)left);

 char out_screen[10][10];
 int y,x,countx=0,shotx=0,shoty=0,numb_ennemie=16,point=0,flag=0;
 
 int main(void)
{
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
 /* player position */
 out_screen[8][4]='9'; 
 /* ennemie position */
 for(y=1;y<3;y++){
  for(x=1;x<9;x++){
   out_screen[y][x]='0';
  }
 }

 while(1){
  show_screen();
  move_shot();
  move_ennemie();
  sleep(1);
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

 void move_ennemie(void)
{
 int i;
  /*先頭の敵から移動していく*/
  for(y=8;y>0;y--){
 /*奇数　右への移動*/ 
   if(y%2==0){
    for(x=8;x>0;x--){
    /*敵を見つけた*/
    if(out_screen[y][x]=='0')
     move_right(y,x);
    }
   }
 /* 偶数 左への移動*/ 
   if(y%2!=0){
    for(x=1;x<9;x++){
    /*敵を見つけた*/
    if(out_screen[y][x]=='0')
     move_left(y,x);
    }
   }
  }
 return;
}

 /* それぞれ先頭からひとつづつ、敵を移動していく*/
 void move_right(int currenty,int currentx)
{
 /* 移動跡を消す*/
 out_screen[currenty][currentx]=' ';  
 /*壁に当たったら一段降りる*/
 if(currentx+1>8)
  out_screen[currenty+1][currentx]='0';
 else 
  out_screen[currenty][currentx+1]='0';

 /* ゲームオーバー判定*/
 check_game_over(currenty+1);
 return;
}

 void move_left(int currenty,int currentx)
{
 /* 移動跡を消す*/
 out_screen[currenty][currentx]=' ';  
 /*壁に当たったら一段降りる*/
 if(currentx-1<1) 
  out_screen[currenty+1][currentx]='0';
 else
  out_screen[currenty][currentx-1]='0';

 /* ゲームオーバー判定*/
 check_game_over(currenty+1);
 return;
}

 void check_game_over(int currenty)
{
 if(currenty>8){
  printf("gameover!\n");
  printf("you got %d points\n",point);
  exit(1);
 }
 return;
}
 
 void shot(void)
{
 /*もし他のショットが画面上にあればショットは打てない*/
 /* move_shot()の実行時に弾があればflagを立ててくれるのでforで探す必要は無し*/
  if(flag==1){
 printf("you can not shot !!!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    exit(1);
    return;
  }
  if(flag==0){
 /* ユーザがショットを打つ*/
 flag=1;
 out_screen[7][countx+4]='*';
  }
 return;
}

 void move_shot(void)
{
 /*ショットがあればフラグを立てる*/
 /* shot (*) を探す*/
 for(y=9;y>0;y--){
  for(x=1;x<9;x++){
   if(out_screen[y][x]=='*'){
    shoty=y;
    shotx=x;
   }
  }
 }
 printf("%d %d \n",shoty,shotx);
  /* 画面上にショットが存在すれば一つ進める*/
 if(flag==1){
  /*消す*/
  out_screen[shoty][shotx]=' ';
  /*移動前に枠の上にないか確かめる。あれば場外*/
  if(shoty<1){
   shotx=0;
   shoty=0;
   flag=0;
   return;
  }
  /* ショットが当たったか判定*/
  if(touched()==1){
   /*当たったら敵を消す*/
   out_screen[shoty-1][shotx]=' ';
   /*ショット自体も消す*/
   out_screen[shoty][shotx]=' ';
   printf("hit!\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   point++;
   /*フラグを０に戻してshot()で再びショットが打てるようにする。*/
   flag=0;
   /*ショットを移動せずにmove_shot()を中断する。*/
   return;
  }
  /* 一つ移動*/
  out_screen[shoty-1][shotx]='*';
  }
 return;
}
 
 int touched(void)
{
 /*ショット(2)が敵(0)を上書きする前にチェックをする*/
 if(flag==1){
  if(out_screen[shoty-1][shotx]='0'){
   return 1;
  }
 }
 return 0;
}
