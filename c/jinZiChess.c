#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define  COLNMN 3

void menu(void);
void printBoard(char board[ROW][COLNMN],int row,int lie);
void game(void);
void initialize(char board[ROW][COLNMN],int row,int lie);
void play(char board[ROW][COLNMN]);
char winning(char board[ROW][COLNMN]);


int main()
{
    menu();
    return 0;
}

void menu(void){
    //srand(time(0));
    printf("------------------------------\n");
    printf("1.Begin\n");
    printf("0.exit\n");
    printf("------------------------------\n");
    int choice = 0;
    do{
    printf("Please enter:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            game();
            break;
        case 0:
            break;
        default:
             printf("Mistyped\n");
             break;

    }
    } while (choice);

}
/*
   |   |
---|---|---
   |   |
---|---|---
   |   |
*/
void game(void){
      char board[ROW][COLNMN]= {0};
      initialize(board,ROW,COLNMN);
      printBoard(board,ROW,COLNMN);
      play(board);
}

void printBoard(char board[ROW][COLNMN],int row,int lie){
     for(int i = 0;i < row;i++){
          for(int j = 0;j < lie;j++){
                    if(j == lie - 1){
                         printf(" %c ",board[i][j]);
                    }
                    else{
               printf(" %c |",board[i][j]);
                    }
          }
          printf("\n");
          if(i != row-1)  //如果不是最后一行
          {
          for(int j = 0;j < lie;j++){
                     if(j == lie - 1){
                          printf("---");
                     }
          else{
               printf("---|");
           }
          }
                    printf("\n");
          }

     }
}

void initialize(char board[ROW][COLNMN],int row,int lie){
     for(int i = 0;i < row;i++){
          for(int j = 0;j < lie;j++){
               board[i][j] = ' ';
          }
     }
}

void play(char board[ROW][COLNMN]){
     int row,col;
     char ret;
     while(1){
          for(int i = 0;i <ROW * COLNMN;i++  ){
            //people
     printf("输入坐标(x y)(有效范是围(0 0)-(%d %d):",ROW-1,COLNMN-1);
     scanf("%d%d",&row,&col);
     if(board[row][col] != ' '){
          printf("It's already down here\n");
          continue;
     }  else{
          board[row][col] = '*';
          printBoard(board,ROW,COLNMN);
          ret = winning(board);
          if(ret == '*'){
               printf("win\n");
              return;
          } else if(ret == 'd'){
               printf("draw\n");
               return;
          }
          break;
           }
          }
          printf("----------------------\n");
          //computer
          for(int i = 0;i <ROW * COLNMN;i++  ){
          int drow,dcol;
          //srand(time(0));
          //srand((unsigned int)time(NULL));
          drow = rand() % ROW;
          dcol = rand() % COLNMN;
          if(board[drow][dcol] != ' '){
              continue;
          }  else{
          board[drow][dcol] = '&';
          printBoard(board,ROW,COLNMN);
          ret = winning(board);
          if(ret == '&'){
               printf("lose\n");
              return;
           }
          }

          break;
          }
     }
}

//* WIN
//#lose
//d draw

char winning(char board[ROW][COLNMN]){
     //row
     for(int i = 0;i < ROW;i++){
          if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' '){
               return board[i][0];
          }
     }
     //col
     for(int i = 0;i < ROW;i++){
          if(board[0][i] ==board[1][i] && board[1][i] ==board[2][i] && board[0][i] != ' '){
               return board[0][i];
          }
     }
     //diagonal
      if(board[0][0] ==board[1][1] && board[1][1] ==board[2][2] && board[0][0] != ' '){
               return board[0][0];
          }
     if(board[0][2] ==board[1][1] && board[1][1] ==board[2][0] && board[2][0] != ' '){
               return board[2][0];
          }
          //draw
          int cout = 0;
          for(int i = 0;i < ROW;i++){
            for(int j = 0;j < COLNMN;j++){
               if(board[i][j] != ' '){
                    cout++;
               }
           }
     }
     if(cout == ROW * COLNMN){
          return 'd';
     }
     return 'c';
}








