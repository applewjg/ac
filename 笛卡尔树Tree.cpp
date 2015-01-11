#include <iostream>
#include <queue>
using namespace std;
const int maxnum=10;

int a[maxnum] = {3, 2, 4, 5, 6, 8, 1, 9, 10, 7};
struct node
{
    int key;
    int parent;
    int l;
    int r;
}tree[maxnum];


void Init()
{
    int i;
    for(i=0;i<maxnum;i++)
        tree[i].parent=tree[i].l=tree[i].r=-1;  //初始化
}

int Build_Tree()
{
    int i,top,k;
    int stack[maxnum];
    top=-1;
    for(i=0;i<maxnum;i++)
    {
        k=top;
        while(k>=0 && a[stack[k]]>a[i])  //栈中比当前元素大的都出栈
            k--;

        if(k!=-1)  //find it，栈中元素没有完全出栈，当前元素为栈顶元素的右孩子
        {
            tree[i].parent=stack[k];
            tree[stack[k]].r=i;
        }
        if(k<top)    //出栈的元素为当前元素的左孩子
        {
            tree[stack[k+1]].parent=i;
            tree[i].l=stack[k+1];
        }

        stack[++k]=i;//当前元素入栈
        top=k;//top指向栈顶元素
    }
    tree[stack[0]].parent=-1;//遍历完成后的栈顶元素就是根
    return stack[0];
}

void inorder(int node)
{
   if(node!=-1)
   {
       inorder(tree[node].l);
       cout<<tree[node].key<<endl;
       inorder(tree[node].r);
   }
}

void levelorder(int node)
{
    queue<int> q;
    q.push(node);
    while(!q.empty())
    {
        int k=q.front();
        q.pop();
        cout<<tree[k].key<<endl;
        if(tree[k].l!=-1)
            q.push(tree[k].l);
        if(tree[k].r!=-1)
            q.push(tree[k].r);
    }
}

int main()
{
    int i;
    Init();

    for(i=0;i<maxnum;i++)
    {
        //cin>>a[i];
        tree[i].key=a[i];
    }

    int root=Build_Tree();

    inorder(root);
    levelorder(root);
    return 0;
}

/*
3 2 4 5 6 8 1 9 10 7
*/