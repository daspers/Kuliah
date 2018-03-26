#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main(){
	int n, a, sum=0;
	vector<int> v;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a;
		v.push_back(a);
		sum +=a;
	}
	if(v.size()){
		vector<int> s(v);
		sort(s.begin(), s.end());
		cout<<1.0*sum/v.size()<<endl;
		if(v.size()&1)
			cout<<s[n/2]<<endl;
		else
			cout<<(s[n/2]+s[n/2-1])/2.0<<endl;
		int c=0, b=0;
		for(vector<int>::iterator it = v.begin(); it!=v.end(); ++it){
			int t = count(v.begin(), v.end(), *it);
			if(t>c){
				b = *it;
				c = t;
			}
			else if(t==c){
				b = min(b, *it);
			}
		}
		cout<<b<<endl;
		for(vector<int>::iterator it = v.begin(); it!=v.end(); ++it)
			cout<<*it<<" ";
		cout<<b;
		v.push_back(b);
		for(int i=1;i<c;i++){
			cout<<" "<<b;
			v.push_back(b);
		}
		cout<<endl<<v.size()<<endl;
	}
	else{
		cout<<"-\n-\n-\n-\n0\n";
	}
	return 0;
}
