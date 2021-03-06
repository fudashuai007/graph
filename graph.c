/*************************************
  图的遍历
  图的数据结构采用邻接表
 *************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VER 20
#define MAX_ARC (MAX_VER * 2)
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
	Arc* AdjArc;
}Ver;

/* 定义图的结构体 */
typedef struct Graph{
	int ArcNum;
	int VerNum;
	Arc* ArcArray[MAX_ARC];
	Ver* VerArray[MAX_VER];
}Graph;

/* 初始化图 */
void GraphInit(Graph* g);

/* 深度优先搜索图 */
void DFSTraverse(Graph* g);

/* 深度优先搜索某个定点 */
void DFS(Graph* g,int VerLocation);

/* 销毁图 */
void GraphDestroy(Graph* g);

/* 获取顶点ver的第一个邻接边 */
Arc* GetFirstAdj(Graph* g, int VerLocation);

/* 获取与顶点ver相关的边arc的下一条邻接边 */
Arc* GetNextAdj(Graph* g, int VerLocation,Arc* arc);

/* 定义记录顶点是否被访问的数组 */
int visited[MAX_VER];


/* 初始化图 */
void GraphInit(Graph* g){
	int i, j;
	int Data;
	int Start, End;

	/* 初始化顶点 */
	for(i = 0; i < g->VerNum; i++){
		Ver* ver = (Ver*)malloc(sizeof(Ver));
		scanf("%d", &Data);
		ver->Data = Data;
		g->VerArray[i] = ver;
	}

	/* 初始化边 */
	for(i = 0; i < g->ArcNum / 2; i++){
		Arc* arc = (Arc*)malloc(sizeof(Arc));
		scanf("%d%d",&Start,&End);
		arc->Start = Start;
		arc->End = End;
		g->ArcArray[i] = arc;
	}
	/* 建立所有边的逆向边 */
	for(i = 0; i < g->ArcNum / 2; i++){
		Arc* arc = (Arc*)malloc(sizeof(Arc));
		arc->Start = g->ArcArray[i]->End;
		arc->End = g->ArcArray[i]->Start;
		g->ArcArray[i + g->ArcNum / 2] = arc;
	}

	/* 建立顶点的邻接表 */
	for(i = 0; i < g->VerNum; i++){
		Arc** last = &(g->VerArray[i]->AdjArc);
		for(j = 0; j< g->ArcNum; j++){
			if(g->ArcArray[j]->Start == i){ 
				*last = g->ArcArray[j];
				last = &(g->ArcArray[j]->Next);
			}
		}
	}
}


/* 图的深度优先搜索 */
void DFSTraverse(Graph* g){
	int i;

	/* 初始化顶点访问记录数组 */
	for(i = 0; i < g->VerNum; i++){
		visited[i] = FALSE;
	}

	for(i = 0;i < g->VerNum; i++){
		if(!visited[i]){
			/* 深度递归当前顶点 */
			DFS(g,i);
		}
	}
}


/* 某个顶点的深度优先递归 */
void DFS(Graph* g, int VerLocation){
	Arc* arc;
	visited[VerLocation] = TRUE;
	printf("%d", g->VerArray[VerLocation]->Data);
	for(arc = GetFirstAdj(g, VerLocation); arc != NULL; arc = GetNextAdj(g, VerLocation, arc)){
		if(arc->Start == VerLocation){
			if(!visited[arc->End]){
				DFS(g, arc->End);
			}
		}
		else{
			if(!visited[arc->Start]){
				DFS(g, arc->Start);
			}
		}
	}
}


/* 获取顶点ver的第一个邻接边 */
Arc* GetFirstAdj(Graph* g, int VerLocation){
	return g->VerArray[VerLocation]->AdjArc;
}


/* 获取与顶点ver相关的边arc的下一条邻接边 */
Arc* GetNextAdj(Graph* g, int VerLocation, Arc* arc){
	return arc->Next;
}

int main()
{
	Graph *g;
	int verNum, arcNum;

	g = (Graph *)malloc(sizeof(Graph));

	while(scanf("%d%d", &verNum, &arcNum) != EOF){
		g->VerNum = verNum;
		g->ArcNum = arcNum * 2;
		GraphInit(g);
		DFSTraverse(g);
		printf("\n");
	}
	return 0;
}
