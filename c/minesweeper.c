#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  THUNDER 4  //�׵���Ŀ
#define ROW 6     //����
#define COL  6    //����
#define ROWS ROW +2
#define COLS COL +2

void menu(void);
void test(void);
void game(void);
void initializev(char a[ROWS][COLS],char b);   //��ʼ����
void putThunder(char a[ROWS][COLS]);     //������ ����1����ʾ�ף���0����ʾû��    
void sweepThunder(char a[ROWS][COLS],char b[ROWS][COLS]);  //�Ų���
void print(char a[ROWS][COLS]);
int thunders(char sp[ROWS][COLS]);  //���㻹�ж���û���Ų�

int main(void){
    test();
    return 0;
}

void menu(void){
    printf("----------------------------------\n");
    printf("1.��ʼ��Ϸ\n");
    printf("0.�˳���Ϸ\n");
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
    char sweep[ROWS][COLS] = {0};  	//����Ų��׵���Ϣ 
    char put[ROWS][COLS] = {0};  //��Ų����׵���Ϣ
    //��ʼ������
    initializev(sweep,'*');
    initializev(put,'0');
    //����
    putThunder(put);
        //print(put);
    //ɨ��
    sweepThunder(put,sweep);
    print(sweep);
}

//��ʼ������
void initializev(char a[ROWS][COLS],char b){
    for(int i = 0;i < ROWS;i++){
        for(int j = 0;j < COLS;j++){
            a[i][j] = b;
        }
    }
}

//����
void putThunder(char a[ROWS][COLS]){
    int x,y;
    int thunder = THUNDER;
    while(thunder--){
        x = rand() % ROW +1;   //�������
        y = rand() % COL +1;
        if(a[x][y] != '0'){
            thunder++;
            continue;
        }
        a[x][y] = '1';
   }

}

//ɨ��
void sweepThunder(char a[ROWS][COLS],char b[ROWS][COLS]){
    int x,y;
    int cout = 0;
    print(b);
    int thCout = thunders(b);
    while(thCout){
    printf("����������:(1 1)-( %d %d)",ROW,COL);
    scanf("%d%d",&x,&y);
        if(b[x][y] != '*'){           
            printf("�˴��Ѿ�����\n");
            continue;
        }
        //����
        if(a[x][y] == '1'){
            printf("������\n");          
            print(a);
            return;
        }  else if(a[x][y] == '0'){  //ִ�е���˵���˴�û��
                for(int i = x - 1;i <= x + 1;i++){
                    for(int j = y - 1;j <= y + 1;j++ ){
                        if(i == x && j == y){
                            continue;
                        }
                        if(a[i][j] != '1'){  //���û������մ˸�
                            b[i][j] = ' ';
                        }  else if(a[i][j] == '1'){
                            cout++;
                        }
                    }
                }
                b[x][y] = cout + '0';
                 thCout = thunders(b);  //���㻹�ж���ûɨ
              //printf("3*:%d\n",thCout);
             if(thCout == THUNDER){
                            printf("Ӯ��\n");
                            print(a);
                            return;
                            }
                cout = 0;
                     print(b);
        }
            
    }
}
//���㻹�ж���ûɨ
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

//��ӡ��
void print(char a[ROWS][COLS]){
    printf("   ");  //3���ո�
    //��ӡ���
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
                   //��ӡ�ݱ�
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

