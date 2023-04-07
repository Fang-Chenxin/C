#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<ctime>
using namespace std;

class person
{
    public:
    deque<int> score;
    float average;
};

int main()
{
    srand((unsigned)time(NULL));
    person a;
    person b;
    person c;
    person d;
    person e;
    vector<person> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);
    v.push_back(d);
    v.push_back(e);
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
        {
            int score = rand()%41+60;
            v[i].score.push_back(score);
        }
        for(int j=0;j<10;j++)
        {
            cout<<v[i].score[j]<<" ";
        }
        sort(v[i].score.begin(),v[i].score.end());
        v[i].score.pop_front();
        v[i].score.pop_back();
        for(int j=0;j<8;j++)
        {
            cout<<v[i].score[j]<<" ";
            v[i].average+=v[i].score[j];
        }
        v[i].average/=8;
        cout<<endl;
        cout<<v[i].average<<endl;
    }

    return 0;
}