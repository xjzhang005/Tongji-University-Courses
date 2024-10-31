#include<iostream>
#include<cmath>
#include<stack> 
using namespace std;
int main()
{
    int cnt = 0;
    char t[1000000];
    while (cin >> t)
    {
        if (t[0] == '#')
            break;
        int nh = 0, h = 0, nh2 = 0, h2 = 0; 
        stack<int> now;
        now.push(0);
        for (int i = 0; t[i] != '\0'; i++)
        {
            if (t[i] == 'd')
            {
                nh++;//记录树的当前高度
                nh2++;//记录二叉树的当前高度
                now.push(nh2);//把当前结点入栈
            }
            else
            {
                nh--;
                nh2 = now.top();//如果下一个是d那么这个结点在二叉树中就是下一个结点的父亲结点
                now.pop();//这一结点已经不在路径上了，出栈
            }
            h2 = max(h2, nh2);
            h = max(h, nh);
        }
        cout << "Tree " << ++cnt << ": " << h << " => " << h2 << endl;  
    }
    return 0;
}
