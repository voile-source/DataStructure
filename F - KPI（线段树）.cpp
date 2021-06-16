/**
你工作以后, KPI 就是你的全部了. 我开发了一个服务，取得了很大的知名度。数十亿的请求被推到一个大管道后同时服务从管头拉取请求。让我们来定义每个请求都有一个重要值。我的KPI是由当前管道内请求的重要值的中间值来计算。现在给你服务记录，有时我想知道当前管道内请求的重要值得中间值。
Input
有大约100组数据。

每组数据第一行有一个n(1≤n≤10000)，代表服务记录数。

接下来有n行，每一行有3种形式
  "in x": 代表重要值为x(0≤x≤109)的请求被推进管道。
  "out": 代表服务拉取了管道头部的请求。
  "query: 代表我想知道当前管道内请求重要值的中间值. 那就是说，如果当前管道内有m条请求, 我想知道，升序排序后第floor(m/2)+1th 条请求的重要值.

为了让题目简单，所有的x都不同，并且如果管道内没有值，就不会有"out"和"query"操作。
Output
对于每组数据，先输出一行

Case #i:
然后每一次"query"，输出当前管道内重要值的中间值。
Sample Input
6
in 874
query
out
in 24622
in 12194
query
Sample Output
Case #1:
874
24622

解题思路：队列+权值线段树，队列模拟in和out操作，权值线段树维护中间值。踩到了一个新坑，使用ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);优化cin,cout后，printf将可能不会输出正确的值，
卡在了奇怪的地方，错了二十多发，呜呜呜）

**/

#include<iostream>
#include<algorithm> 
#include<queue>
#include<string>
using namespace std;
const int max_n=1e4+10;

struct tree{
	int v;
	int l,r;
}t[4*max_n];

void creat(int i,int l,int r)
{
	t[i].l=l,t[i].r=r;
	t[i].v=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	creat(i<<1,l,mid);
	creat(i<<1|1,mid+1,r);
}

void update(int i,int x,int s)
{
	if(t[i].l>x||t[i].r<x)return ;
	if(t[i].l==t[i].r) {
		t[i].v+=s;
		return ;
	}
	update(i<<1,x,s);
	update(i<<1|1,x,s);
	t[i].v=t[i<<1].v+t[i<<1|1].v;
}

int query(int i,int x)
{
	if(t[i].l==t[i].r) {
		return t[i].l;
	}
	if(t[i<<1].v>=x)return query(i<<1,x);
	else return query(i<<1|1,x-t[i<<1].v);
}

int main()
{
	int n,w=1;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while(cin>>n) {
		int a[max_n]={0},b[max_n];
		string pi[max_n];
		for(int i=1;i<=n;i++) {
			cin>>pi[i];
			if(pi[i]=="in"){
				cin>>a[i];
			}
		}
		int k=0;
		for(int i=1;i<=n;i++) {
			if(a[i])b[++k]=a[i];
		}
		sort(b+1,b+k+1);
		k=unique(b+1,b+k)-b;
		creat(1,1,k);
		queue<int> Q;
		cout<<"Case #"<<w++<<":"<<endl;
		for(int i=1;i<=n;i++){
			if(pi[i]=="in"){
				int t=lower_bound(b+1,b+k+1,a[i])-b;
				Q.push(a[i]);
				update(1,t,1);
			}else if(pi[i]=="out"){
				int m=Q.front();
				Q.pop();
				int t=lower_bound(b+1,b+k+1,m)-b;
				update(1,t,-1);
			} else {
				cout<<b[query(1,Q.size()/2+1)]<<endl;
			}
		}
	}
       return 0;
}
