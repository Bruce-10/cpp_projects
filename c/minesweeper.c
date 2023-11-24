#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  THUNDER 4  //雷的数目
#define ROW 6     //行数
#define COL  6    //列数
#define ROWS ROW +2
#define COLS COL +2

void menu(void);
void test(void);
void game(void);
void initializev(char a[ROWS][COLS],char b);   //初始化雷
void putThunder(char a[ROWS][COLS]);     //放置雷 ，‘1’表示雷，‘0’表示没雷    
void sweepThunder(char a[ROWS][COLS],char b[ROWS][COLS]);  //排查雷
void print(char a[ROWS][COLS]);
int thunders(char sp[ROWS][COLS]);  //计算还有多少没有排查

int main(void){
    test();
    return 0;
}

void menu(void){
    printf("----------------------------------\n");
    printf("1.开始游戏\n");
    printf("0.退出游戏\n");
    printf("----------------------------------\n");
}

void test(void){
    int choose = 0;
    do{
        menu();
        printf("Please enter:");
        scanf("%d",&choose);
        switch(choose){
            case 1:
                game();
                break;
            case 0:
                break;
            default:
                printf("Mistyped\n");
        }
    } while(choose);
}

void game(void){
    //srand(time(0));
    srand((unsigned int)time(NULL));
    char sweep[ROWS][COLS] = {0};  	//存放排查雷的信息 
    char put[ROWS][COLS] = {0};  //存放布置雷的信息
    //初始化数组
    initializev(sweep,'*');
    initializev(put,'0');
    //布雷
    putThunder(put);
        //print(put);
    //扫雷
    sweepThunder(put,sweep);
    print(sweep);
}

//初始化数组
void initializev(char a[ROWS][COLS],char b){
    for(int i = 0;i < ROWS;i++){
        for(int j = 0;j < COLS;j++){
            a[i][j] = b;
        }
    }
}

//布雷
void putThunder(char a[ROWS][COLS]){
    int x,y;
    int thunder = THUNDER;
    while(thunder--){
        x = rand() % ROW +1;   //随机坐标
        y = rand() % COL +1;
        if(a[x][y] != '0'){
            thunder++;
            continue;
        }
        a[x][y] = '1';
   }

}

//扫雷
void sweepThunder(char a[ROWS][COLS],char b[ROWS][COLS]){
    int x,y;
    int cout = 0;
    print(b);
    int thCout = thunders(b);
    while(thCout){
    printf("请输入坐标:(1 1)-( %d %d)",ROW,COL);
    scanf("%d%d",&x,&y);
        if(b[x][y] != '*'){           
            printf("此处已经找了\n");
            continue;
        }
        //触雷
        if(a[x][y] == '1'){
            printf("触雷了\n");          
            print(a);
            return;
        }  else if(a[x][y] == '0'){  //执行到这说明此处没雷
                for(int i = x - 1;i <= x + 1;i++){
                    for(int j = y - 1;j <= y + 1;j++ ){
                        if(i == x && j == y){
                            continue;
                        }
                        if(a[i][j] != '1'){  //如果没雷则清空此格
                            b[i][j] = ' ';
                        }  else if(a[i][j] == '1'){
                            cout++;
                        }
                    }
                }
                b[x][y] = cout + '0';
                 thCout = thunders(b);  //计算还有多少没扫
              //printf("3*:%d\n",thCout);
             if(thCout == THUNDER){
                            printf("赢了\n");
                            print(a);
                            return;
                            }
                cout = 0;
                     print(b);
        }
            
    }
}
//计算还有多少没扫
int thunders(char sp[ROWS][COLS]){
    int XCout =0;
    for(int i = 1;i <= ROW;i++){
        for(int j = 1;j <= COL;j++){
            if(sp[i][j]  == '*'){
                XCout++;
            }
        }
     }
     return XCout;
}

//打印雷
void print(char a[ROWS][COLS]){
    printf("   ");  //3个空格
    //打印横标
    for(int j = 1;j < COLS - 1;j++){
            printf("  %d ",j);
        }
        printf("\n   ");
     for(int i = 1;i <= ROW;i++){
        for(int j = 1;j <= COL;j++){
            printf("|---");           
        }
             printf("|\n  ");
        for(int j = 1;j <= COL;j++){
                   //打印纵标
                   if(j == 1){
                        printf("%d",i);
                    }
            printf("| %c ",a[i][j]);
        }
        printf("|\n   ");
     }
     for(int j = 1;j <= COL;j++){
            printf("|---");
        }
             printf("|\n");
}

