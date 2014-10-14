 #include <stdio.h>
 #include <stdlib.h>
 #include <signal.h>
 
 void show_screen(void);
 void move_shot(void);
 void left(void);
 void right(void);
 void shot(void);
 int touched(void);
 void check_game_over(int);
 void move_ennemie(void);
 void move_right(int,int);
 void move_left(int,int);
 void reproduction_ennemie(void);

 char out_screen[10][10];
 int flag,x,y,shoty,shotx,countx=0,point=0,numb_ennemie=0;
  
 int main(void)
{
 signal(SIGINT,(void *)right);
 signal(SIGTSTP,(void *)left);
 signal(SIGQUIT,(void *)shot);

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
 
 out_screen[8][4]='9';
 flag=0;

  /* ennemie position */
 for(y=1;y<3;y++){
  for(x=1;x<9;x++){
   out_screen[y][x]='0';
   numb_ennemie++;
  }
 }

 while(1){
  reproduction_ennemie();
  show_screen(); 
  move_shot(); 
  move_ennemie();
  sleep(1);
  fflush(stdout);
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

 void shot(void)
{
 if(flag==1){
  printf("you can not shot !!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  return;
 }
 if(flag==0){
  flag=1;
  out_screen[7][4+countx]='*';
 }
 return;
}

 void move_shot(void)
{
 /*ショットがあればフラグを立てる*/
 /* shot を探す*/
 for(y=9;y>0;y--){
  for(x=1;x<9;x++){
   if(out_screen[y][x]=='*'){
    shoty=y;
    shotx=x;
   }
  }
 }
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
   /*敵の合計数から１を引く*/
   numb_ennemie--;
   point++;
   /*フラグを０に戻してshot()で再びショットが打てるようにする。*/
   flag=0;
   /*ショットを移動せずにmove_shot()を中断する。*/
   return;
  }
  /* 一つ移動*/
  out_screen[shoty-1][shotx]='*';
   /*ショットがあたっていないか確認*/
  }
 return;
}

 int touched(void)
{
 if(out_screen[shoty-1][shotx]=='0'){
  return 1;
 }
 return 0;
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

 /*move_ennemieとは真逆の方向から空きスぺースを探していく。敵の合計数が１６になるまで敵を作る*/
 void reproduction_ennemie(void)
{
 while(numb_ennemie<16){ 
  for(y=1;y<9;y++){
   /*先頭の敵から移動していく*/
  /*奇数　右への移動*/
   if(y%2==0){
    for(x=0;x<8;x++){
    /*空いているスペースを見つけた*/
    if(out_screen[y][x]==' ')
     if(numb_ennemie<16){
      out_screen[y][x]='0';
      numb_ennemie++;
     }
    }
   }
 /* 偶数 左への移動*/
   if(y%2!=0){
    for(x=8;x>0;x--){
   /*　空いているスペースを見つけた*/
    if(out_screen[y][x]==' ')
     if(numb_ennemie<16){
     out_screen[y][x]='0';
      numb_ennemie++;
     }
    }
   }
  }
 }

 return;
}
