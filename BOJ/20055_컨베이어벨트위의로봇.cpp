#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int up, down,b;
vector<int> durability,robot;
vector<bool> belt;
int robotMove(int n,int k,vector<int> &idx,bool debug = false){//idx:=��ġ ������ �κ��� ������ ����
    int turn = 1;
    up = 0;
    down = n/2-1;
    int cnt = 0;
    for(;;turn++){
        //cout<<turn<<" ";
        //1. ��Ʈ ȸ��
        up=(up+n-1)%n;
        down=(down+n-1)%n;
        if(debug){
            cout<<endl<<"****��Ʈ���ư�******"<<turn<<endl<<"ROBOT"<<endl;
            for(int i=0;i<robot.size();i++){
                cout<<robot[i]<<", ";
            }
            cout<<endl;
            cout<<"dura"<<endl;
            for(int i=0;i<durability.size();i++){
                cout<<durability[i]<<" ";
            }
            cout<<endl;
            cout<<"down : "<<down<<" ";
            cout<<endl<<"idx"<<endl;
            for(int i=0;i<idx.size();i++){
                cout<<idx[i]<<" ";
            }
            cout<<endl;
        }

       //�������� ��ġ�� �η��� ������ ������
        
        if(idx[down]>-1){
            robot[idx[down]]=-1;
            if(durability[down]>0) belt[down] = true;
            idx[down] = -1;
        }
        //2. �κ� �̵�
        if(debug) cout<<"�κ� �̵� ";
        for(int i=0;i<robot.size();i++){
            if(robot[i]<0) continue; 
            if(belt[(robot[i]+1)%n]){//�̵������ϸ�
                //�����ڸ� ������ Ȯ���ϰ� �ö� �� �ִ� �� üũ�ص�
                if(durability[robot[i]]>0) belt[robot[i]] = true;
                idx[robot[i]] = -1;//���� ��ġ ����
                robot[i]=(robot[i]+1)%n;//����ġ                
                durability[robot[i]]--;//������ �϶�
                if(durability[robot[i]]==0) cnt++;//������ 0 ���� Ȯ��
                if(debug)cout<<robot[i]<<"�� ������ �϶�->"<<durability[robot[i]]<<" ";
                if(cnt>=k) return turn;//���� ���� Ȯ��
                if(robot[i]==down){//���������ϴ� ��ġ���
                    robot[i]=-1;//�κ�������
                    if(durability[down]>0) belt[down] = true;
                    //idx[robot[i]] = -1;//��ġ ����
                }
                else {
                    belt[robot[i]] = false;//  
                    idx[robot[i]] = i;//�� ��ġ ������Ʈ      
                }
            }
        }

        //3. �κ� �ø���
        if(belt[up]){//�ö󰡴� ��ġ�� �������� ��������
            if(debug)cout<<up<<"�� �κ� �ø���"<<endl;
            belt[up] = false;
            robot.push_back(up);
            idx[up] = robot.size()-1;
            durability[up]--;
            if(durability[up]==0) cnt++;
        }
        //4. ���Ῡ�� Ȯ��
        if(cnt>=k) return turn;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    int n,k,a;
    cin>>n>>k;
    vector<int> idx;
    for(int i=0;i<2*n;i++){
        cin>>a;
        durability.push_back(a);
        belt.push_back(true);
        idx.push_back(-1);
    }
    
    int ans = robotMove(2*n,k,idx);
    cout<<ans;
    return 0;
}