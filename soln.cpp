/*......... your happiness is my motivation ............*/
//Coded by Aman Bharti (ECE 2k18) Nit Patna
#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 1000000007

int d,I,s,v,f;
map<string,int>mp;
map<string,int>mp2;

class street{
    public:
    int b,e;
    string name;
    int l;
    street(int b1,int e1,string name1,int l1){
        b=b1;e=e1;name=name1;l=l1;
    }
};


class car{
    public:
    int p,cost,last=0;
    vector<string>name;
    car(int p1,int cost1,vector<string>sname){
        p=p1;cost=cost1;
        name=sname;
    }
};

bool cmp (car* a,car *b){
    if(a->cost<b->cost)return true;
    return false;
}

vector<street*>st;
vector<car*>cr;
vector<street*>adj[10005];
vector<pair<int,int>>szi;

int cnt=0;
int hs[100005];
vector<pair<int,string>>res[100005];

int32_t main()
{
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

//   assert(freopen("f.txt","r",stdin));
//   assert(freopen("foutput.txt","w",stdout));
    cin>>d>>I>>s>>v>>f;


    for(int i=0;i<s;i++){
        int b,e,l;
        string sname;
        cin>>e>>b>>sname>>l;
        street *str = new street(b,e,sname,l);
        st.push_back(str);
        adj[b].push_back(str);
        mp[sname]=b;
        mp2[sname]=l;
    }

    for(int i=0;i<v;i++){
        int p;
        cin>>p;
        int cost=0;
        vector<string>temp;
        for(int j=0;j<p;j++){
            string t;
            cin>>t;
            cost+=mp[t];
            temp.push_back(t);
        }
        car *necr = new car(p,cost,temp);
        cr.push_back(necr);
    }

    szi.assign(I,{0,0});
    for(int i=0;i<I;i++){
        szi[i].first=adj[i].size();
        szi[i].second=i;
    }
    
    sort(cr.begin(),cr.end(),cmp);

    sort(szi.begin(),szi.end(),greater<>());
    
    for(auto crt:cr){
        for(auto st : crt->name){
            int be = mp[st];
            if(hs[be]==0)cnt++;
            hs[be]=1;
            res[be].push_back({crt->last,st});
            crt->last=crt->last+mp2[st];
        }
    }

    for(int i=0;i<I;i++){
        sort(res[i].begin(),res[i].end());
    }
    
    cout<<cnt<<endl;
    for(int i=0;i<I;i++){
        if(hs[i]==0)continue;
        cout<<i<<endl;
        vector<pair<string,int>>sol2;
        set<string>st1;

        for(int j=0;j<res[i].size();j++){
            int cnt=0;
            string ans = res[i][j].second;
            if(st1.find(ans)!=st1.end())continue;
            st1.insert(ans);
            for(int k=j;k<res[i].size();k++){
                if(res[i][k].second==res[i][j].second){cnt++;}
                else {j=k-1;break;}
                if(k==res[i].size()-1){j=k;}
            }
            sol2.push_back({ans,cnt});
        }

        cout<<st1.size()<<endl;
        for(auto x:sol2){
            cout<<x.first<<" "<<x.second<<endl;
        }
    }



  cerr<<endl<<"Time: "<<(clock() * 1000. / CLOCKS_PER_SEC)<<" ms"<<endl;
  return 0;
}