#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h> 

 void choice_bloc(char sotowaku[][23]);
 void down_bloc(char sotowaku[][23]);
 void left(void);
 void right(void);
 void declare_blocs(void);

 int x,y,county=0,countx=0,numero_bloc=0,mode=0;
 int bloc_long_hight,bloc_long_width,bloc_carre_hight,bloc_carre_width,bloc_left_hight,bloc_left_width,bloc_right_hight,bloc_right_width;
 char sotowaku[23][23];

 int main(void)
{
 /*ブロックを外部ファイルから読み込む*/
  /*2.外枠を表示*/
 for(y=0;y<23;y++){
  for(x=0;x<23;x++){
   if(y==0 || y==22){
    sotowaku[y][x]='*';
   }
   else{
    if(x==0 || x==22){
     sotowaku[y][x]='*';
    }
    else{
     sotowaku[y][x]=' ';
    }
   }
  }
 }

 
 /*まとめて表示*/
 while(1){
  choice_bloc(sotowaku);
 }
 return 0;
}

 void choice_bloc(char sotowaku[][23])
{
 numero_bloc=rand()%1;
 
 switch(numero_bloc){
  case 0:
	 /*apparition ,nouveau carre*/
          for(y=1/*+county*/;y<3/*+county*/;y++){
           for(x=11;x<13;x++){
           /* ここはブロック配列をコピーしなくても、ランダムに出されるブロックの
番号によってこちらでfor文の格納刑を変更すればよい*/
            sotowaku[y][x]='*';
           }
          }
	 if(mode==1){
	  
 for(y=0;y<23;y++){
  for(x=0;x<23;x++){
   printf("%c",sotowaku[y][x]);
  }
  printf("\n");
 }
	}
	 break;
 case 1:
        /* long bar */
	 /*
         for(y=10+county;y<14+county;y++){
          for(x=11;x<12;x++){
           sotowaku[y][x]='*';
          }
         }
	 break;
	*/
  default:  break;
 }
 
 /* show_screen() */
 for(y=0;y<23;y++){
  for(x=0;x<23;x++){
   printf("%c",sotowaku[y][x]);
  }
  printf("\n");
 }

 /*down */
 down_bloc(sotowaku);
 countx=0;
 county=0;
 return; 
}

 /* county で底までの距離を調節*/
 /* out_count で天井までの高さを設定、ゲームオーバーの基準点*/
 void down_bloc(char sotowaku[][23])
{
 int out_count=0;

 /* ブロックを左に移動*/
 signal(SIGINT,(void *)left);
 /* ブロックを右に移動*/
 signal(SIGTSTP,(void *)right);

 switch(numero_bloc){
  case 0:
	 while(county<23){
  /*前のブロックを消す*/
  for(y=1+county-1;y<2+county;y++){
   for(x=11/*+countx+2*/;x<13/*+countx*/;x++){
    sotowaku[y][x]=' ';
   }
  }
  /* 消した後、ブロックを再度表示*/
  /*現在落下中のブロックの座標は、10(ブロック　最初の位置)+county          最後にcountyをインクリメントしているので＋１する必要はない  yは次の表示部で一度初期化されるのでそのまま使えない*/
          for(y=1+county;y<3+county;y++){
           for(x=11+countx;x<13+countx;x++){
            sotowaku[y][x]='*';
	  }
	 }

  /*画面、およびブロックを表示する*/
  for(y=0;y<23;y++){
   for(x=0;x<23;x++){
    printf("%c",sotowaku[y][x]);
   }
   printf("\n");
  }

  /*ゲームおーば０判定*/
out_count=0;
  /*行をずらしていく*/
  for(x=1;x<22;x++){
   out_count=0; 
   /*一行ずつ確認,一つの行に10以上 * があればゲームおーば０*/ 
   for(y=1;y<22;y++){
    if(sotowaku[y][x]=='*'){ 
     out_count++;
    }
   }
   if(out_count==23){
    printf("gameover\n");
    exit(1);
   }
  }
  county++;
  sleep(1);
  printf("coordonnees actuelles y %d \n\n\n\n\n",10+county);
  /*もしy+1の座標に*が既に入っているならブロック同士が接触したと判断*/
  /* 処理を中断し、再度新しいブロックが登場*/
  /* x座標、テスト中は１１で固定する*/
   printf("%d\n\n\n\n\n\n\n\n\n\n\n",2+county);
  if(sotowaku[2+county][11]=='*'){
   printf("10\n\n\n\n\n\n\n\n");
   /* 再度呼び出す際に新しいブロックの位置が初期化されるように注意*/
   county=0;
   /*ゲームオーバーチェック*/
   break;
  }
 }
	break;
  case 1:
	 while(county<10){
  /*前のブロックを消す*/
  for(y=1+county-1;y<2+county-1;y++){
   for(x=11;x<12;x++){
    sotowaku[y][x]=' ';
   }
  }

  for(y=0;y<23;y++){
   for(x=0;x<23;x++){
    printf("%c",sotowaku[y][x]);
   }
   printf("\n");
  }

  county++;
  sleep(1);
  }
  
	break;
  default:break;
 }

 return;
}

 /* x-1 */
 void left(void)
{
 printf("x座標%d y座標%d \n",x,y);
 /* 移動する 呼び出し時点でのブロックの位置を渡す*/
 /*これをx,yにすると、表示部分のところの適当な値を呼び出してしまう
可能性があり。countyとcountx　、ブロックの座標専用の変数を用いるべき。*/
 int this_y,this_x;
 mode++;
 countx--;
 fflush(stdin);
 fflush(stdout);
 switch(numero_bloc){
  case 0:
   /* kesu */
   for(this_y=county;this_y<county+2;this_y++){
    for(this_x=countx;this_x<countx+2;this_x++){
     sotowaku[this_y][this_x]=' ';
    }
   } 
   /* ido */
   for(this_y=county;this_y<county+2;this_y++){
    for(this_x=countx-1;this_x<countx+2;this_x++){
     sotowaku[this_y][this_x]='*';
    }
   }
  /* hyoji */
  /*
  for(y=0;y<23;y++){
   for(x=0;x<23;x++){
    printf("%c",sotowaku[y][x]);
   }
   printf("\n");
  }
  */
   break;
  }
 return;
}

 /* x+1 */
 void right(void)
{
 printf("x座標%d y座標%d \n",x,y);

 int this_y,this_x;

 countx++;
 switch(numero_bloc){
  case 0:
   for(this_y=county;this_y<county+3;this_y++){
    for(this_x=countx;this_x<countx+2;this_x++){
     sotowaku[this_y][this_x]=' ';
    }
   } 
   for(this_y=county;this_y<county+4;this_y++){
    for(this_x=countx-1;this_x<countx+1;this_x++){
     sotowaku[this_y][this_x]='*';
    }
   }
   break;
  }
 /* (動する 呼び出し時点でのブロックの位置を渡す*/
 /*これをx,yにすると、表示部分のところの適当な値を呼び出してしまう
可能性があり。countyとcountx　、ブロックの座標専用の変数を用いるべき。*/
 return;
}

 void declare_blocs(void)
{
 FILE *fd_long,*fd_carre,*fd_left,*fd_right;
 char boit_long[10],boit_carre[11],boit_left[17],c=' ';
 int i=0,hauteur=0,largeur=0;
 /*ファイルを開く*/  
 fd_long=fopen("components/long_bloc","r");
 fd_carre=fopen("components/carre_bloc","r");
 fd_left=fopen("components/left_bloc","r");
 fd_right=fopen("components/right_bloc","r");

 if(fd_long==NULL){
   printf("i");
   exit(1);
 }

 /*1ファイルからブロックの形を読み込む*/
 while(c!=EOF){
  c=fgetc(fd_long);
  boit_long[i]=c;
  i++;
 } 

 /*ブロックの高さと幅を計算*/
 while(boit_long[i]!=EOF){
  largeur++;
  if(boit_long[i]=='\n'){
   hauteur++;
   largeur=1;
  }
  printf("%c",boit_long[i]);
  i++;
 }

 bloc_long_hight=hauteur;
 bloc_long_width=largeur;

 /*2ファイルからブロックの形を読み込む*/
 i=0;
 while(c!=EOF){
  c=fgetc(fd_carre);
  boit_carre[i]=c;
  i++;
 }

 /*ブロックの高さと幅を計算*/
 while(boit_carre[i]!=EOF){
  largeur++;
  if(boit_carre[i]=='\n'){
   hauteur++;
   largeur=1;
  }
  i++;
 }
 bloc_carre_hight=hauteur;
 bloc_carre_width=largeur;

 i=0;
 /*3ファイルからブロックの形を読み込む*/
 while(c!=EOF){
  c=fgetc(fd_left);
  boit_left[i]=c;
  i++;
 }

 /*ブロックの高さと幅を計算*/
 while(boit_left[i]!=EOF){
  largeur++;
  if(boit_left[i]=='\n'){
   hauteur++;
   largeur=1;
  }
  i++;
 }
 bloc_left_hight=hauteur;
 bloc_left_width=largeur;

 i=0;
 /*4ファイルからブロックの形を読み込む*/
 while(c!=EOF){
  c=fgetc(fd_right);
  boit_left[i]=c;
  i++;
 }

 /*ブロックの高さと幅を計算*/
 while(boit_left[i]!=EOF){
  largeur++;
  if(boit_left[i]=='\n'){
   hauteur++;
   largeur=1;
  }
  i++;
 }
 bloc_right_hight=hauteur;
 bloc_right_width=largeur;

 fclose(fd_long);
 fclose(fd_carre);
 fclose(fd_left);
 fclose(fd_right);

 printf(" hateur %d largeur %d \n",bloc_long_hight,bloc_long_width);
 printf(" hateur %d largeur %d \n",bloc_carre_hight,bloc_carre_width);
 printf(" hateur %d largeur %d \n",bloc_left_hight,bloc_left_width);
 printf(" hateur %d largeur %d \n",bloc_right_hight,bloc_right_width);
 exit(1);
 return;
}
 
 
