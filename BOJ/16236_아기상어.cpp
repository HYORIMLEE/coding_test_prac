while(!ť.empty){
    ���� = q.pop
    for(���¿���){
        ũ -> ����
        ��||�� -> ť.push
        ��-> priority ť.push ==>ť.pushXXX
    }
}
����ĭ �̵�
//����

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<vector<bool>> vvb;
int n,s_size = 2,cnt=0;
int now[2];//������ġ
int w[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};//���캼 ����
int time = 0;
void eatFish(vvi &sea){
    if(cnt==s_size&&s_size<8){
        cnt=0;
        s_size++;
    }
    vector<bool> t_b(n,false);
    vvb chk(n,t_b);
    vector<int> t_i(n,-1);
    vvi dis(n,t_i);
    chk[now[0]][now[1]] = true;
    dis[now[0]][now[1]] = 0;
    queue<pair<int,int>> q;
    priority_queue<pair<int,int>> fish;
    q.push(make_pair(now[0],now[1]));
    //cout<<"BRAND NEW ";
    int nxt[2],found_dis;
    bool found = false;
    while(q.size()>0){
        pair<int,int> t = q.front();
        //cout<<t.first<<","<<t.second<<endl;
        q.pop();
        for(int i=0;i<4;i++){
            //cout<<i<<"_____"<<q.s_size();
            nxt[0] =t.first+w[i][0];
            if(nxt[0]<0||nxt[0]>=n) continue;
            nxt[1] =t.second+w[i][1];
            if(nxt[1]<0||nxt[1]>=n) continue;
            if(chk[nxt[0]][nxt[1]] == true) continue;

            chk[nxt[0]][nxt[1]] = true;
            int kan = sea[nxt[0]][nxt[1]];
            if(kan>s_size) continue;
            else if(kan==0||kan==s_size) {
                if(!found) q.push(make_pair(nxt[0],nxt[1]));
                dis[nxt[0]][nxt[1]] = dis[t.first][t.second]+1;
            }
            else {//kan<s_size ������ ������, ť���ִ� �Ÿ� �� ���� �� �߿� ���� ���� �ִ� ��, �״��� ������ �� ����
                if(found&&(found_dis!=dis[t.first][t.second]+1)) continue; 
                else if(!found) found_dis = dis[t.first][t.second]+1;
                found = true;
                fish.push(make_pair(-nxt[0],-nxt[1]));
            }       
        }
    }
    if(found) {
        pair<int,int> real = fish.top();
        sea[now[0]][now[1]] = 0;
        time+=found_dis;
        now[0] = -real.first;
        now[1] = -real.second;
        sea[now[0]][now[1]] = 9;
        cnt++;
        eatFish(sea);
    }
}

int main(){
    cin>>n;
    vector<vector<int>> sea(n);
    int temp;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>temp;
            if(temp == 9){
                now[0] = i;
                now[1] = j;
            }
            sea[i].push_back(temp);
        }
    }
    eatFish(sea);
    cout<<time;
    return 0;
}