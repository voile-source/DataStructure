/**
给你有26个字母的密码表，a[i]表示第i个字母经过密码表转变成的密码字符。（如a[2]==‘c’，表示字母‘b’加密后变成‘c’）
现在有一条信息，前一半为经过加密的字符，后一半为前一半加密前的字符。不过由于某些原因，后一半的部分内容消失了，你现在的任务是，恢复整条信息的内容。
Input
The first line contains only one integer T, which is the number of test cases.
Each test case contains two lines. The first line of each test case is the conversion table S. S[i] is the ith latin letter's cryptographic letter. The second line is the intercepted text which has n letters that you should recover. It is possible that the text is complete.
Hint
Range of test data:
T<= 100 ;
n<= 100000;
Output
For each test case, output one line contains the shorest possible complete text.
Sample Input
2
abcdefghijklmnopqrstuvwxyz
abcdab
qwertyuiopasdfghjklzxcvbnm
qwertabcde
Sample Output
abcdabcd
qwertabcde

解题思路：
读题可知，暗文的长度在任何情况下都是大于明文的，
所以我们可以假设字符串的前一段就是暗文，
然后从字符串的中间开始找，
直到后一段完全匹配。

**/

#include<iostream>
#include<string>
using namespace std;

int main()
{
	int t;
	cin>>t;
	while(t--) {
		string ch;
		string str;
		cin>>ch>>str;
		int i,j=0;
		for(i=(str.size()+1)/2;i<str.size();i++) {
			if(ch[str[i]-'a']!=str[j])continue;
			else {
				j++;
				int flag =0;
				for(int k=i+1;k<str.size();k++){
					if(ch[str[k]-'a']!=str[j++]){
						flag=1;
						break;
					}
				}
				if(!flag)break;
			}
		}
		for(int k=0;k<i;k++){
			cout<<str[k];
		}
		for(int k=0;k<i;k++) {
			for(int w=0;w<26;w++) {
				char c=w+'a';
				if(str[k]==ch[w])cout<<c;
			}
		}
		cout<<endl;
	}
} 
