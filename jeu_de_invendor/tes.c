 #include <stdio.h>
 
 char out_screen[10][10];
 int y,x,count=0;

 int main(void)
{
 int i,numb_ennemie=8;
 /* 移動は敵の数分実行される*/
  /*先頭の敵から移動していく*/
  for(y=8;y>0;y--){
 /*奇数　右への移動*/
   if(y%2==0){
    printf("敵さがし左への移動です。\n");
    for(x=8;x>0;x--){
    /*敵を見つけた*/
    printf("%d",x);
    }
    count++;
   }
 /* 偶数 左への移動*/
   if(y%2!=0){
    printf("敵さがし右への移動です。\n");
    for(x=1;x<9;x++){
    /*敵を見つけた*/
    printf("%d",x);
    }
    count++;
   }
   printf("%d\n",y%2);
  }

 printf("%d\n",count);
 return;
}
