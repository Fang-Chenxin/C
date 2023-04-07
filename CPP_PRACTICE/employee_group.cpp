#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
using namespace std;


class person
{
public:
    int salary;
    string name;
};

vector<person> v;

// class p_compary(person a,person b)const
// {
// public:
//     operator()(person a,person b)
//     {
//         return a.salary>b.salary;
//     }
// };

void assign_salary()
{
    for(int i=0;i<5;i++)
    {
        person p;
        string seed="12345";
        p.salary = rand()%1000;
        p.name = "员工";
        p.name += seed[i];
        v.push_back(p);
        cout<<"姓名"<<p.name<<"薪水"<<p.salary<<endl;
    }
}

void print_multimap(multimap<string,person> m)
{
    multimap<string,person>::iterator it;
    for(it=m.begin();it!=m.end();it++)
    {
        cout<<it->second.name<<" "<<it->second.salary<<" "<<it->first<<endl;
    }
}

int main()
{
    assign_salary();
    multimap<string,person> m;
    string apartment[4]= {"A","B","C","D"};
    for(int i=0;i<4;i++)
    {
        m.insert(make_pair(apartment[rand()%4],v[i]));
    }
    print_multimap(m);
    return 0;
}