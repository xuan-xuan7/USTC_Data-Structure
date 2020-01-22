//
//  main.c
//  Graph
//
//  Created by 吴钰轩 on 2019/12/11.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int vexnum,arcnum;
    int arcs[100][100];
    int val[100]; //记录关节点状态
}MGraph;
MGraph G;

typedef struct ALGraph{
    int data;
    struct ALGraph *nextarc;
}ALGraph;

ALGraph *T[100];

int count=1;

void CreateUDN(){
    char c;
    int a,b;
    int i,j;
    G.arcnum=0;
    scanf("%d%c",&G.vexnum,&c);
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++){
            G.arcs[i][j]=0;
        }
        G.val[i]=0;
    }
    while(1){
        scanf("%c",&c);
        if(c=='\n') break;
        else{
            a=c-'0';
            scanf("%d%c",&b,&c);
            G.arcs[a][b]=1;
            G.arcs[b][a]=1;
            G.arcnum++;
        }
    }
}

void DFS_Find(){
    int visited[G.vexnum];
    int i,j;
    int low[G.vexnum];
    int max[G.vexnum],min[G.vexnum];
    int val=1; //记录是否有符合条件的结点
    int top,key;
    int gen[G.vexnum]; //用来判断节点是否是关节点
    int stack[G.vexnum];
    for(i=0;i<G.vexnum;i++){
        visited[i]=0;
        low[i]=10000;
        max[i]=0;
        min[i]=10000;
        gen[i]=0;
    }
    stack[0]=0;
    top=1;
    gen[0]=0;
    visited[0]=1;
    while(top!=0){
        key=stack[top-1];
        for(i=0;i<G.vexnum;i++){
            if(G.arcs[key][i]==1&&visited[i]==0) break;
            if(i==G.vexnum-1) val=0;
        }
        if(val){
            count++;
            visited[i]=count;
            stack[top]=i;
            top++;
        }
        else{
            top--;//需要的值为stack[top]
            if(top>1){
                gen[stack[top-1]]++;
            }
            if(low[stack[top]]==10000){
                low[stack[top]]=visited[stack[top]];
            }
            else{
                if(gen[stack[top]]>1){
                    if(max[stack[top]]>=visited[stack[top]]) G.val[stack[top]]=1;
                }
                else{
                    if(min[stack[top]]>=visited[stack[top]]) G.val[stack[top]]=1;
                }
                if(low[stack[top]]>visited[stack[top]]) low[stack[top]]=visited[stack[top]];
            }
            for(j=0;j<top-1;j++){
                if(G.arcs[stack[top]][stack[j]]){
                    if(visited[stack[j]]<low[stack[top]]) low[stack[top]]=visited[stack[j]];
                }
            }
            if(low[stack[top]]>max[stack[top]]) max[stack[top]]=low[stack[top]];
            if(low[stack[top]]<min[stack[top]]) min[stack[top]]=low[stack[top]];
            if(top>=2){
                if(min[stack[top-1]]>min[stack[top]]) min[stack[top-1]]=min[stack[top]];
                if(gen[stack[top-1]]>1){
                    if(max[stack[top-1]]<min[stack[top]]) max[stack[top-1]]=min[stack[top]];
                }
                low[stack[top-1]]=min[stack[top-1]];
            }
            if(top==1) gen[0]++;
        }
        val=1;
    }
    if(gen[0]>=2) G.val[0]=1;
}

void CreateAL(){
    int i,j;
    ALGraph *p,*node;
    for(i=0;i<G.vexnum;i++){
        T[i]=(ALGraph*)malloc(sizeof(ALGraph));
        p=(ALGraph*)malloc(sizeof(ALGraph));
        T[i]->data=i;
        p=T[i];
        for(j=0;j<G.vexnum;j++){
            if(G.arcs[i][j]){
                node=(ALGraph*)malloc(sizeof(ALGraph));
                node->data=j;
                p->nextarc=node;
                p=p->nextarc;
            }
        }
        p->nextarc=NULL;
    }
}

void BFS_Find(){
    int i,j;
    int base,top;
    int queue[G.vexnum];
    int visited[G.vexnum];
    int len[G.vexnum][G.vexnum];
    ALGraph *p;
    for(i=0;i<G.vexnum;i++) visited[i]=0;
    queue[0]=0;
    base=0;
    top=1;
    visited[0]=1;
    len[0][0]=0;
    p=(ALGraph*)malloc(sizeof(ALGraph));
    p=T[0]->nextarc;
    while(base!=top){
        if(p&&visited[p->data]==0){
            queue[top]=p->data;
            visited[p->data]=visited[queue[base]]+1;
            for(j=0;j<visited[queue[base]];j++){
                len[queue[top]][j]=len[queue[base]][j];
            }
            len[queue[top]][visited[queue[top]]-1]=queue[top];
            top++;
            p=p->nextarc;
        }
        else if(p&&visited[p->data]!=0) p=p->nextarc;
        else{
            base++;
            if(base<G.vexnum) p=T[queue[base]]->nextarc;
        }
    }
    for(i=1;i<G.vexnum;i++){
        printf("%d ",visited[i]-1);
        for(j=0;j<visited[i];j++){
            printf("%d",len[i][j]);
            if(j!=visited[i]-1) printf("->");
        }
        printf("\n");
    }
}

int main(){
    int i;
    CreateUDN();
    DFS_Find();
    for(i=0;i<G.vexnum;i++){
        if(G.val[i]) printf("%d ",i);
    }
    printf("\n");
    CreateAL();
    BFS_Find();
}
