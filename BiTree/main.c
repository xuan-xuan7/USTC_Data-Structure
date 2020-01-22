//
//  main.c
//  BiTree
//
//  Created by 吴钰轩 on 2019/11/22.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
    int Ltag,Rtag;
}BiTNode,*BiTree;

typedef struct Queue{
    struct BiTNode *new;
    struct Queue *next;
}Queue;

int length=0;
BiTree T;
BiTree pre=NULL;

void CreateBiTree(char input[]){
    int i,j;
    BiTree p;
    Queue *Node,*base,*q;
    base=(Queue*)malloc(sizeof(Queue));
    base->next=NULL;
    Node=(Queue*)malloc(sizeof(Queue));
    q=(Queue*)malloc(sizeof(Queue));
    Node=base;
    j=0;
    if(input[0]==' '){
        T=NULL;
    }
    else{
        T=(BiTNode*)malloc(sizeof(BiTNode));
        T->data=input[0];
        T->Ltag=0;
        T->Rtag=0;
        q->new=T;
        q->next=Node->next;
        Node->next=q;
        Node=Node->next;
    }
    for(i=1;i<length;i=i+2){
        if(input[i]==' '){
            base->next->new->lchild=NULL;
        }
        else{
            q=(Queue*)malloc(sizeof(Queue));
            p=(BiTNode*)malloc(sizeof(BiTNode));
            p->data=input[i];
            p->Ltag=0;
            p->Rtag=0;
            q->new=p;
            q->next=Node->next;
            Node->next=q;
            Node=Node->next;
            base->next->new->lchild=p;
        }
        if(input[i+1]==' '){
            base->next->new->rchild=NULL;
        }
        else{
            q=(Queue*)malloc(sizeof(Queue));
            p=(BiTNode*)malloc(sizeof(BiTNode));
            p->data=input[i+1];
            p->Ltag=0;
            p->Rtag=0;
            q->new=p;
            q->next=Node->next;
            Node->next=q;
            Node=Node->next;
            base->next->new->rchild=p;
        }
        base=base->next;
    }
}

void ThreadTree(BiTree T){
    if(T){
        if(!(T->rchild)&&pre!=NULL){
            T->Rtag=1;
            T->rchild=pre;
        }
        else T->Rtag=0;
        if(pre!=NULL&&(!(pre->lchild))){
            pre->Ltag=1;
            pre->lchild=T;
        }
        else T->Ltag=0;
        pre=T;
        if(T->Rtag==0) ThreadTree(T->rchild);
        if(T->Ltag==0) ThreadTree(T->lchild);
    }
}

void PreOrderTree(BiTree T){
    if(T){
        printf("%c%d%d  ",T->data,T->Ltag,T->Rtag);
        if(T->Ltag) printf("%c ",T->lchild->data);
        if(T->Rtag) printf("%c ",T->rchild->data);
        if(T->Ltag==0) PreOrderTree(T->lchild);
        if(T->Rtag==0) PreOrderTree(T->rchild);
    }
}

void InOrderTree(BiTree T){
    if(T){
        if(T->Ltag==0) InOrderTree(T->lchild);
        printf("%c",T->data);
        if(T->Rtag==0) InOrderTree(T->rchild);
    }
}

void PostOrderTree(BiTree T){
    if(T){
        if(T->Ltag==0) PostOrderTree(T->lchild);
        if(T->Rtag==0) PostOrderTree(T->rchild);
        printf("%c",T->data);
    }
}

int main(){
    char input[10000];
    int i=0;
    do{
        scanf("%c",&input[i]);
        length++;
        i++;
    }while(input[i-1]!='\n');
    length--;
    CreateBiTree(input);
    ThreadTree(T);
    printf("\n");
    PreOrderTree(T);
    printf("\n");
    InOrderTree(T);
    printf("\n");
    PostOrderTree(T);
    printf("\n");
}
