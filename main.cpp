//Piotr Makosiej
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int sum(int a,int b)
{
    if(a==0) return b;
    else if(b==0) return a;
    else if(a==b) return a<<1;
    else return sum((a^b),((a&b)<<1));
}
int subtract(int a,int b)
{
    if(b==0) return a;
    else return subtract((a^b),((~a&b)<<1));
}
void add(string s,int x,int* variable)
{
    int pom=0;
    int p=1<<4;
    if(s.at(x)=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,1))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,2))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,3))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,4))=='1')pom|=p;
    *variable|=(1<<pom);
}
void f(string s,int x,int y,int* variable)
{
    if(sum(x,1)>=s.length())return;
    if(s.at(x)==' ')
    {
        f(s,sum(x,1),y,variable);
        return;
    }
    if(y>sum(x,5)) f(s,sum(x,5),y,variable);
    if(y>sum(x,4)) add(s,x,variable);
}
void Delete(string s,int x,int* variable)
{
    int pom=0;
    int p=1<<4;
    if(s.at(x)=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,1))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,2))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,3))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,4))=='1')pom|=p;
    //cout << pom;
    *variable&=(~(1<<pom));
}
void g(string s,int x,int y,int* variable)
{
    if(sum(x,1)>=s.length())return;
    if(s.at(x)==' ')
    {
        g(s,sum(x,1),y,variable);
        return;
    }
    if(y>sum(x,5)) g(s,sum(x,5),y,variable);
    if(y>sum(x,4)) Delete(s,x,variable);
}



void Emplace(string s,int* variable)
{
    *variable=0;
    f(s,0,s.length(),variable);
}
void Insert(string s,int* variable)
{
    f(s,0,s.length(),variable);
}
void Erase(string s,int* variable)
{
    g(s,0,s.length(),variable);
}
bool Emptiness(int v)
{
    if(v==0)
        return true;
    return false;
}
bool Nonempty(int v)
{
    if(v==0)
        return false;
    return true;
}
void PrintWay(int v,string *s, int x,stringstream*ss)
{
    if(x<0)return;
    int p=1;
    p<<=x;
    int y=p&v;
    if(y==0)
    {
        PrintWay(v,s,subtract(x,1),ss);
        return;
    }
    string s1;
    int pom=1<<4;
    y=pom&x;
    if(y!=0) s1='1';
    else s1='0';
    *ss<<s1;
    pom>>=1;
    y=pom&x;
    if(y!=0) s1='1';
    else s1='0';
    *ss<<s1;
    pom>>=1;
    y=pom&x;
    if(y!=0) s1='1';
    else s1='0';
    *ss<<s1;
    pom>>=1;
    y=pom&x;
    if(y!=0) s1='1';
    else s1='0';
    *ss<<s1;
    pom>>=1;
    y=pom&x;
    if(y!=0) s1='1';
    else s1='0';
    *ss<<s1;
    s1=' ';
    *ss<<s1;
    PrintWay(v,s,subtract(x,1),ss);
}
void Print(int v,string* s)
{
    *s='\0';
    if(Emptiness(v))
    {
        *s="empty";
        return;
    }
    stringstream ss;
    PrintWay(v,s,31,&ss);
    *s=ss.str();
}
int Memberway(string s,int x)
{
    if(s.at(x)==' ')
    {
        return Memberway(s,sum(x,1));
    }
    return x;
}
bool Member(string s,int v)
{
    int x=Memberway(s,0);
    int pom=0;
    int p=1<<4;
    if(s.at(x)=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,1))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,2))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,3))=='1')pom|=p;
    p>>=1;
    if(s.at(sum(x,4))=='1')pom|=p;
    int variable=(1<<pom);
    if((v&variable)!=0)return true;
    return false;
}

bool Disjoint(int v1,int v2)
{
    if((v1&v2)!=0)return false;
    return true;
}
bool Conjunctive(int v1,int v2)
{
    if((v1&v2)!=0)return true;
    return false;
}
bool Equality(int v1,int v2)
{
    if(v1==v2)return true;
    return false;
}
bool Inclusion(int v1,int v2)
{
    if((v1&v2)==v1)return true;
    return false;
}
void Union(int v1,int v2,int* variable)
{
    *variable=(v1|v2);
}
void Intersection(int v1,int v2,int* variable)
{
    *variable=(v1&v2);
}
void Symmetric(int v1,int v2,int *variable)
{
    *variable=((v1|v2)&(~(v1&v2)));
}
void Difference(int v1,int v2,int* variable)
{
    *variable=(v1&(~v2));
}
void Complement(int v1,int* variable)
{
    *variable=(~v1);
}
int counter(int v,int x,int amount)
{
    if(x==32)return amount;
    int p=1;
    p<<=x;
    if((p&v)!=0)amount=sum(amount,1);
    counter(v,sum(x,1),amount);
}
bool compare(int v1,int v2,int x)
{
    int p=1;
    p<<=x;
    if((p&v1)!=(p&v2))
    {
        if((p&v1)!=0)return true;
        return false;
    }
    compare(v1,v2,subtract(x,1));

}
bool LessThen(int v1,int v2)
{
    if(Equality(v1,v2))return false;
    int count1=counter(v1,0,0);
    int count2=counter(v2,0,0);
    if(count2>count1)return true;
    else if(count1>count2) return false;
    return !compare(v1,v2,31);
}
bool LessEqual(int v1,int v2)
{
    if(Equality(v1,v2))return true;
    int count1=counter(v1,0,0);
    int count2=counter(v2,0,0);
    if(count2>count1)return true;
    else if(count1>count2) return false;
    return !compare(v1,v2,31);
}
bool GreatEqual(int v1,int v2)
{
    if(Equality(v1,v2))return true;
    int count1=counter(v1,0,0);
    int count2=counter(v2,0,0);
    if(count2>count1)return false;
    else if(count1>count2) return true;
    return compare(v1,v2,31);
}
bool GreatThen(int v1,int v2)
{
    if(Equality(v1,v2))return false;
    int count1=counter(v1,0,0);
    int count2=counter(v2,0,0);
    if(count2>count1)return false;
    else if(count1>count2) return true;
    return compare(v1,v2,31);
}

int main()
{
    string s="11111 01010 00011 00000        ";
    int * i=new int();
    string * sx=new string();

    int * x1=new int();
    int * x2=new int();
    string s1,s2;
    s1="00001 11111";
    s2="00011 10111";
    Emplace(s1,x1);
    Emplace(s2,x2);
    if(LessThen(*x1,*x2))cout << "x2";
    else cout << "x1";

}
