#ifndef _cuckoo_H
#define _cuckoo_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
//#include "params.h"
#include "BOBHASH32.h"
using namespace std;
class cuckoo
{
    private:
        string *out;
        bool *Find;
        BOBHash32 * bobhash[2];
        int R,SS,*st,*Value,Item,MAX;

    public:
        int F,G,sum,M,MAXI,F2,False;
        cuckoo(int M):M(M)
        {
            MAXI=0; False=0;
            out = new string [M+2];
            Find = new bool [M+2];
            st = new int [M+2];
            Value = new int [M+2];
            F=G=sum=0;
            for (int i=0; i<2; i++) bobhash[i]=new BOBHash32(1000+i);
            for (int j=0; j<M; j++) Find[j]=false;
            R=0;
        }
        bool Ins(string x,int V)
        {
            int p[2];
            for (int i=0; i<2; i++)
            {
                F++; F2++; if (F2>MAXI) MAXI=F2;
                p[i]=(bobhash[i]->run(x.c_str(),x.size())) % M;
                if (!Find[p[i]] && out[p[i]]=="") {out[p[i]]=x; Value[p[i]]=V; return true;}
            }
            SS++;
            if (SS>=500) return false;
            for (int i=0; i<2; i++)
            if (!Find[p[i]])
            {
                Find[p[i]]=true; st[++R]=p[i];
                string t=out[p[i]]; int v=Value[p[i]];
                out[p[i]]=""; Value[p[i]]=0;
                if (Ins(t,v)) {out[p[i]]=x; Value[p[i]]=V; return true;}
                out[p[i]]=t; Value[p[i]]=v;
            }
            return false;
        }
        void Insert(string s,int V)
        {
            Item++; F2=0;
            for (int j=1; j<=R; j++) Find[st[j]]=false; R=0; SS=0;
            if (!Ins(s,V)) False=1; else if (!False) sum++; // puts("cuckoo : Insert failed");
        }
        int Query(string x)
        {
            int p0=(bobhash[0]->run(x.c_str(),x.size())) % M; G++;
            MAX=max(MAX,1);
            if (out[p0]==x) return Value[p0];
            int p1=(bobhash[1]->run(x.c_str(),x.size())) % M; G++;
            MAX=max(MAX,2);
            if (out[p1]==x) return Value[p1];
            return -1;
        }
        void print()
        {
            puts("cuckoo_hash : ");
            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F/(Item+0.0),G/(Item+0.0),MAXI,MAX,sum/(M+0.0));
            puts("");
        }
};
#endif
