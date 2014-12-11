#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <map>
#include <queue>
#include <set>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;

class node{
public:
    node(){
        bad=false;
        prev=NULL;
        for(int i=0;i<26;i++)
            next[i]=NULL;
    }
    bool bad;//是否是终点
    node *next[26];
    node *prev;//前缀节点
};

class trie{
public:
    trie(){
        root=new node();
    }
    void in(string &str){
        node *proot=root;
        int l=str.size();
        for(int i=0;i<l;i++){
            if(!proot->next[str.at(i)-'a'])
                proot->next[str.at(i)-'a']=new node();
            proot=proot->next[str.at(i)-'a'];
        }
        proot->bad=true;//单词结尾节点
    }
    void bulid (){
        queue<node*>Q;
        node *proot=root;
        for(int i=0;i<26;i++){
            if(proot->next[i]){
                proot->next[i]->prev=root;
                Q.push(proot->next[i]);
            }
        }
        while(!Q.empty()){
            proot=Q.front();
            Q.pop();
            for(int i=0;i<26;i++){
                node *p=proot->next[i];
                if(p&&!p->bad){
                    node* prev=proot->prev;
                    while(prev){
                        if(prev->next[i]){
                            p->prev=prev->next[i];
                            if(p->prev->bad)
                                p->bad=true;
                            break;
                        }else
                            prev=prev->prev;
                    }
                    if(p->prev==NULL)
                        p->prev=root;
                    Q.push(p);
                }
            }
        }
    }
    bool sea(string &str){
        int l=str.size();
        node *proot=root;
        for(int i=0;i<l;i++){
            while(true){
                if(proot->next[str.at(i)-'a']){
                    proot=proot->next[str.at(i)-'a'];
                    if(proot->bad)
                        return true;
                    break;
                }else
                    proot=proot->prev;
                if(proot==root||!proot){
                    proot=root;
                    break;
                }
            }
        }
        return false;
    }
private:
    node *root;
};

int main(){
    ios::sync_with_stdio(false) ;
    int n;
    trie T;
    string word;
    string pas;
    for(cin>>n;n--;){
        cin>>word;
        T.in(word);
    }
    T.bulid();
    cin>>pas;
    bool sig=T.sea(pas);
    if(sig)printf("YES\n");
    else printf("NO\n");
    return 0;
}
