#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define ll long long
#define pp pair<ll,ll>
#define ld long double
#define all(a) (a).begin(),(a).end()
#define mk make_pair
#define difine define
#define Yes(q) cout << ((q) ? "Yes" : "No") << endl;
constexpr int inf=1000000000;
constexpr ll INF=2e18;
constexpr ll mod=1000000007;
constexpr ll MOD=998244353;
int dx[4]={1,0,-1,0},dy[4]={0,-1,0,1};
int dx1[8]={0,0,-1,1,1,1,-1,-1},dy1[8]={-1,1,0,0,1,-1,1,-1};

 
// #include <atcoder/all>
// typedef atcoder::modint998244353 mint;
// typedef atcoder::modint1000000007 mint;

ofstream ofs;
ifstream ifs("data.txt");
map<string,vector<pair<ld,ld>>> m;
void input(){
    int n;
    ifs >> n;
    rep(i,n){
        string s;
        ifs >> s;
        rep(j,11){
            ld f,g;
            ifs >> f >> g;
            m[s].push_back({f,g});
        }
    }
}

void output(){
    ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);
    ofs << m.size() << endl;
    for (auto it=m.begin();it!=m.end();it++){
        vector<pair<ld,ld>> a=it->second;
        ofs << it->first << endl;
        rep(i,11){
            ofs << a[i].first << " " << a[i].second << " ";
        }
        ofs << endl;
    }
    cout << "data is saved" << endl;
    ofs.close();
}

//0:SB raise
//1:BB fold
//2:3bet
//3:3bet fold
//4:CB
//5:CB fold
//6:prob
//7:prob fold
//8:CBCB
//9:CBCB fold
//10:hand sum

vector<string> data_name={"SB raise","BB fold","3bet","3bet fold","CB","CB fold","prob","prob fold","CBCB","CBCB fold"};

int main() {
    input();
    while(true){
        cout << "o : データをセーブします" << endl;
        cout << "p [playername] [position(0:SB,1:BB)] : 記録開始" << endl;
        char s;
        cin >> s;
        if (s=='o'){
            output();
        }
        if (s=='p'){
            string u;
            int pos;
            cin >> u >> pos;
            if(m.find(u)==m.end()){
                vector<pair<ld,ld>> temp(11,{0,0});
                m[u]=temp;
            }
            while(true){
                cout << "1:fold 2:check,call 3:bet,raise" << endl;
                cout << "4:ポジション変更 o:データをセーブします e:プレイヤー選択に戻ります" << endl; //うざかったらこの行コメントアウトして

                cout << "hand sum       " << m[u][10].first << endl;
                rep(i,10){
                    if (m[u][i].second==0) continue;
                    cout << data_name[i];
                    rep(j,15-data_name[i].size()) cout << " ";
                    cout << m[u][i].first/m[u][i].second << endl;
                }
                m[u][10].first++;
                if (pos==0){
                    cout << "you are SB" << endl;
                    string k;
                    cin >> k;
                    if (k=="o"){
                        output();
                        continue;
                    }
                    if (k=="4") {
                        pos=1-pos;
                        continue;
                    }
                    if (k=="e") break;
                    if (k[0]=='3'){
                        m[u][1].second+=1;
                        m[u][2].second+=1;
                        if (k[1]=='1'){
                            m[u][1].first+=1;
                        } else if (k[1]=='2'){
                            if (k[3]=='2'){
                                m[u][6].second+=1;
                                if (k[4]=='3') m[u][6].first+=1;
                            } else if (k[3]=='3') {
                                m[u][5].second+=1;
                                if (k[4]=='1') m[u][5].first+=1;
                                else{
                                    if (k[6]=='3'){
                                        m[u][9].second+=1;
                                        if (k[7]=='1') m[u][9].first+=1;
                                    }
                                }
                            }
                        } else {
                            m[u][2].first+=1;
                        }
                    }
                } else {
                    cout << "you are BB" << endl;
                    string k;
                    cin >> k;
                    if (k=="o"){
                        output();
                        continue;
                    }
                    if (k=="4") {
                        pos=1-pos;
                        continue;
                    }
                    if (k=="e") break;
                    m[u][0].second+=1;
                    if (k[0]=='3'){
                        m[u][0].first+=1;
                        if (k[1]=='2'){
                            m[u][4].second+=1;
                            if (k[3]=='2'){
                                if (k[4]=='3'){
                                    m[u][7].second+=1;
                                    if (k[5]=='1') m[u][7].first+=1;
                                }
                            } else if (k[3]=='3') {
                                m[u][4].first+=1;
                                if (k[4]=='2'){
                                    m[u][8].second+=1;
                                    if (k[6]=='3'){
                                        m[u][8].first+=1;
                                    }
                                }
                            }
                        } else if (k[1]=='3') {
                            m[u][3].second+=1;
                            if (k[2]=='1') m[u][3].first+=1;
                        }
                    }
                }
                pos=1-pos;
            }
        }
    }
}