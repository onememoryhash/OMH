#ifndef _Double_H
#define _Double_H

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
class Double
{
    private:
        string *out;
        bool *Find;
        BOBHash32 * bobhash, *bobhash2;
        int *Value;
        int M,Item;

    public:
        int F,Q,sum,Q2,MAX,MAXI,F2,False;
        Double(int M):M(M)
        {
            MAXI=0; False=0;
            out = new string [M+2];
            Find = new bool [M+2];
            Value = new int [M+2];
            F=0; Q=0; sum=0;
            bobhash=new BOBHash32(1000);
            bobhash2=new BOBHash32(1005);
            for (int j=0; j<M; j++) Find[j]=false;
        }
        void Insert(string s,int V)
        {
            Item++; F2=0;
            int p=bobhash->run(s.c_str(),s.size()) % M; F++; int ss=bobhash2->run(s.c_str(),s.size()) % (M-1)+1;
            int tot=0; while (Find[p]) {tot++; if (tot>=500) return; p+=ss; if (p>=M) p-=M; F++; F2++; if (F2>MAXI) MAXI=F2;}
            if (tot>=500) {False=1; return;} else if (!False) sum++;
            Find[p]=true; Value[p]=V; out[p]=s;
        }
        int Query(string x)
        {
            int p=bobhash->run(x.c_str(),x.size()) % M; Q++; Q2=1; MAX=max(MAX,Q2); int ss=bobhash2->run(x.c_str(),x.size()) % (M-1)+1;
            int tot=0; while (Find[p] && out[p]!=x) {tot++; if (tot>=500) return -1; Q2++; MAX=max(MAX,Q2);p+=ss; if (p>=M) p-=M; Q++;}
            if (out[p]==x) return Value[p];
            return -1;
        }
        void print()
        {
            puts("double_hash : ");
            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F/(Item+0.0),Q/(Item+0.0),MAXI,MAX,sum/(M+0.0));
            puts("");
            F=0; Item=0; Q=0; MAXI=0; MAX=0;
        }
};
#endif
