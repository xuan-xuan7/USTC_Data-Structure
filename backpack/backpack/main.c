//
//  main.c
//  backpack
//
//  Created by 吴钰轩 on 2019/10/30.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int base;
    int top;
    int input[];
}Stack;

Stack S;
int volume,number;

void InitStack(Stack S){
    int i;
    S.base=0;
    S.top=S.base-1;
    for(i=0;i<=number;i++){
        S.input[i]=0;
    }
}

void Push(Stack *S,int in){
    S->top++;
    S->input[S->top]=in;
}

void Pop(Stack *S){
    S->input[S->top]=0;
    S->top--;
}

int main(){
    scanf("%d",&volume);
    scanf("%d",&number);
    InitStack(S);
    int con=0;
    int count;
    int m=0;
    int w[number];
    int addr[number]; //记录入栈的元素在原数组中的位置
    int back=0; //记录退栈的元素
    int now_w=0; //表示当前栈中的总重量
    for(count=0;count<number;count++){
        scanf("%d",&w[count]);
        addr[count]=0;
    }
    for(;S.base<number;S.base++){
        m=S.base;
        S.top=S.base-1;
        Push(&S,w[m]);
        addr[S.top]=m;
        now_w=w[m];
        m++;
        while(S.base<=S.top){
            while(now_w<volume&&w[m]!=back&&m<number){
                Push(&S,w[m]);
                addr[S.top]=m;
                now_w=now_w+w[m];
                m++;
            }
            if(now_w==volume){
                for(count=S.base;count<=S.top;count++)
                    printf("%d ",S.input[count]);
                printf("\n");
                now_w=now_w-w[addr[S.top]];
                Pop(&S);
                con++;
            }
            if(now_w>volume){
                now_w=now_w-w[addr[S.top]];
                Pop(&S);
            }
            if(m==number){
                now_w=now_w-w[addr[S.top]];
                m=addr[S.top]+1;
                Pop(&S);
            }
        }
    }
    printf("%d\n",con);
}



