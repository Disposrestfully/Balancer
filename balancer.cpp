#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=105;
char s1[N],s2[N];
int tot,tt,l1,l2;
bool is_ion;
map<vector<char>,int>c[N];
map<vector<char>,int>::iterator it;
map<vector<char>,bool>p;
map<vector<char>,bool>::iterator iter;
vector<char>ss[N];
int e[N];
int gcd(int x,int y){
	if (x==0 && y==0){
		printf("$$\\tan90^\\circ$$\n\n");
		exit(0);
	}
	if (!y) return x;
	return gcd(y,x%y);
}
struct frac{
	int x,y;
	#define gcd(a,b) gcd(abs(a),abs(b))
	inline bool operator < (const frac &u)const{
		return x*u.y<y*u.x;
	}
	inline bool operator != (const frac &u)const{
		return ((x!=u.x) || (y!=u.y));
	}
	inline frac operator + (const frac &u){
		frac res=(frac){x*u.y+y*u.x,u.y*y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
		
	}
	inline frac operator + (const int &u){
		frac res=(frac){x+y*u,y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
	}
	inline frac operator - (const frac &u){
		frac res=(frac){x*u.y-y*u.x,u.y*y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
		
	}
	inline frac operator - (const int &u){
		frac res=(frac){x-y*u,y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
	}
	inline frac operator * (const frac &u){
		frac res=(frac){x*u.x,y*u.y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
		
	}
	inline frac operator * (const int &u){
		frac res=(frac){x*u,y};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
	}
	inline frac operator / (const frac &u){
		frac res=(frac){x*u.y,y*u.x};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
		
	}
	inline frac operator / (const int &u){
		frac res=(frac){x,y*u};
		if (res.x<0 && res.y<0) res.x=-res.x,res.y=-res.y;
		int d=gcd(res.x,res.y);
		return (frac){res.x/d,res.y/d};
	}
};
inline frac abs(frac k){
	return (frac){abs(k.x),abs(k.y)};
}
namespace input{
	typedef pair<vector<char>,int> pr;
	#define mp make_pair
	vector<char>stmp,now;
	stack<pr>sta,st;
	inline void push_to_sta(){
		int cnt=0;
		for (int j=0,sz2=now.size();j<sz2;++j)
			if (now[j]<='9' && now[j]>='0')
				cnt=(cnt<<1)+(cnt<<3)+now[j]-'0';
		while (now[now.size()-1]>='0' && now[now.size()-1]<='9') now.pop_back();
		if (!cnt) cnt=1;
		sta.push(mp(now,cnt));
		now=vector<char>();
	}
	inline vector<char> trans(vector <char> s){
		vector<char>res;
		res=vector<char>();
		for (int i=0,ssz=s.size();i<ssz;++i){
			if (s[i]<='9' && s[i]>='0'){
				res.push_back('_');
				res.push_back('{');
				int j;
				for (j=i;j<ssz && s[j]<='9' && s[j]>='0';++j)
					res.push_back(s[j]);
				i=j-1;
				res.push_back('}');
			}else res.push_back(s[i]);
		}
		return res;
	}
	inline void count(vector<char> s){
		ss[++tot]=trans(s);
		int sz=s.size();
		/*for (int i=0;i<sz;++i)
			printf("%c",s[i]);
		printf("\n");*/
		for (int i=0;i<sz;++i){
			if (s[i]>='A' && s[i]<='Z'){
				if (!now.empty()) push_to_sta();
				now.push_back(s[i]);
			}else if (s[i]=='('){
				if (!now.empty()) push_to_sta();
				sta.push(mp(now,-1));
			}else if (s[i]==')'){
				if (!now.empty()) push_to_sta();
				int cnt=0,las=i;
				for (int j=i+1;j<sz;++j){
					if (s[j]<='9' && s[j]>='0')
						cnt=(cnt<<1)+(cnt<<3)+s[j]-'0',las=j;
					else break;
				}
				if (!cnt) cnt=1;
				i=las;
				while (~sta.top().second){
					st.push(sta.top());
					st.top().second*=cnt;
					sta.pop();
				}
				sta.pop();
				while (!st.empty()) sta.push(st.top()),st.pop();
			}else now.push_back(s[i]);
		}
		if (!now.empty()) push_to_sta();
		while (!sta.empty())
			p[sta.top().first]=1,c[tot][sta.top().first]+=sta.top().second,sta.pop();
	}
	inline void read(char *s1,char *s2,int l1,int l2){
		for (int i=1;i<=l1;++i){
			if (s1[i]==' '){
				count(stmp);
				stmp=vector<char>();
			}else stmp.push_back(s1[i]);
		}
		if (!stmp.empty()) count(stmp);
		stmp=vector<char>();
		tt=tot;
		for (int i=1;i<=l2;++i){
			if (s2[i]==' '){
				count(stmp);
				stmp=vector<char>();
			}else stmp.push_back(s2[i]);
		}
		if (!stmp.empty()) count(stmp);
		/*for (int i=1;i<=tot;++i){
			it=c[i].begin();
			while (it!=c[i].end()){
				for (int j=0,sz=it->first.size();j<sz;++j)
					printf("%c",it->first[j]);
				printf(" %d\n",it->second);
				it++;
			}
			printf("\n");
		}*/
	}
}
namespace input_ion{
	typedef pair<vector<char>,int> pr;
	#define mp make_pair
	vector<char>stmp,now;
	stack<pr>sta,st;
	inline void push_to_sta(){
		int cnt=0;
		for (int j=0,sz2=now.size();j<sz2;++j)
			if (now[j]<='9' && now[j]>='0')
				cnt=(cnt<<1)+(cnt<<3)+now[j]-'0';
		while (now[now.size()-1]>='0' && now[now.size()-1]<='9') now.pop_back();
		if (!cnt) cnt=1;
		sta.push(mp(now,cnt));
		now=vector<char>();
	}
	inline vector<char> trans(vector <char> s){
		vector<char>res;
		res=vector<char>();
		for (int i=0,ssz=s.size();i<ssz;++i){
			if (s[i]=='^'){
				res.push_back('^');
				res.push_back('{');
				for (int j=i+1;j<ssz;++j)
					res.push_back(s[j]);
				res.push_back('}');
				break;
			}else if (s[i]<='9' && s[i]>='0'){
				res.push_back('_');
				res.push_back('{');
				int j;
				for (j=i;j<ssz && s[j]<='9' && s[j]>='0';++j)
					res.push_back(s[j]);
				i=j-1;
				res.push_back('}');
			}else res.push_back(s[i]);
		}
		return res;
	}
	inline void count(vector<char> s){
		ss[++tot]=trans(s);
		int S=s.size(),sz;
		for (sz=0;s[sz]!='^' && sz<S;++sz);
		for (int i=0;i<sz;++i){
			if (s[i]>='A' && s[i]<='Z'){
				if (!now.empty()) push_to_sta();
				now.push_back(s[i]);
			}else if (s[i]=='('){
				if (!now.empty()) push_to_sta();
				sta.push(mp(now,-1));
			}else if (s[i]==')'){
				if (!now.empty()) push_to_sta();
				int cnt=0,las=i;
				for (int j=i+1;j<sz;++j){
					if (s[j]<='9' && s[j]>='0')
						cnt=(cnt<<1)+(cnt<<3)+s[j]-'0',las=j;
					else break;
				}
				if (!cnt) cnt=1;
				i=las;
				while (~sta.top().second){
					st.push(sta.top());
					st.top().second*=cnt;
					sta.pop();
				}
				sta.pop();
				while (!st.empty()) sta.push(st.top()),st.pop();
			}else now.push_back(s[i]);
		}
		if (!now.empty()) push_to_sta();
		while (!sta.empty())
			p[sta.top().first]=1,c[tot][sta.top().first]+=sta.top().second,sta.pop();
		int e_cnt=0;
		for (int i=sz+1;i<S;++i)
			if (s[i]<='9' && s[i]>='0')
				e_cnt=(e_cnt<<1)+(e_cnt<<3)+s[i]-'0';
		if (s.back()=='+' || s.back()=='-'){
			if (!e_cnt) e_cnt=1;
			if (s.back()=='-') e_cnt=-e_cnt;
		}
		e[tot]=e_cnt;
		//printf("%d %d\n",tot,e_cnt);
	}
	inline void read(char *s1,char *s2,int l1,int l2){
		for (int i=1;i<=l1;++i){
			if (s1[i]==' '){
				count(stmp);
				stmp=vector<char>();
			}else stmp.push_back(s1[i]);
		}
		if (!stmp.empty()) count(stmp);
		stmp=vector<char>();
		tt=tot;
		for (int i=1;i<=l2;++i){
			if (s2[i]==' '){
				count(stmp);
				stmp=vector<char>();
			}else stmp.push_back(s2[i]);
		}
		if (!stmp.empty()) count(stmp);
		/*for (int i=1;i<=tot;++i){
			it=c[i].begin();
			while (it!=c[i].end()){
				for (int j=0,sz=it->first.size();j<sz;++j)
					printf("%c",it->first[j]);
				printf(" %d\n",it->second);
				it++;
			}
			printf("\n");
		}*/
	}
}
namespace gauss{
	frac a[N][N],x[N];
	inline int calc(int x){
		int res=0;
		if (!x) return 1;
		while (x) ++res,x/=10;
		return res;
	}
	inline void check(){
		for (iter=p.begin();iter!=p.end();++iter){
			frac temp=(frac){0,1};
			for (int i=1;i<=tot;++i)
				if (c[i][iter->first]){
					frac tmp=(frac){(i>tt?-1:1)*c[i][iter->first],1};
					temp=temp+(tmp*x[i]);
				}
			if (temp.x!=0){
				printf("<font color=#FF0000 size=6 >$$Impossible$$</font>\n\n");
				exit(0);
			}
		}
	}
	inline bool chk(int p1,int p2){
		frac k=(frac){0,1};
		for (int i=1;i<=tot;++i)
			if (a[p2][i].x){
				k=a[p1][i]/a[p2][i];
				break;
			}
		for (int i=1;i<=tot;++i)
			if (a[p2][i]*k!=a[p1][i]) return 0;
		return 1;
	}
	inline void init(){
		int cnt=0;
		if (is_ion){
			++cnt;
			for (int i=1;i<=tot;++i)
				a[cnt][i]=(frac){(i>tt?-1:1)*e[i],1};
		}
		for (iter=p.begin();iter!=p.end();++iter){
			++cnt;
			for (int i=1;i<=tot;++i)
				if (c[i][iter->first])
					a[cnt][i]=(frac){(i>tt?-1:1)*c[i][iter->first],1};
				else a[cnt][i]=(frac){0,1};
			bool flag=0;
			for (int i=1;i<cnt;++i){
				flag=1;
				if (!chk(i,cnt)) flag=0;
				if (flag) break;
			}
			if (flag) --cnt;
			if (cnt==tot-1) break;
		}
		for (int i=1;i<=cnt;++i)
			a[i][tot+1]=(frac){0,1};
		a[++cnt][tot+1]=(frac){1,1};
		a[cnt][1]=(frac){1,1};
		for (int i=2;i<=tot;++i) a[cnt][i].y=1;
		/*for (int i=1;i<=tot;++i){
			for (int j=1;j<=tot+1;++j)
				printf("%d/%d ",a[i][j].x,a[i][j].y);
			printf("\n");
		}*/
	}
	inline void gs(int n){
		for (int k=1;k<=n;++k){
			int pos=k;
			for (int i=k+1;i<=n;++i)
				if (abs(a[pos][k])<abs(a[i][k]))
					pos=i;	
			if (pos!=k)
				for (int i=1;i<=n+1;++i)
					swap(a[pos][i],a[k][i]);
			for (int i=k+1;i<=n;++i)
				if (a[i][k].x!=0){
					frac u=a[i][k]/a[k][k];
				//	printf("%d %d\n",u.x,u.y);
					for (int j=k;j<=n+1;++j){
						//printf("%d %d %d %d %d %d %d\n",i,k,j,a[i][j].x,a[i][j].y,a[k][j].x,a[k][j].y);
						a[i][j]=a[i][j]-u*a[k][j];
					}
				}
		}
	}
	inline void solve(){
		init(),gs(tot);
		/*for (int i=1;i<=tot;++i){
			for (int j=1;j<=tot+1;++j)
				printf("%d/%d ",a[i][j].x,a[i][j].y);
			printf("\n");	
		}*/
		for (int i=tot;i;--i){
			frac temp=(frac){0,1};
			for (int j=i+1;j<=tot;++j){
				//printf("%d %d %d %d\n",a[i][j].x,a[i][j].y,x[j].x,x[j].y);
				temp=temp+a[i][j]*x[j];
			}
			x[i]=(a[i][tot+1]-temp)/a[i][i];
			//printf("%d %d\n",x[i].x,x[i].y);
		}
		/*for (int i=1;i<=tot;++i)
			printf("%d/%d\n",x[i].x,x[i].y);*/
		check();
		int k=x[1].y;
		for (int i=2;i<=tot;++i)
			k=k*x[i].y/gcd(k,x[i].y);
		for (int i=1;i<=tot;++i) x[i]=x[i]*k;
		k=0;
		for (int i=1;i<=tot;++i) k=gcd(k,x[i].x);
		printf("$$");
		int print_tot=0;
		for (int i=1;i<=tot;++i){
			if ((x[i].x/k)!=1) printf("%d",x[i].x/k),print_tot+=calc(x[i].x/k);
			for (int j=0,ssz=ss[i].size();j<ssz;++j){
				printf("%c",ss[i][j]);
				if (ss[i][j]!='_' && ss[i][j]!='^' && ss[i][j]!='{' && ss[i][j]!='}')	
					++print_tot;
			}
			if (i==tt) printf("\\xlongequal{\\quad\\quad}"),++print_tot;
			else if (i^tot) printf("+"),++print_tot;	
			if (print_tot>=70){
				printf("$$\n$$");
				print_tot=0;
			}
		}
		printf("{}$$\n\n");
	}
};
int main(){
	freopen("balancer.in","r",stdin);
	freopen("balancer.md","w",stdout);
	is_ion=0;
	cin.getline(s1+1,10000);
	cin.getline(s2+1,10000);
	l1=strlen(s1+1),l2=strlen(s2+1);
	for (int i=1;i<=l1;++i)
		if (s1[i]=='+' || s1[i]=='-'){
			is_ion=1;
			break;
		}
	for (int i=1;i<=l2;++i)
		if (s2[i]=='+' || s2[i]=='-'){
			is_ion=1;
			break;
		}
	if (!is_ion) input::read(s1,s2,l1,l2);
	else input_ion::read(s1,s2,l1,l2);
	gauss::solve();
	return 0;
}
