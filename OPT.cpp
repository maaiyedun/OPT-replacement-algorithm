#include<bits/stdc++.h>
using namespace std;
int main(){
    int cSize,pSize,i,j,k;
	cout<<"Enter the cache Size"<< endl;
	cin>>cSize;

	cout<<"Enter the number of Processes"<< endl;
	cin>>pSize;
    vector<int> p(pSize);

	cout<<"Enter Processes"<< endl;
    for(i=0;i<pSize;i++){
        cin>>p[i];
    }
    vector<vector<int>> a(cSize,vector<int>(pSize,-1));
    map <int, int> mp;
    for(i=0;i<pSize;i++){
        vector<int> op;
        vector<pair<int,int>> c;
        for(auto q: mp){
            c.push_back({q.second,q.first});
        }
        for(int q=i+1;q<pSize;q++){
            for(j=0;j<cSize;j++){
                if(a[j][i]==p[q]){
                    op.push_back(p[q]);
                }
            }
        }
        sort(op.begin(),op.end());
        op.erase(unique(op.begin(),op.end()),op.end());
        bool dontCall=true;
        if(op.size()==cSize){
            dontCall=false;
        }
        sort(c.begin(),c.end());
        bool hasrun=false;
        for(j=0;j<cSize;j++){
            if(a[j][i]==p[i]){
                mp[p[i]]++;
                hasrun=true;
                break;
            }
            if(a[j][i]==-1){
                for(k=i;k<pSize;k++)
                    a[j][k]=p[i];
                mp[p[i]]++;
                hasrun=true;
                break;
            }
        }
        if(j==cSize||hasrun==false){
            for(j=0;j<cSize;j++){
                if(dontCall==true){
                    if(a[j][i]==c[c.size()-1].second){
                        mp.erase(a[j][i]);
                        for(k=i;k<pSize;k++)
                            a[j][k]=p[i];
                        mp[p[i]]++;
                        break;
                    }
                }
                else if(dontCall==false){
                    if(a[j][i]==op[op.size()-1]){
                        mp.erase(a[j][i]);
                        for(k=i;k<pSize;k++)
                            a[j][k]=p[i];
                        mp[p[i]]++;
                        break;
                    }
                }
            }
        }
        for(auto q:mp){
            if(q.first!=p[i]){
                mp[q.first]++;
            }
        }
    }
    int hit=0;
    vector<int> hitv(pSize);
    for(i=1;i<pSize;i++){
        for(j=0;j<cSize;j++){
            if(p[i]==a[j][i-1]){
                hit++;
                hitv[i]=1;
                break;
            }
        }
    }
    cout<<"Process ";
    for(i=0;i<pSize;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
    for(i=0;i<cSize;i++){
        cout<<"Frame "<<i<<" ";
        for(j=0;j<pSize;j++){
            if(a[i][j]==-1)
                cout<<"E ";
                else
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"HIT     ";
    for(i=0;i<hitv.size();i++){
        if(hitv[i]==0)
            cout<<"  ";
        else
        cout<<hitv[i]<<" ";
    }
    cout<<endl;
    cout<<"Hit "<<hit<<endl<<"Page Fault "<<pSize-hit<<endl;
    return 0;
}
