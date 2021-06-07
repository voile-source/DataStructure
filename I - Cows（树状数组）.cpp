/**
Farmer John's cows have discovered that the clover growing along the ridge of the hill (which we can think of as a one-dimensional number line) in his field is particularly good.

Farmer John has N cows (we number the cows from 1 to N). Each of Farmer John's N cows has a range of clover that she particularly likes (these ranges might overlap). The ranges are defined by a closed interval [S,E].

But some cows are strong and some are weak. Given two cows: cow i and cow j, their favourite clover range is [Si, Ei] and [Sj, Ej]. If Si <= Sj and Ej <= Ei and Ei - Si > Ej - Sj, we say that cow i is stronger than cow j.

For each cow, how many cows are stronger than her? Farmer John needs your help!
题目翻译

农夫约翰的牛发现，他的田地里沿着山脊生长的三叶草（我们可以将其视为一维数字线）特别好。

农夫约翰有N头母牛（我们将母牛的编号从1到N）。每位农夫约翰的N头母牛都有她特别喜欢的三叶草范围（这些范围可能重叠）。范围由闭合间隔[S，E]定义。

但是有些母牛很强壮，有些却很弱。给定两个母牛：母牛i和母牛j，它们最喜欢的三叶草范围是[Si，Ei]和[Sj，Ej]。如果Si <= Sj并且Ej <= Ei并且Ei-Si> Ej-Sj，我们说母牛i比母牛j强。

对于每头母牛，有几头母牛比她强？农夫约翰需要您的帮助！

输入项

输入包含多个测试用例。

对于每个测试用例，第一行是整数N（1 <= N <= 10 ^ 5），它是母牛的数量。然后是N行，其第i行包含两个整数：S和E（0 <= S<=E<=1e5 )

输入的末尾包含单个0。

输出量

对于每个测试用例，输出一行包含n个以空格分隔的整数，其中第i个数字指定比母牛i强的母牛的数量。

Sample Input

3

1 2

0 3

3 4

0

Sample Output

1 0 0

Hint

Huge input and output,scanf and printf is recommended.

Input
The input contains multiple test cases.
For each test case, the first line is an integer N (1 <= N <= 10 5), which is the number of cows. Then come N lines, the i-th of which contains two integers: S and E(0 <= S < E <= 10 5) specifying the start end location respectively of a range preferred by some cow. Locations are given as distance from the start of the ridge.

The end of the input contains a single 0.
Output
For each test case, output one line containing n space-separated integers, the i-th of which specifying the number of cows that are stronger than cow i.
Sample Input
3
1 2
0 3
3 4
0
Sample Output
1 0 0
Hint
Huge input and output,scanf and printf is recommended.

题目大意，给定n个区间，求出每个区间有多少个可以完全包含的区间。

解题思路：首先我们对这n个区间进行排序，先按E值作为主要关键字排降序，如果两个区间的E值相等，按l值排升序，然后我们就可以用树状数组求出每个区间有多少个可以完全包括它的区间了，记得处理一下全进完全重复
的情况，然后输入输出用scanf，printf（不然会超时）

**/
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int max_n=1e5+10; 

struct node{
	int l,r;
	int num;
}a[max_n]; 

int t[max_n],ans[max_n];
int n;

bool cmp(node a,node b)
{
	if(a.r==b.r)return a.l<b.l;
	return a.r>b.r;
}

int lowbit(int x)
{
	return x&(-x);
}

void update(int x)
{
	for(int i=x;i<=n;i+=lowbit(i)){
		t[i]++;
	}
}

int getsum(int x)
{
	int s=0;
	for(int i=x;i;i-=lowbit(i)){
		s+=t[i];
	}
	return s;
}

int main()
{
	while(scanf("%d",&n)&&n){
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i].l,&a[i].r);
			a[i].num=i; 
		}
		sort(a+1,a+n+1,cmp);
		memset(t,0,sizeof t);
		ans[a[1].num]=0;
		update(a[1].l+1);
		for(int i=2;i<=n;i++) {
			if(a[i].l==a[i-1].l&&a[i].r==a[i-1].r) {
				ans[a[i].num]=ans[a[i-1].num];
			}else {
				ans[a[i].num]=getsum(a[i].l+1);
			}
			update(a[i].l+1);
		}
		for(int i=1;i<=n;i++){
			printf("%d ",ans[i]);
		}
		printf("\n");
	}	 
} 
