/**
奶牛们最近的旅游计划，是到苏必利尔湖畔，享受那里的湖光山色，以及明媚的阳光。作为整个旅游的策划者和负责人，贝茜选择在湖边的一家著名的旅馆住宿。这个巨大的旅馆一共有N 间客房，它们在同一层楼中顺次一字排开，在任何一个房间里，只需要拉开窗帘，就能见到波光粼粼的湖面。

贝茜一行，以及其他慕名而来的旅游者，都是一批批地来到旅馆的服务台，希望能订到D_i (1 <= D_i <= N)间连续的房间。服务台的接待工作也很简单：如果存在r满足编号为r..r+D_i-1的房间均空着，他就将这一批顾客安排到这些房间入住；如果没有满足条件的r，他会道歉说没有足够的空房间，请顾客们另找一家宾馆。如果有多个满足条件的r，服务员会选择其中最小的一个。

旅馆中的退房服务也是批量进行的。每一个退房请求由2个数字X_i、D_i描述，表示编号为X_i..X_i+D_i-1 (1 <= X_i <= N-D_i+1)房间中的客人全部离开。退房前，请求退掉的房间中的一些，甚至是所有，可能本来就无人入住。

而你的工作，就是写一个程序，帮服务员为旅客安排房间。你的程序一共需要处理M 个按输入次序到来的住店或退房的请求。第一个请求到来前，旅店中所有房间都是空闲的。

输入格式
第一行输入n，m ，n代表有n个房间，编号为1---n，开始都为空房，m表示以下有m行操作，以下 每行先输入一个数 i ，表示一种操作：

若i为1，表示查询房间，再输入一个数x，表示在1--n 房间中找到长度为x的连续空房，输出连续x个房间中左端的房间号，尽量让这个房间号最小，然后入住。若找不到长度为x的连续空房，输出0。

若i为2，表示退房，再输入两个数 x，y 代表 房间号 x---x+y-1 退房，即让房间为空。

输出格式
对于每一个入住请求，输出查询出可以入住的最小房间号，如果不能安排入住输出0；

样例输入
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
样例输出
1
4
7
0
5
数据范围
1 <= N <= 50,000； 1 <= M < 50,000

解题思路：权值线段树维护最大连续子区间，向上传递的时候我们需要维护三个值：分别是区间的左起最大连续空区间长度，右起最大连续空区间长度和最大连续空区间的长度。
然后其余的操作和普通的权值线段树没什么差别

**/

#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int max_n=5e4;

struct node{
	int l,r;
	int ls,rs;
	int sum;
	int la;
	int len;
}t[8*max_n];

void push_up(int i)
{
	if(t[i<<1].sum==t[i<<1].len){
		t[i].ls=t[i<<1].sum+t[i<<1|1].ls;
	}else{
		t[i].ls=t[i<<1].ls;
	}
	if(t[i<<1|1].sum==t[i<<1|1].len){
		t[i].rs=t[i<<1|1].sum+t[i<<1].rs;
	}else{
		t[i].rs=t[i<<1|1].rs;
	}
	t[i].sum=max(t[i<<1].rs+t[i<<1|1].ls,max(t[i<<1].sum,t[i<<1|1].sum));
} 

void creat(int i,int l,int r)
{
	t[i].l=l,t[i].r=r;
	t[i].len=t[i].sum=t[i].ls=t[i].rs=r-l+1;
	t[i].la=0;
	if(l==r){
		return;
	}
	int mid=(l+r)>>1;
	creat(i<<1,l,mid);
	creat(i<<1|1,mid+1,r);
}

void push_down(int i)
{
	if(t[i].la){
		t[i<<1].la=t[i<<1|1].la=t[i].la;
		t[i<<1].ls=t[i<<1].rs=t[i<<1].sum=t[i].la==-1?0:t[i<<1].len;
		t[i<<1|1].ls=t[i<<1|1].rs=t[i<<1|1].sum=t[i].la==-1?0:t[i<<1|1].len;
		t[i].la=0;
	}
}

void update(int i,int x,int y,int s)
{
	push_down(i);
	if(t[i].l>y||t[i].r<x)return ;
	if(t[i].l>=x&&t[i].r<=y){
		if(s==1){
			t[i].sum=t[i].ls=t[i].rs=t[i].len;
		}else t[i].sum=t[i].ls=t[i].rs=0;
		t[i].la=s;
		return ;
	}
	update(i<<1,x,y,s);
	update(i<<1|1,x,y,s);
	push_up(i);
}

int query(int i,int x)
{
	push_down(i);
	int mid=(t[i].l+t[i].r)>>1;
	if(t[i].l==t[i].r)return t[i].l;
	if(t[i<<1].sum>=x)return query(i<<1,x);
	if(t[i<<1].rs+t[i<<1|1].ls>=x)return mid-t[i<<1].rs+1;
	return query(i<<1|1,x);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	creat(1,1,n);
	for(int i=1;i<=m;i++){
		int op;
		cin>>op;
		if(op==1){
			int x;
			cin>>x;
			if(t[1].sum<x){
				cout<<0<<endl;
				continue;
			}
			int te=query(1,x);
			cout<<te<<endl;
			update(1,te,te+x-1,-1);
		}else{
			int x,y;
			cin>>x>>y;
			update(1,x,x+y-1,1);
		} 	
	}	
} 
