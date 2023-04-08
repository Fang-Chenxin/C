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
int step = 0;
int px[100], py[100];

struct Node
{
    float G;
    float H;
    float F;
    int x;
    int y;
};

struct Point
{
    int x;
    int y;
};

typedef std::vector<Node> Node_list;

/*障碍物为1（地图可给根据需要修改）*/
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}};
Point parent[MAP_HEIGHT][MAP_WIDTH];
//---------------------------------------------------------------------------//
class A_list
{
public:
    Node_list nodes;
    // 遍历nodes,返回与tmpY和tmpY匹配的节点指针
    Node_list::iterator list_browse(int tmpX, int tmpY);
    // 判断nodes中是不是有某个节点（通过坐标来确定），有的话返回true，没有返回false
    bool judge_node_exist(int x, int y);
    // 删除nodes中某个节点，通过坐标删除,并且返回这个删除的节点指针，方便加入到close list
    void list_delete_point(int tmpX, int tmpY);
    // 找到nodes中最小的f值的节点,输入nodes，返回最小f的节点
    Node_list::iterator find_min_f();
    // 打印nodes中的各个节点坐标以及F值
    void show_list();
};

//---------------------------------------------------------------------------//
// 绝对值函数
float my_abs(int x);
// G距离函数（给两个坐标(x1,y1)和（x2，y2））
float G_distance(int x1, int y1, int x2, int y2);
// H距离函数（节点和（x，y））
float H_distance(const Node &node, int x, int y);
// 打印所有父节点的坐标
void show_parent(int x, int y);
// 显示路径
void show_path();

// 删除nodes中某个节点，通过坐标删除
void A_list::list_delete_point(int x, int y)
{
    Node deleted_node; // Node to be deleted
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->x == x && it->y == y)
        {
            deleted_node = *it; // Store the deleted node
            nodes.erase(it);    // Erase the node from the list
            break;
        }
    }
}

// 找到链表中最小的f值的函数,输入链表，返回最小f的节点
Node_list::iterator A_list::find_min_f()
{
    Node_list::iterator min_it = nodes.begin();
    float min_f = min_it->F;
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->F < min_f)
        {
            min_f = it->F;
            min_it = it;
        }
    }
    return min_it;
}

// 判断nodes中是不是有某个节点（通过坐标来确定），有的话返回true，没有返回false
bool A_list::judge_node_exist(int x, int y)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->x == x && it->y == y)
        {
            return true;
        }
    }
    return false;
}

// 遍历nodes,返回与tmpY和tmpY匹配的节点指针
Node_list::iterator A_list::list_browse(int tmpX, int tmpY)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        if (it->x == tmpX && it->y == tmpY)
        {
            return it;
        }
    }
    return nodes.end(); // Return end iterator if node not found
}

// 打印nodes中的各个节点坐标以及F值
void A_list::show_list()
{
    printf("Node_list: ");
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
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

// 寻找转弯点
void find_turn_point()
{
    int count = 0;
    for (int i = 0; i < step - 1; i++)
    {
        if (px[i + 1] != px[i - 1] && py[i + 1] != py[i - 1])
        {
            printf("turn(%d, %d)->(%d,%d)->(%d,%d)\n",
                   px[i - 1], py[i - 1], px[i], py[i], px[i + 1], py[i + 1]);
            count++;
        }
    }
}

// 显示路径图
void show_path()
{
    map[START_X][START_Y] = 2;
    map[END_X][END_Y] = 3;
    printf("\n");
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
            else if (map[i][j] == 4)
            {
                printf("o");
            }
        }
        printf("\n");
    }
}
// 最短路径
void show_parent(int x, int y)
{
    if (x == START_X && y == START_Y)
    {
        printf("(%d,%d)", x, y);
        return;
    }
    px[step] = x;
    py[step] = y;
    step++;
    map[x][y] = 4;
    show_parent(parent[x][y].x, parent[x][y].y);
    printf("->(%d,%d)", x, y);
}

int main()
{
    A_list open_list;
    A_list close_list;

    Node start;

    start.x = START_X;
    start.y = START_Y;
    start.G = 0;
    start.H = H_distance(start, END_X, END_Y);
    start.F = start.G + start.H;

    Node end;
    end.x = END_X;
    end.y = END_Y;
    end.G = 0;
    end.H = 0;
    end.F = 0;

    // 起始节点加入到nodes
    open_list.nodes.push_back(start);
    int i, j;
    int cir = 1;
    bool found = false;
    while (cir)
    {
        // 寻找最小的F值节点，记为pCurrent（第一次循环也就是起点）
        if (open_list.nodes.empty())
        {
            break;
        }

        Node_list::iterator pCurrent = open_list.find_min_f();
        Node current = *pCurrent;
        // 将pCurrent从nodes中删除，并加入到close list
        close_list.nodes.push_back(*pCurrent);
        open_list.nodes.erase(pCurrent);
        printf("Current Node: (%d,%d)\n", current.x, current.y);

        // 上下左右四个方向
        for (i = -1; i < 2; i++)
        {
            for (j = -1; j < 2; j++)
            {
                int nowX = current.x + i;
                int nowY = current.y + j;
                // 如果是斜方向，跳过;如果是当前节点，跳过
                if (i != 0 && j != 0 || i == 0 && j == 0)
                {
                    continue;
                }
                // 超出地图范围，跳过
                if (nowX < 0 || nowX >= MAP_WIDTH || nowY < 0 || nowY >= MAP_HEIGHT)
                {
                    continue;
                }
                // 如果是障碍物，跳过
                if (map[nowX][nowY] == 1)
                {
                    continue;
                }
                // 不是nodes里面的节点
                if (!open_list.judge_node_exist(nowX, nowY))
                {
                    // 如果是close list中的节点，跳过
                    if (close_list.judge_node_exist(nowX, nowY))
                    {
                        continue;
                    }
                    // 如果是终点，结束循环
                    else if (nowX == end.x && nowY == end.y)
                    {
                        printf("Find the end!\n");
                        found = true;
                        parent[nowX][nowY].x = current.x;
                        parent[nowX][nowY].y = current.y;
                        cir = 0;
                        goto endcode;
                        break;
                    }
                    // 如果不在nodes中，加入到nodes
                    else
                    {
                        Node tmp;
                        tmp.x = nowX;
                        tmp.y = nowY;
                        tmp.G = current.G + G_distance(current.x, current.y, tmp.x, tmp.y);
                        tmp.H = H_distance(tmp, end.x, end.y);
                        tmp.F = tmp.G + tmp.H;
                        open_list.nodes.push_back(tmp);
                        parent[nowX][nowY].x = current.x;
                        parent[nowX][nowY].y = current.y;
                    }
                }
                // 如果是nodes中的节点，更新G值
                else
                {
                    Node_list::iterator pOpen = open_list.list_browse(nowX, nowY);
                    float currentG = current.G + G_distance(current.x, current.y, pOpen->x, pOpen->y);
                    if (currentG < pOpen->G)
                    {
                        pOpen->G = currentG;
                        pOpen->F = pOpen->G + pOpen->H;
                        parent[nowX][nowY].x = current.x;
                        parent[nowX][nowY].y = current.y;
                    }
                }
            }
        }
    }
    endcode:
    if (found)
    {
        printf("Find the path!\n");
        // 显示最短路径
        show_parent(END_X, END_Y);
        // 显示路径图
        show_path();
        // 寻找转弯点
        find_turn_point();
    }
    else
    {
        printf("No path found!\n");
    }
    return 0;
}