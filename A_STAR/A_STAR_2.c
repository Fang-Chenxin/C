#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define END_X 1 // 终点坐标，（根据地图修改）
#define END_Y 0
#define START_X 0 // 起点坐标，（根据地图修改）
#define START_Y 2
#define MAP_LENTH 5 // 地图高宽，（根据地图修改）
#define MAP_WIDTH 5

#define ERROR -1

//---------------------------------------------------------------------------//

typedef struct Open_list Open_list, *pOpen_list;
typedef struct Node
{
	// 父节点
	pOpen_list pFather;
	float G;
	float H;
	// F值
	float F;
	// x,y坐标
	int x;
	int y;
} Node, *pNode;

typedef struct Open_list
{
	struct Open_list *next;
	struct Node node;
} Open_list, *pOpen_list;
/*障碍物为1，起点为2，终点为3，（地图可给根据需要修改）*/
int map[MAP_LENTH][MAP_WIDTH] = {
	{0, 1, 2, 1, 1},
	{3, 1, 0, 1, 1},
	{0, 1, 0, 0, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0}};

float my_abs(int x);
// 距离函数（给两个坐标(x1,y1)和（x2，y2））
float my_distance(int x1, int y1, int x2, int y2);
// 添加链表
void list_add_tail(pOpen_list my_list, pOpen_list add_node);
// 遍历链表,返回与tmpY和tmpY匹配的节点指针
pOpen_list list_browse(pOpen_list my_list, int tmpX, int tmpY);
// 判断链表中是不是有某个节点（通过坐标来确定），有的话返回0，没有返回1
int judge_node_exist(pOpen_list mylist, int x, int y);
// 删除链表中某个节点，通过坐标删除,并且返回这个删除的节点指针，方便加入到close list
pOpen_list list_delete_point(pOpen_list my_list, int tmpX, int tmpY);
// 找到链表中最小的f值的函数,输入链表，返回最小f的节点
pOpen_list find_min_f(pOpen_list my_list);
// 打印open list中的各个节点坐标以及F值
void msg_open_list(pOpen_list my_list);
// 打印父节点坐标函数
void printf_father_node(pOpen_list my_list);

//---------------------------------------------------------------------------//
// 尾部插入链表
void list_add_tail(pOpen_list my_list, pOpen_list add_node)
{
	pOpen_list tmp = my_list;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = add_node;
	add_node->next = NULL;
}

// 删除链表中某个节点，通过坐标删除,并且返回这个删除的节点指针，方便free
pOpen_list list_delete_point(pOpen_list my_list, int x, int y)
{

	while (my_list->next != NULL)
	{
		if ((my_list->next->node.x == x) && (my_list->next->node.y == y))
		{ // 找到删除节点
			pOpen_list tmp = my_list->next;
			// 这个节点不是最后一个节点
			if (my_list->next->next != NULL)
			{
				my_list->next = my_list->next->next;

				tmp->next = NULL;
			}
			else
			{ // 最后一个节点
				my_list->next = NULL;

				tmp->next = NULL;
			}
			return tmp;
		}
		my_list = my_list->next;
	}

	return NULL;
}

// 遍历链表,返回与p->node.y和p->node.y匹配的节点指针
pOpen_list list_browse(pOpen_list my_list, int x, int y)
{

	while (my_list->next != NULL)
	{
		if ((my_list->next->node.x == x) && (my_list->next->node.y == y))
		{
			return my_list->next;
		}
		my_list = my_list->next;
	}

	return NULL;
}

// 判断链表中是不是有某个节点，有的话返回0，没有返回1
int judge_node_exist(pOpen_list mylist, int x, int y)
{
	while (mylist->next != NULL)
	{
		if ((mylist->next->node.x == x) && (mylist->next->node.y == y))
		{ // 在open list
			return 0;
		}
		mylist = mylist->next;
	}

	return 1;
}

// 找到链表中最小的f值的函数,输入链表，返回最小f的节点
pOpen_list find_min_f(pOpen_list my_list)
{
	// 定义一个临时变量tmpf为第二个节点的F值
	int tmpf = my_list->next->node.F;
	pOpen_list tmpp = my_list->next;

	while (my_list->next != NULL)
	{

		if (tmpf > my_list->next->node.F)
		{
			tmpf = my_list->next->node.F;
			tmpp = my_list->next;
		}
		my_list = my_list->next;
	}

	return tmpp;
}

// 打印open list中的各个节点坐标以及F值
void msg_open_list(pOpen_list my_list)
{
	while (my_list->next != NULL)
	{
		int x = my_list->next->node.x;
		int y = my_list->next->node.y;

		float f = my_list->next->node.F;
		printf("is (%d, %d).   F = %f\n", x, y, f);

		my_list = my_list->next;
	}
}

// 打印父节点坐标函数
void printf_father_node(pOpen_list my_list)
{
	printf("\n地图为：\n");
	for (int i = 0; i < MAP_LENTH; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	printf("\n从终点到起点：\n");
	while (my_list->node.pFather != NULL)
	{
		printf("(%d, %d)\n", my_list->node.pFather->node.x, my_list->node.pFather->node.y);
		my_list = my_list->node.pFather;
	}
}

// 绝对值函数
float my_abs(int x)
{
	if (x < 0)
	{
		return (float)(-x);
	}
	else
	{
		return (float)(x);
	}
}

// 距离函数（给两个坐标(x1,y1)和（x2，y2））
float my_distance(int x1, int y1, int x2, int y2)
{
	return sqrt((my_abs(x1 - x2) * my_abs(x1 - x2)) + (my_abs(y1 - y2) * my_abs(y1 - y2)));
}

//判断移动方向
int analysis_move_dir(pOpen_list pre,pOpen_list now)
{
	if(pre->node.x == now->node.x)
	{
		if(pre->node.y > now->node.y)
		{
			return 1;//上
		}
		else
		{
			return 2;//下
		}
	}
	else
	{
		if(pre->node.x > now->node.x)
		{
			return 3;//左
		}
		else
		{
			return 4;//右
		}
	}
}

//寻找转弯点
void find_turn_point(pOpen_list my_list)
{
	pOpen_list tmp = my_list;
	pOpen_list turn_point = (pOpen_list)malloc(sizeof(Open_list));
	turn_point->next = NULL;
	pOpen_list tmp_t = turn_point;
	while(tmp->node.pFather != NULL)
	{
		if(tmp->node.x != tmp->node.pFather->node.x && tmp->node.y != tmp->node.pFather->node.y)
		{
			tmp_t->next = tmp;
			tmp_t = tmp_t->next;
			tmp_t->next = tmp->node.pFather;
			tmp_t = tmp_t->next;
			tmp_t->next = NULL;
		}
		tmp = tmp->node.pFather;
	}
	while (turn_point->next != NULL)
	{
		turn_point = turn_point->next;
		printf("转弯点为(%d, %d)", turn_point->node.x, turn_point->node.y);
		turn_point = turn_point->next;
		printf("至(%d, %d)\n", turn_point->node.x, turn_point->node.y);
	}
}

int main()
{

	pOpen_list pO = (pOpen_list)malloc(sizeof(Open_list));
	pO->next = NULL;
	pOpen_list pC = (pOpen_list)malloc(sizeof(Open_list));
	pC->next = NULL;

	// 创建起始节点并初始化，创建一个目标节点
	pOpen_list start = (pOpen_list)malloc(sizeof(Open_list));
	start->next = NULL;
	pOpen_list end = (pOpen_list)malloc(sizeof(Open_list));
	end->next = NULL;

	start->node.pFather = NULL;
	start->node.x = START_X;
	start->node.y = START_Y;
	start->node.G = 0;
	start->node.H = (my_abs(END_X - START_X) + my_abs(END_Y - START_Y));
	start->node.F = start->node.G + start->node.H;

	end->node.pFather = NULL;
	end->node.x = END_X;
	end->node.y = END_Y;

	// 起始节点加入到open list
	list_add_tail(pO, start);

	int i, j; // 计数来遍历

	//************************************************************************//
	int cir = 1;
	while (cir)
	{
		// 寻找最小的F值节点，记为pCurrent（第一次循环也就是起点）
		msg_open_list(pO); // 现在open list中有的节点
		if (pO->next == NULL)
		{
			printf("注意注意！！！！！！！！！！！没有最优路径\n");
			return 1;
		}
		pOpen_list pCurrent = find_min_f(pO); // 有可能找不到

		// 把当前点从open list中移除（通过坐标），加入到close list，记为p
		pOpen_list p = list_delete_point(pO, pCurrent->node.x, pCurrent->node.y);
		list_add_tail(pC, p);
		printf("now node is (%d, %d)\n", p->node.x, p->node.y);

		printf("打印出相关F值\n");
		msg_open_list(pO);

		for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
				if ((p->node.x + i < 0) || (p->node.x + i > 4) || (p->node.y + j < 0) || (p->node.y + j > 4)) // 超过边界了，跳过这次循环
					continue;

				if (judge_node_exist(pO, (p->node.x + i), (p->node.y + j)))
				{ // 不是open list里面的节点
					if (1 == map[p->node.x + i][p->node.y + j])
					{ // 不可到达
						continue;
					}
					else if (!(judge_node_exist(pC, (p->node.x + i), (p->node.y + j))))
					{ // 在close list中
						continue;
					}
					else if (((p->node.x + i) == END_X) && ((p->node.y + j) == END_Y))
					{ // 是目标节点，初始化
						printf("打印好了\n");
						end->node.pFather = p; // 当前节点设为end 的父节点
						cir = 0;			   // 跳出循环标志，注意跳出的是for
						break;
					}
					else
					{ // 不在open list中的普通节点

						pOpen_list pTmp = (pOpen_list)malloc(sizeof(Open_list));
						pTmp->next = NULL;

						pTmp->node.pFather = p; // 父节点为当前节点
						// 节点坐标
						pTmp->node.x = p->node.x + i;
						pTmp->node.y = p->node.y + j;
						// 节点G.H.F值
						// G值的计算利用距离公式直接计算
						pTmp->node.G = my_distance(pTmp->node.x, pTmp->node.y, START_X, START_Y);
						// H值的计算只计算横纵移动距离，忽略障碍物
						pTmp->node.H = (my_abs(END_X - pTmp->node.x) + my_abs(END_Y - pTmp->node.y));
						pTmp->node.F = pTmp->node.G + pTmp->node.H;

						// 加入到open list
						list_add_tail(pO, pTmp);
						msg_open_list(pO);
					}
				}
				else
				{ // 在open list中

					pOpen_list pTmp = list_browse(pO, (p->node.x + i), (p->node.y + j));
					float currentG = p->node.G + my_distance(pTmp->node.x, pTmp->node.y, p->node.x, p->node.y);
					float pastG = pTmp->node.G;

					if (currentG < pastG)
					{							// 当前更优
						pTmp->node.pFather = p; // 更换父节点
						// 更换G,F值
						pTmp->node.G = currentG;
						pTmp->node.F = pTmp->node.G + pTmp->node.H;
					}
				}
			}
			if (cir == 0) // 跳出外层的for循环
				break;
		}
	}
	find_turn_point(end);
	printf_father_node(end);
	return 0;
}
