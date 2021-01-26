#include <iostream>
#include <vector>
#include <list>
using namespace std;
typedef pair<int,int> pii;
int n,m,k;//n:�ٴ� ũ��, m:��� ��, k:��� ���ӽð�
//vector<bool> alive;//����ִ��� Ȯ��
//vector<queue<int>> where;(ť�� ũ��� k)

class shark{
    public:
    bool alive;
    pii now;
    int dir;
    vector<vector<int>> prio;

    shark(int x, int y){
        alive = true;
        now = make_pair(x,y);
        vector<int> a;
        prio.push_back(a);
    }
};
vector<shark> sharks;

pii operator+(const pii &x, const pii &y){
    return make_pair(x.first+y.first, x.second+y.second);
}
void seaShow(const vector<vector<int>> &sea){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<sea[i][j]<<" ";
        }
        cout<<endl;
    }
}
pii dTodir(int d){
    if(d == 1){
        return make_pair(-1,0);
    }
    if(d==2) return make_pair(1,0);
    if(d==3) return make_pair(0,-1);
    return make_pair(0,1);
}


bool findNxt(vector<vector<int>> &sea,pii &now,int me){
    cout<<"FIND NXT ";
    pii nxt;
    int d = sharks[me].dir;
    cout<<me<<"�� ���� : "<<d;
    vector<int> prio = sharks[me].prio[d];
    //0Ȯ�� meȮ��
    for(int x=0;x<2;x++){
        int chk = 0;
        if(x>0) chk = me;
        for(int i=0;i<4;i++){
            nxt = now+dTodir(prio[i]);
            if(nxt.first>=0&&nxt.first<n&&nxt.second>=0&&nxt.second<n){
                if(sea[nxt.first][nxt.second]==chk){
                    now = nxt;
                    sharks[me].dir = prio[i];
                    cout<<"->"<<sharks[me].dir<<" ��÷! "<<chk<<endl;
                    return true;
                }
            }

        } 
    }

    //������,,
    return false;
}

int game(vector<vector<int>> &sea, vector<list<pii>> &smells){
    int cnt = m,tim = 0;
    vector<pii> nxt(m);
    while(cnt>1){
        tim++;
        if(tim >1000) return tim;

        cout<<"*****************"<<tim<<endl;
        seaShow(sea);

        for(int i=1;i<=m;i++){
            if(sharks[i].alive) {
                if(findNxt(sea,nxt[i],i)==false) {//�� ���� ������
                    sharks[i].alive = false;//�׿�
                }
            }
        }
        
        for(int i=1;i<=m;i++){
            if(smells[i].empty()) continue;
            pii del = smells[i].front();//�ð� �������� ����
            list<pii>::iterator iter = smells[i].begin()++;
            bool duplicated = false;
            for(;iter!=smells[i].end();iter++){
                if(del == *iter) duplicated = true;///������� ������ �ߺ��Ǵ��� üũ
            }
            if(!duplicated) sea[del.first][del.second] = 0;//�ٴٿ��� ������ ���� ���ֱ�
            smells[i].pop_front();//�ð� �������� ���� ����
            
            if(sea[nxt[i].first][nxt[i].second]>0){//���ڸ��� �� ������
                sharks[i].alive = false;//�׿�
                cnt--;//��� ���� �ٿ�
            }
            sea[nxt[i].first][nxt[i].second]=i;//�ٴٿ� ��� ��ġ
            smells[i].push_back(nxt[i]);
        }
    }
    return tim;
}

int main(){
    cin>>n>>m>>k;
    vector<int> s(n);
    vector<vector<int>> sea(n,s);
    //����ִ��� Ȯ��
    vector<list<pii>> where(m+1);
    shark a1(-1,-1);
    sharks.push_back(a1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>sea[i][j];
            if(sea[i][j]>0){
                where[sea[i][j]].emplace_back(i,j);
                shark a(i,j);
                sharks.push_back(a);
            }
        }
    }
    int d;
    for(int i=1;i<=m;i++){
        cin>>d;
        sharks[i].dir = d;
    }
    vector<int> temp(4);
    for(int i=1;i<=m;i++){
        for(int j=0;j<4;j++){
            cin>>temp[0]>>temp[1]>>temp[2]>>temp[3];
            sharks[i].prio.push_back(temp);
        }
    }

    int tim= game(sea,where);
    if(tim>1000) cout<<-1;
    else cout<<tim;
    return 0;
}