#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  MAX_NAME 10
#define MAX_PHONE 11
#define MAX_ADDRESS 15
#define MAX_NUMBER 1000

enum choose{exits,add, del, find, change, print, sort} ;

struct contacts
{
    /* data */
    char name[MAX_NAME];
    char phone[MAX_PHONE];
     char address[MAX_ADDRESS];
    int age;
};

struct people
{
    /* data */
    struct contacts date[MAX_NUMBER + 1];
    int size;
};
            struct people con;

void menu();
void add02(struct people *ptr);
void find02(void);
void print02(const struct people *ptr);
int find01(const struct people *ptr);
void del02( void);
void sort02(struct people *ptr);




int main(void){
            int input;
            // struct people con;
            initialize(con);
            //enum choose s1;
    do{
        menu();
        puts("Please select(0-6)");
        //printf("%d %d %d ",exit,add,del);
        scanf("%d",&input);
         switch(input){
            case  add:
                add02(&con);
                break;
            case del:
               del02();
                break;
            case find:
                //find02(void);
                find02();
                break;
            case change:
                change02(&con);
                break;
            case print:
                print02(&con);
                break;
             case sort:
                sort02(&con);
                puts("sort");
                break;
            default:
                puts("Mistyped");
                break;
         }
    } while(input);
    puts("test");
    return 0;
}

void menu(){
    puts("----------------");
    puts("1.add"); puts("4.change");
    puts("2.del");puts("5.print");
    puts("3.Find");puts("6.sort");
    //puts("0.exit");
    puts("---------------");

}
//initialize
void initialize( struct people *ptr){
    memset(ptr->date,0,sizeof(ptr->date));
    ptr->size = 0;
            //printf("��ʼ��%d\n",ptr->size);
}
//add
void add02(struct people *ptr){
        //printf("��%d\n",ptr->size);
    //address
    char addre[10];
    puts("Please enter an address>");
    scanf("%s",addre);
    strcpy( ptr->date[ptr->size].address,addre);
    printf("%s\n", ptr->date[ptr->size].address);
    //name
     puts("Please enter an name>");
         char name02[10];
    scanf("%s",name02);
    strcpy( ptr->date[ptr->size].name,name02);
    printf("%s\n", ptr->date[ptr->size].name);
    //phone
       puts("Please enter an phone>");
         char phone02[10];
    scanf("%s",phone02);
    strcpy( ptr->date[ptr->size].phone,phone02);
    printf("%s\n", ptr->date[ptr->size].phone);
    //age
       puts("Please enter an age>");
    int age02;
    scanf("%d",&age02);
    ptr->date[ptr->size].age = age02;
    printf("%d\n", ptr->date[ptr->size].age);
    ptr->size++;
    //printf("ΰ%d\n",ptr->size);
}

// //del
void del02( void){
    int ret =  find01(&con);
       if(ret != -1 ){
        con.date[ret] = con.date[con.size - 1];
        con.size--;
        //ptr->date[i].age = 0;
        // ptr->date[i].name = " ";  //��ʱ����
       }  else {
    puts("No such person was found");
       }
}

// }
//del
// void del02(void){
//     puts("Please enter an name>");
//          char name02[10];
//     scanf("%s",name02);
//     // strcpy( ptr->date[ptr->size].name,name02);
//     // printf("%s\n", ptr->date[ptr->size].name);
//     /**
//      * �������ֵС�� 0�����ʾ str1 С�� str2��

// �������ֵ���� 0�����ʾ str1 ���� str2��

// �������ֵ���� 0�����ʾ str1 ���� str2��
// */
//     for(int i = 0;i < con.size;i++){
//        if(strcmp(name02,con.date[i].name) ==0 ){
//         con.date[i].age = 0;
//         con.date[i].name = 0;
//        }

//     }

// }
//find��ͨ�ú���
int find01(const struct people *ptr){
    puts("Please enter an name>");
         char name02[10];
    scanf("%s",name02);
    // strcpy( ptr->date[ptr->size].name,name02);
    // printf("%s\n", ptr->date[ptr->size].name);
    /**
     * �������ֵС�� 0�����ʾ str1 С�� str2��

�������ֵ���� 0�����ʾ str1 ���� str2��

�������ֵ���� 0�����ʾ str1 ���� str2��
*/
    for(int i = 0;i < ptr->size;i++){
       if(strcmp(name02,ptr->date[i].name) ==0 ){
        //ptr->date[i].age = 0;
        //ptr->date[i].name = " ";  //��ʱ����
        //printf("find:%d\n",i);
        //break;
        return i;
       }
    }
    return -1;
}
//��
void find02(void){
    int ret = find01(&con);
      if(ret == -1){
            puts("No such person was found");
       } else{
        printf("�ҵ���%d",ret);
       }

}

//��
void change02(void){
        int ret = find01(&con);
         if(ret == -1){
            puts("No such person was found");
       } else{
         //address
    // char addre[10];
    // puts("Please enter an address>");
    // scanf("%s",addre);
    // strcpy( ptr->date[ptr->size].address,addre);
    // printf("%s\n", ptr->date[ptr->size].address);
    // //name
    //  puts("Please enter an name>");
    //      char name02[10];
    // scanf("%s",name02);
    // strcpy( ptr->date[ptr->size].name,name02);
    // printf("%s\n", ptr->date[ptr->size].name);
    // //phone
    //    puts("Please enter an phone>");
    //      char phone02[10];
    // scanf("%s",phone02);
    // strcpy( ptr->date[ptr->size].phone,phone02);
    // printf("%s\n", ptr->date[ptr->size].phone);
    // //age
    //    puts("Please enter an age>");
    // int age02;
    // scanf("%d",&age02);
    // ptr->date[ptr->size].age = age02;
    // printf("%d\n", ptr->date[ptr->size].age);
    // ptr->size++;
    //printf("ΰ%d\n",ptr->size);
        //printf("�ҵ���%d",ret);
       }
}
//print
void print02(const struct people *ptr){
    system("cls"); //����
    printf("address\tname\tphone\tage\n");
    for(int i = 0;i < ptr->size;i++){
        printf("%s\t",ptr->date[i].address);
        printf("%s\t",ptr->date[i].name);
        printf("%s\t",ptr->date[i].phone);
        printf("%d\t",ptr->date[i].age);
        puts("");  //����
    }
    puts(""); //����
}
//sort
/*���������������ASCII��ֵ���бȽϣ�ֱ�����ֲ�ͬ���ַ�������\0��Ϊֹ��
�������ֵ < 0�����ʾ s1 С�� s2��
�������ֵ > 0�����ʾ s1 ���� s2��
�������ֵ = 0�����ʾ s1 ���� s2��*/
void sort02(struct people *ptr){
    for(int i = 0;i < ptr->size - 1;i++){
        for(int j = 0;j < ptr->size - 1 - i;j++){
            if(strcmp(ptr->date[j].name, ptr->date[j+1].name) > 0){
                /* t=a[j+1];
               a[j+1]=a[j];
               a[j]=t;
*/
                con.date[MAX_NUMBER + 1] = ptr->date[j];
                ptr->date[j]= ptr->date[j+1];
                ptr->date[j +1] = con.date[MAX_NUMBER + 1];

            }
        }
    }

}
