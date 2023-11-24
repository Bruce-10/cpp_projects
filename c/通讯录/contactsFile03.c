#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define  MAX_NAME 10
#define MAX_PHONE 11
#define MAX_ADDRESS 15
#define EVERY_TIME 3

enum choose{exits,add, del, find, change, print, sort,enumDel02} ;

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
    //struct contacts date[];
    struct contacts *date;
    int size;
    int capacity;  //����
};
            struct people con;
void menu();
void add02(struct people *ptr);
void find02(void);
void print02(const struct people *ptr);
int find01(const struct people *ptr);
void del02( );
void save( struct people *ptr);
int comp(const void *a, const void *b);
void del03();

int main(void){
            int input;
            // struct people con;
            initialize(&con); //��ʼ��
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
printf("size:%d \n",con.size);
                 qsort( con.date, con.size+1, sizeof( con.date[0] ), comp);
                //  qsort( (con.date), con.size+1, MAX_NAME, comp);
                puts("sort");
                break;
            case exits:
                save(&con);
                destroyed(&con);
                break;
           case enumDel02:
                    del03();
                    break;
            default:
                puts("Mistyped");
                break;
         }
    } while(input);
    return 0;
}

void menu(){
        // system("cls"); //����
    puts("----------------");
    puts("1.add"); puts("4.change");
    puts("2.del");puts("5.print");
    puts("3.Find");puts("6.sort");
    //puts("0.exit");
    puts("---------------");

}
   void lodeContacts(struct people *ptr);  //������Ϣ
//initialize
void initialize( struct people *ptr){
    // puts("t1");
    ptr->date = (struct contacts*)malloc(EVERY_TIME * sizeof(struct contacts) );
    if(ptr->date == NULL){
        puts("molloc Pioneering failure");
        return;
    }
    ptr->capacity = EVERY_TIME;
    ptr->size = 0;
    puts("molloc win");
    lodeContacts(ptr);
}
//detectSpace  //����
void detectSpace(struct people *pt){
    struct contacts *pt02= realloc(pt->date,sizeof(struct contacts) * (pt->capacity + 2) );
     if(pt02 == NULL){
        puts(" realloc Pioneering failure");
    }else{
        pt->date = pt02;
    pt->capacity += 2;
    puts("realloc win");
    }

}

//add
void add02(struct people *ptr){
    if(ptr->size == ptr->capacity){
        detectSpace(ptr);
    }

    //address
    char addre[10];
    puts("Please enter an address>");
    scanf("%s",addre);
    strcpy( ptr->date[ptr->size].address,addre);
    // printf("%s\n", ptr->date[ptr->size].address);
    //name
     puts("Please enter an name>");
         char name02[10];
    scanf("%s",name02);
    strcpy( ptr->date[ptr->size].name,name02);
    // printf("%s\n", ptr->date[ptr->size].name);
    //phone
       puts("Please enter an phone>");
         char phone02[10];
    scanf("%s",phone02);
    strcpy( ptr->date[ptr->size].phone,phone02);
    //age
       puts("Please enter an age>");
    int age02;
    scanf("%d",&age02);
    ptr->date[ptr->size].age = age02;
    ptr->size++;
        system("cls"); //����

}

// //del
void del02( void){
    int ret =  find01(&con);
       if(ret != -1 ){
        con.date[ret] = con.date[con.size - 1];
        con.size--;
                printf("DEL02:%d\n",con.size);

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
       }
    //     else{
    //     // address
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
    // printf("ΰ%d\n",ptr->size);
    //     printf("�ҵ���%d",ret);
    //    }
}
//print
void print02(const struct people *ptr){
    system("cls"); //����
            printf("print02:%d\n",ptr->size);

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
//Destroyed
void destroyed(struct people *ptr){
    free(ptr->date);
    ptr = NULL;
    puts("Destroyed");
}
//svae
void save( struct people *ptr){
    FILE *pf = fopen("contacts.bat","wb");
    // FILE *pf = fopen("contacts.bat","wb");
    if(pf == NULL){
        printf("save::%s\n",strerror(errno) );
        return;
    }
    for(int i = 0; i < ptr->size;i++){
        //fread(&temp,sizeof(S),1,pf);
        fwrite(&ptr->date[i],sizeof(struct contacts),1,pf);
    }
    fclose(pf);
    pf = NULL;
}
//    lodeContacts
   void lodeContacts(struct people *ptr){
    struct contacts temp = {0};
     FILE *pf = fopen("contacts.bat","rb");
    // FILE *pf = fopen("contacts.bat","wb");
    if(pf == NULL){
        printf("lodeContacts::%s\n",strerror(errno) );
        return;
    }
    //int cout = 0;
       while( fread(&temp,sizeof(struct contacts),1,pf) ){
          if(ptr->size == ptr->capacity){
        detectSpace(ptr);
    }
        ptr->date[ptr->size] = temp;
        ptr->size++;
       }
    fclose(pf);
    pf = NULL;
   }

//qsort�ıȽϺ���
int comp(const void *a, const void *b){
    char *str1 =  ( (struct contacts *)a)->name;
    char *str2 =  ( (struct contacts *)b)->name;
    return strcmp(str1, str2);
}
//ɾ���ļ�
void del03()
{
             initialize(&con); //��ʼ��
    if(  remove("contacts.bat") == 0 ){
		puts("ɾ���ɹ�");
	}
	else
	{
		puts("ɾ��ʧ��");
	}
}
