//
//  main.c
//  Joseph
//
//  Created by 吴钰轩 on 2019/10/22.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>

struct people{
    int num;
    int secret;
    struct people *next;
};

typedef struct people single;

int main(int argc,char *argv[]) {
    FILE *fp;
    fp=fopen("out.txt", "w");
    if((fopen("out.txt", "w")==NULL)) printf("file cannot open \n");
    single *node,*head,*tail,*q;
    int *arg[argc];
    int i,j;
    for(i=1;i<argc;i++) sscanf(argv[i],"%d",&arg[i]);
    int count;
    int left_people;
    int key=arg[2];
    tail=(single*)malloc(sizeof(single));
    head=(single*)malloc(sizeof(single));
    head=tail;
    for(i=3,j=1;i<argc;i++,j++){
        node=(single*)malloc(sizeof(single));
        node->num=j;
        node->secret=arg[i];
        tail->next=node;
        tail=tail->next;
    }
    tail->next=head->next; //tail的next域为num=1的结点
    for(left_people=arg[1];left_people>0;left_people--){
        for(count=1;count<key;count++) tail=tail->next;
        q=tail->next;
        key=tail->next->secret;
        fprintf(fp,"%d  ",tail->next->num);
        tail->next=tail->next->next;
    }
    fprintf(fp,"\n");
    printf("OK\n");
    fclose(fp);
}
