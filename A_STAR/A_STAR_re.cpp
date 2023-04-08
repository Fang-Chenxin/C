#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>

#define END_X 1 // 终点坐标，（根据地图修改）
#define END_Y 0
#define START_X 0 // 起点坐标，（根据地图修改）
#define START_Y 2
#define MAP_HEIGHT 5 // 地图高宽，（根据地图修改）
#define MAP_WIDTH 5

#define ERROR -1

//---------------------------------------------------------------------------//

struct Node
{
    // 父节点
    Node *pFather;
    float G;
    float H;
    // F值
    float F;
    // x,y坐标
    int x;
    int y;
};

typedef std::vector<Node> Open_list;

/*障碍物为1，起点为2，终点为3，（地图可给根据需要修改）*/
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 1, 2, 1, 1},
    {3, 1, 0, 1, 1},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}};

//---------------------------------------------------------------------------//

// 绝对值函数
float my_abs(int x);
// G距离函数（给两个坐标(x1,y1)和（x2，y2））
float G_distance(int x1, int y1, int x2, int y2);
// H距离函数（节点和（x，y））
float H_distance(const Node &node, int x, int y);
// 遍历Open_list,返回与tmpY和tmpY匹配的节点指针
Open_list::iterator list_browse(Open_list &my_list, int tmpX, int tmpY);
// 判断Open_list中是不是有某个节点（通过坐标来确定），有的话返回true，没有返回false
bool judge_node_exist(const Open_list &mylist, int x, int y);
// 删除Open_list中某个节点，通过坐标删除,并且返回这个删除的节点指针，方便加入到close list
Node list_delete_point(Open_list &my_list, int tmpX, int tmpY);
// 找到Open_list中最小的f值的节点,输入Open_list，返回最小f的节点
Open_list::iterator find_min_f(Open_list &my_list);
// 打印Open_list中的各个节点坐标以及F值
void msg_open_list(const Open_list &my_list);
// 显示地图
void show_map(const Open_list &my_list);

//---------------------------------------------------------------------------//

// 删除Open_list中某个节点，通过坐标删除,并且返回这个删除的节点，方便free
Node list_delete_point(Open_list &my_list, int x, int y)
{
    Node deleted_node; // Node to be deleted
    for (auto it = my_list.begin(); it != my_list.end(); ++it)
    {
        if (it->x == x && it->y == y)
        {
            deleted_node = *it; // Store the deleted node
            my_list.erase(it);  // Erase the node from the list
            break;
        }
    }
    return deleted_node;
}

// 找到链表中最小的f值的函数,输入链表，返回最小f的节点
Open_list::iterator find_min_f(Open_list &my_list)
{
    Open_list::iterator min_it = my_list.begin();
    float min_f = min_it->F;
    for (auto it = my_list.begin(); it != my_list.end(); ++it)
    {
        if (it->F < min_f)
        {
            min_f = it->F;
            min_it = it;
        }
    }
    return min_it;
}

// 判断Open_list中是不是有某个节点（通过坐标来确定），有的话返回true，没有返回false
bool judge_node_exist(const Open_list &mylist, int x, int y)
{
    for (auto it = mylist.begin(); it != mylist.end(); ++it)
    {
        if (it->x == x && it->y == y)
        {
            return true;
        }
    }
    return false;
}

// 遍历Open_list,返回与tmpY和tmpY匹配的节点指针
Open_list::iterator list_browse(Open_list &my_list, int tmpX, int tmpY)
{
    for (auto it = my_list.begin(); it != my_list.end(); ++it)
    {
        if (it->x == tmpX && it->y == tmpY)
        {
            return it;
        }
    }
    return my_list.end(); // Return end iterator if node not found
}

// 打印open list中的各个节点坐标以及F值
void msg_open_list(const Open_list &my_list)
{
    printf("Open_list: ");
    for (auto it = my_list.begin(); it != my_list.end(); ++it)
    {
        printf("(%d,%d) F=%.2f ", it->x, it->y, it->F);
    }
    printf("\n");
}

// 绝对值函数
float my_abs(int x)
{
    return x > 0 ? x : -x;
}

// G距离函数（给两个坐标(x1,y1)和（x2，y2））
float G_distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// H距离函数（节点和（x，y））
float H_distance(const Node &node, int x, int y)
{
    return my_abs(x - node.x) + my_abs(y - node.y);
}

// 显示地图
void show_map(const Open_list &my_list)
{
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (map[i][j] == 1)
            {
                printf("■");
            }
            else if (map[i][j] == 0)
            {
                printf("□");
            }
            else if (map[i][j] == 2)
            {
                printf("s");
            }
            else if (map[i][j] == 3)
            {
                printf("e");
            }
        }
        printf("\n");
    }
}

int main()
{
    std::vector<Node> open_list; 
    std::vector<Node> close_list; 

    Node start;    
    start.x = START_X;
    start.y = START_Y;
    start.G = 0;
    start.H = H_distance(start, END_X, END_Y);
    start.F = start.G + start.H;
    start.pFather = NULL;
    
    Node end;
    end.x = END_X;
    end.y = END_Y;
    end.G = 0;
    end.H = 0;
    end.F = 0;
    end.pFather = NULL;

    // 起始节点加入到open list
    open_list.push_back(start);
	int i, j; // 计数来遍历
    int cir = 1;
	while (cir)
	{
		// 寻找最小的F值节点，记为pCurrent（第一次循环也就是起点）
        if (open_list.empty())
        {
            printf("No path found!\n");
            break;
        }
        
        Open_list::iterator pCurrent = find_min_f(open_list);

        // 将pCurrent从open list中删除，并加入到close list
        close_list.push_back(*pCurrent);
        open_list.erase(pCurrent);
        printf("Current Node: (%d,%d)\n", pCurrent->x, pCurrent->y);

        // 上下左右四个方向
        for (i = -1; i < 2; i++)
		{
			for (j = -1; j < 2; j++)
			{
                // 如果是斜方向，跳过;如果是当前节点，跳过
                if (i != 0 && j != 0 || i == 0 && j == 0)
                {
                    continue;
                }
                // 超出地图范围，跳过
                if (pCurrent->x + i < 0 || pCurrent->x + i >= MAP_WIDTH 
                || pCurrent->y + j < 0 || pCurrent->y + j >= MAP_HEIGHT)
                {
                    continue;
                }
                // 如果是障碍物，跳过
                if (map[pCurrent->x + i][pCurrent->y + j] == 1)
                {
                    continue;
                }
                // 如果是close list中的节点，跳过
                if (judge_node_exist(close_list, pCurrent->x + i, pCurrent->y + j))
                {
                    continue;
                }
                // 如果是open list中的节点，更新G值
                if (judge_node_exist(open_list, pCurrent->x + i, pCurrent->y + j))
                {
                    Open_list::iterator pOpen = list_browse(open_list, pCurrent->x + i, pCurrent->y + j);
                    if (pCurrent->G + G_distance(pCurrent->x, pCurrent->y, pOpen->x, pOpen->y) < pOpen->G)
                    {
                        pOpen->G = pCurrent->G + G_distance(pCurrent->x, pCurrent->y, pOpen->x, pOpen->y);
                        pOpen->F = pOpen->G + pOpen->H;
                        pOpen->pFather = &(*pCurrent);
                    }
                }
                // 如果不在open list中，加入到open list
                else
                {
                    Node tmp;
                    tmp.x = pCurrent->x + i;
                    tmp.y = pCurrent->y + j;
                    tmp.G = pCurrent->G + G_distance(pCurrent->x, pCurrent->y, tmp.x, tmp.y);
                    tmp.H = H_distance(tmp, end.x, end.y);
                    tmp.F = tmp.G + tmp.H;
                    tmp.pFather = &(*pCurrent);
                    open_list.push_back(tmp);
                }
                // 如果是终点，结束循环
                if (pCurrent->x + i == end.x && pCurrent->y + j == end.y)
                {
                    printf("Find the end!\n");
                    cir = 0;
                    break;
                }
                // 跳出循环
                if (cir == 0)
                {
                    break;
                }
            }
        }
    }
    // 显示地图
    show_map(open_list);
    return 0;
}