//
//  main.c
//  Porland
//
//  Created by 吴钰轩 on 2019/11/26.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode{
    char data;
    int number;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

char input[100];
int count=0;
int length=0;
int num[100];
int p=0;
int number[100];

void CreateBiTree(BiTree *T){
    if(count<=length){
        *T=(BiTree)malloc(sizeof(BiTNode));
        char ch = '\0';
        if(input[count]=='x'){
            (*T)->data='\0';
            (*T)->number=num[p];
            (*T)->lchild=NULL;
            (*T)->rchild=NULL;
            p++;
            count++;
        }
        else{
            ch=input[count];
            count++;
            (*T)->data=ch;
            CreateBiTree(&(*T)->lchild);
            CreateBiTree(&(*T)->rchild);
        }
    }
}

int judge_1(BiTree t1,BiTree t2){
    if(t1->data=='*'||t1->data=='/'){
        if(t2->data=='+'||t2->data=='-'){
            return 1;
        }
    }
    return 0;
}

int judge_2(BiTree t1,BiTree t2){
    if(t1->data=='-'&&t2->data=='+') return 1;
    if(t1->data=='/'&&t2->data=='*') return 1;
    return 0;
}

void InOrderTree(BiTree T){
    int i;
    if(T){
        if(T->lchild){
            i=judge_1(T,T->lchild);
            if(i){
                printf("( ");
                InOrderTree(T->lchild);
                printf(") ");
            }
            else InOrderTree(T->lchild);
        }
        if(T->data) printf("%c ",T->data);
        else printf("%d ",T->number);
        if(T->rchild){
            i=judge_1(T,T->rchild)+judge_2(T,T->rchild);
            if(i){
                printf("( ");
                InOrderTree(T->rchild);
                printf(") ");
            }
            else InOrderTree(T->rchild);
        }
    }
}

void PostOrderTree(BiTree T){
    if(T){
        PostOrderTree(T->lchild);
        PostOrderTree(T->rchild);
        if(T->data) printf("%c ",T->data);
        else printf("%d ",T->number);
    }
}

int Calculate(){
    int i,j=0,k=0;
    if(input[0]=='x') return num[0];
    while(input[0]!='x'){
        j=0;
        for(i=0;i<=length;i++){
            if(input[i]=='x') j++;
            if(input[i]!='x'&&input[i+1]=='x'&&input[i+2]=='x'){
                switch(input[i]){
                    case '+':
                        num[j]=num[j]+num[j+1];
                        break;
                    case '-':
                        num[j]=num[j]-num[j+1];
                        break;
                    case '*':
                        num[j]=num[j]*num[j+1];
                        break;
                    case '/':
                        num[j]=num[j]/num[j+1];
                        break;
                }
                for(k=j+1;k<=p-1;k++){
                    num[k]=num[k+1];
                }
                p--;
                input[i]='x';
                for(k=i+1;k<=length-2;k++){
                    input[k]=input[k+2];
                }
                length=length-2;
                j++;
            }
        }
    }
    return num[0];
}

int main(){
    BiTree T;
    int result=0;
    int len=0;
    int i,l;
    int j=0,x=0,y=0;
    char a[100];
    char f[100];
    int pre=0;
    do{
        scanf("%c",&a[len]);
        len++;
    }while(a[len-1]!='\n');
    len--;
    for(i=0;i<=len;i++){
        if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/'){
            input[j]=a[i];
            j++;
        }
        else if(a[i]==' '&&pre==0&&a[i+1]!='+'&&a[i+1]!='-'&&a[i+1]!='*'&&a[i+1]!='/'){
            pre=i+1;
        }
        else if(a[i]==' '&&pre!=0){
            for(l=pre;l<=i-1;l++){
                f[x]=a[l];
                x++;
            }
            f[x]='\0';
            sscanf(f,"%d",&num[y]);
            input[j]='x';
            j++;
            y++;
            x=0;
            pre=0;
            if(a[i+1]!='+'&&a[i+1]!='-'&&a[i+1]!='*'&&a[i+1]!='/') pre=i+1;
        }
    }
    length=j-1;
    CreateBiTree(&T);
    InOrderTree(T);
    printf("\n");
    PostOrderTree(T);
    printf("\n");
    result=Calculate();
    printf("%d\n",result);
    return 0;
}
