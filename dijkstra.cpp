#include <iostream>
#include <set>
#include <algorithm>
#include <stack>
using namespace std;
const long DBL_MAX = 500000;
long g[6][6] = {
    {0, 7, 9, DBL_MAX, DBL_MAX, 14},      //v1
    {7, 0, 10, 15, DBL_MAX, DBL_MAX},     //v2
    {9, 10, 0, 11, DBL_MAX, 2},           //v3
    {DBL_MAX, 15, 11, 0, 6, DBL_MAX},     //v4
    {DBL_MAX, DBL_MAX, DBL_MAX, 6, 0, 9}, //v5
    {14, DBL_MAX, 2, DBL_MAX, 9, 0}       //v6
};

long dist[6] = {0};
int pred[6] = {0};

std::set<int> v = {1, 2, 3, 4, 5};
std::set<int> s = {1, 2, 3, 4, 5};

void dijkstra()
{
    // 1. init dist
    for (int i = 1; i < 6; i++)
    {
        dist[i] = g[0][i];
        if (dist[i] == DBL_MAX)
        {
            pred[i] = -1;
        }
        else
        {
            pred[i] = 0;
        }
    }

    while (!v.empty())
    {
        int pos = 0;
        auto min = DBL_MAX;
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            int x = *it;
            if (min > dist[x])
            {
                min = dist[x];
                pos = x;
            }
        }

        v.erase(pos);

        for (auto it = v.begin(); it != v.end(); ++it)
        {
            int i = *it;

            if (dist[pos] + g[pos][i] < dist[i])
            {
                dist[i] = dist[pos] + g[pos][i];
                pred[i] = pos;
            }
        }
    }
}

long path[6][6] = {0};
long minValue[6][6] = {0};

void floyd()
{
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {

            if (g[i][j] == DBL_MAX)
            {
                minValue[i][j] = DBL_MAX;
            }
            else
            {
                minValue[i][j] = g[i][j];
            }

            path[i][j] = i;
        }
    }

    for (int k = 0; k < 6; ++k)
    {
        for (int i = 0; i < 6; ++i)
        {

            if (k != i)
            {
                if (minValue[i][k] != DBL_MAX)
                {
                    for (int j = 0; j < 6; ++j)
                    {
                        if (minValue[i][k] + minValue[k][j] < minValue[i][j])
                        {
                            minValue[i][j] = minValue[i][k] + minValue[k][j];
                            path[i][j] = k;
                        }
                    }
                }
            }
        }
    }
}

void printShortPath()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int k = path[i][j];
            std::cout << "path: v" << i << " >v" << k;
            while (k != j)
            {
                k = path[k][j];
                std::cout << "v" << k;
            }
            std::cout << std::endl;
        }
    }
}

int main()
{

    dijkstra();

    for (int i = 0; i < 6; ++i)
    {
        std::cout << i << "  = " << dist[i] << std::endl;
    }
    std::cout << "----------------------" << std::endl;
    for (int i = 0; i < 6; ++i)
    {
        std::cout << i << "  = " << pred[i] << std::endl;
    }
    std::cout << "----------------------" << std::endl;

    int pos = 4;
    std::stack<int> stack;
    stack.push(pos);
    while (pos > 0)    
    {  
        pos = pred[pos];
        stack.push(pos);
    }
    while (!stack.empty())
    {
      auto top = stack.top();
       std::cout << "v" << top;
       stack.pop();
    }
    
    std::cout<< std::endl;

    std::cout << "------------------------------------" << std::endl;

    floyd();

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            std::cout << path[i][j] << "(" << minValue[i][j] << ")  ";
        }

        std::cout << std::endl;
    }

    std::cout << "--------------------------------------" << std::endl;
    //printShortPath();

    pos = 4;
    stack.push(pos);
    while (pos !=0)    
    {  
        pos = path[0][pos];
        stack.push(pos);
    }
    while (!stack.empty())
    {
      auto top = stack.top();
       std::cout << "v" << top;
       stack.pop();
    }
    std::cout << std::endl;


    return 0;
}