/*************************************
  图的遍历
  图的数据结构采用邻接表
 *************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VER 20
#define MAX_ARC 20
#define TRUE 1
#define FALSE 0

/* 定义边的结构体 */
typedef struct Arc{
	int Start;
	int End;
	struct Arc* Next;
}Arc;

/* 定义顶点的结构体 */
typedef struct Ver{
	int Data;
	Arc* Next;
}Ver;

/* 定义图的结构体 */
typedef struct Graph{
	int ArcNum;
	int VerNum;
	Arc* ArcArray[MAX_ARC];
	Ver* VerArray[MAX_VER];
}Graph;

void GraphInit(Graph* g);           //初始化图
void DFSTraverse(Graph* g);         //深度优先搜索图
void DFS(Graph* g,int VerLocation);        //深度优先搜索某个定点
void GraphDestroy(Graph* g);        //销毁图
Arc* GetFirstAdj(Graph* g, int VerLocation); //获取顶点ver的第一个邻接边
Arc* GetNextAdj(Graph* g, int VerLocation,Arc* arc); //获取与顶点ver相关的边arc的下一条邻接边
int visited[MAX_VER];               //定义记录顶点是否被访问的数组

/* 图的深度优先搜索 */
void DFSTraverse(Graph* g){
	int i;
	/* 初始化顶点访问记录数组 */
	for(i=0;i<g->VerNum;i++){
		visited[i]=FALSE;
	}
	for(i=0;i<g->VerNum;i++){
		if(!visited[i]){
			/* 深度递归当前顶点 */
			DFS(g,i);
		}
	}
}

/* 某个顶点的深度优先递归 */
void DFS(Graph* g,int VerLocation){
	Arc* arc;
	visited[VerLocation]=TRUE;
	printf("%d",g->VerArray[VerLocation]->Data);
	for(arc = GetFirstAdj(g,VerLocation); arc!=NULL; GetNextAdj(g,VerLocation,arc)){
		DFS(g,arc->End);
	}
}

/* 获取顶点ver的第一个邻接边 */
Arc* GetFirstAdj(Graph* g, int VerLocation){
	return g->VerArray[VerLocation]->Next;
}

/* 获取与顶点ver相关的边arc的下一条邻接边 */
Arc* GetNextAdj(Graph* g, int VerLocation,Arc* arc){
	return arc->Next;
}

int main()
{
	Graph *g;
	int verNum,arcNum;
	int i;
	int Data;
	int Start,End;
	g=(Graph *)malloc(sizeof(Graph));
	while(scanf("%d%d",&verNum,&arcNum)!=EOF){
		printf("输入各顶点的值\n");
		for(i=0;i<verNum;i++){
			Ver* ver=(Ver*)malloc(sizeof(Ver));
			scanf("%d",&Data);
			ver->Data=Data;
			g->VerArray[i]=ver;
		}
		printf("输入各条边的初始顶点和结束顶点\n");
		for(i=0;i<arcNum;i++){
			Arc* arc=(Arc*)malloc(sizeof(Arc));
			scanf("%d%d",&Start,&End);
			arc->Start=Start;
			arc->End=End;
			g->ArcArray[i]=arc;
		}
		//DFSTraverse(g);
	}
	return 0;
}