/**
It's time for music! A lot of popular musicians are invited to join us in the music festival. Each of them will play one of their representative songs. To make the programs more interesting and challenging, the hosts are going to add some constraints to the rhythm of the songs, i.e., each song is required to have a 'theme section'. The theme section shall be played at the beginning, the middle, and the end of each song. More specifically, given a theme section E, the song will be in the format of ' EAEBE', where section A and section B could have arbitrary number of notes. Note that there are 26 types of notes, denoted by lower case letters 'a' - 'z'.

To get well prepared for the festival, the hosts want to know the maximum possible length of the theme section of each song. Can you help us?
Input
The integer N in the first line denotes the total number of songs in the festival. Each of the following N lines consists of one string, indicating the notes of the i-th (1 <= i <= N) song. The length of the string will not exceed 10^6.

Output
There will be N lines in the output, where the i-th line denotes the maximum possible length of the theme section of the i-th song.
 

Sample Input
6
xy
abc
aaa
aaaaba
aaxoaaaaa
aaaaabaaa
Sample Output
0
0
1
1
2
2

题目大意：给定一个字符串，找出三个相同子串，它们分别是这个字符串的前缀，后缀，前后缀中间不重合部分。我们要做的就是使这个子串的长度最大。

解题思路：既然是要找子串的问题，那么我们首先可以想到枚举，但很明显，枚举会超时。所以我们可以使用kmp算法的next数组，来辅助我们进行枚举。我们每次找一个最长的相等前后缀，只要能找，我们就一直找下去，
直到不能找了（返回0）。期间，我们还要考虑前后缀重合的问题，当前后缀重合的时候，我们可以在前后缀中再找子串去进行匹配，直到找到中间相等的子串，或者找不到（返回0）

**/

#include<iostream>
#include<string> 
using namespace std;
const int max_n = 1e6+10;

int pre[max_n];

void getnext(string s)
{
	for(int i=2,j=0;i<s.size();i++){
		while(j&&s[i]!=s[j+1])j=pre[j];
		if(s[i]==s[j+1])j++;
		pre[i]=j; 
	} 
} 

int kmp(string s)
{
	getnext(s);
	int l=s.size()-1;
	for(int i=pre[l];i;i=pre[i]) {
		for(int j=i*2;j<=l-i;j++) {
			if(pre[j]>=i)return i;
		}
	}
	return 0;
}

int main()
{
	int t;
	cin>>t; 
	while(t--){
		string s;
		cin>>s;
		s=" "+s;
		cout<<kmp(s)<<endl;
	}
} 
