#include <bits/stdc++.h>
#include "BOBHASH32.h"
#define B 4
using namespace std;
string **out;
bool **Find;
BOBHash32 * bobhash[2];
int RR,SS,*st,*st2,**Value,F,M,G1,G2,G3,R,MAX,MAXI,Last,False,G;
string *RE;
bool Ins(string x,int V)
{
    int p[2];
    for (int i=0; i<2; i++)
    {
        F++;
        p[i]=(bobhash[i]->run(x.c_str(),x.size())) % M;
        for (int j=0; j<B; j++)
        if (!Find[p[i]][j] && out[p[i]][j]=="")
        {
            out[p[i]][j]=x;
            Value[p[i]][j]=V;
            return true;
        }
    }
    SS++;
    if (SS>=500) return false;
    for (int i=0; i<2; i++)
    {
        int t[B];
        for (int j=0; j<B; j++) t[j]=j; random_shuffle(t,t+B);
        for (int j=0; j<B; j++)
        if (!Find[p[i]][t[j]])
        {
            Find[p[i]][t[j]]=true;
            st[++RR]=p[i];
            st2[RR]=t[j];
            string T=out[p[i]][t[j]];
            int v=Value[p[i]][t[j]];
            out[p[i]][t[j]]="";
            Value[p[i]][t[j]]=0;
            if (Ins(T,v))
            {
                out[p[i]][t[j]]=x;
                Value[p[i]][t[j]]=V;
                return true;
            }
            out[p[i]][t[j]]=T;
            Value[p[i]][t[j]]=v;
        }
    }
    return false;
}
int Query(string x,int &G)
{
    int p0=(bobhash[0]->run(x.c_str(),x.size())) % M; G++;
    MAX=max(MAX,1);
    for (int i=0; i<B; i++)
    if (out[p0][i]==x) return Value[p0][i];
    int p1=(bobhash[1]->run(x.c_str(),x.size())) % M; G++;
    MAX=max(MAX,2);
    for (int i=0; i<B; i++)
    if (out[p1][i]==x) return Value[p1][i];
    return -1;
}
int main(int agrc, char **argv)
{
    char file[100];
    //sscanf(argv[1], "%s", file);
    freopen("docid600w.dat","r",stdin);
    int m,sum=0,R;
    m=1000000; R=100;
    //sscanf(argv[2], "%d", &m);
    //sscanf(argv[3], "%d", &R);
    int mm=m*R/100; M=mm/B;

    out = new string *[M+2];
    Find = new bool *[M+2];
    st = new int [mm+2]; st2 = new int [mm+2];
    RE = new string [m+2];
    Value = new int *[M+2];
    F=G1=G2=G3=sum=RR=0;
    for (int i=0; i<M; i++)
    {
        out[i] = new string [B];
        Find[i] = new bool [B];
        Value[i] = new int [B];
    }
    for (int i=0; i<2; i++) bobhash[i]=new BOBHash32(1000+i);
    for (int i=0; i<M; i++) for (int j=0; j<B; j++) Find[i][j]=false;
    int SUM=0,Last=0;
    for (int i=1; i<=m; i++)
    {
        string s="";
        getline(cin,s); RE[i]=s;
        SUM++;
        for (int j=1; j<=RR; j++) Find[st[j]][st2[j]]=false;
        RR=0; SS=0;
        if (!Ins(s,SUM)) False=1; else if (!False) sum++; // load rate
        MAXI=max(MAXI,F-Last);
        Last=F;
    }
    for (int i=1; i<=m; i++) Query(RE[i],G);
    puts("BCHT : ");
    printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F/(m+0.0),G/(m+0.0),MAXI,MAX,sum/(mm+0.0));
    return 0;
}
