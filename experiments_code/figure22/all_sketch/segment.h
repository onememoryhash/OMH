#ifndef _segment_H
#define _segment_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
//#include "params.h"
#include "BOBHASH32.h"
#define D 16
using namespace std;
class segment
{
    private:
        BOBHash32 * bobhash;
        BOBHash32 *** bf_hash;
        string **out;
        int **Value;
        int **bf;
        int *bit;
        int M,W,Item;
    public:
        int F_in,F_out,Q_in,Q_out,sum,MAX,Q_out2,bf_D,MAXI,False;
        segment(int x):W(x/D),M(x*15/int(15*log(2))) // 15 bits for every item
        {
            False=0;
            bf_D=int(15*log(2));
            bf_hash = new BOBHash32 ** [D];
            for (int i=0; i<D; i++) bf_hash[i] = new BOBHash32 * [bf_D];
            out = new string * [D];
            for (int i=0; i<D; i++) out[i] = new string [W];
            Value = new int * [D];
            for (int i=0; i<D; i++) Value[i] = new int [W];
            bf = new int * [D];
            for (int i=0; i<D; i++) bf[i] = new int [M];
            bit = new int [W];

            F_in=F_out=Q_in=Q_out=sum=Q_out2=MAX=0;
            bobhash = new BOBHash32(1000);
            for (int i=0; i<D; i++) for (int j=0; j<bf_D; j++) bf_hash[i][j] = new BOBHash32(1000-i*4-j-1);
            for (int i=0; i<D; i++) for (int j=0; j<M; j++) bf[i][j]=0;
        }
        int cal(int x,string s)
        {
            int sum=0;
            for (int i=0; i<bf_D; i++)
            {
                F_in++;
                int p=bf_hash[x][i]->run(s.c_str(),s.size()) % M;
                if (bf[x][p]==0) sum++;
            }
            return sum;
        }
        void work(int x,string s)
        {
            for (int i=0; i<bf_D; i++)
            {
                int p=bf_hash[x][i]->run(s.c_str(),s.size()) % M;
                bf[x][p]++;
            }
        }
        bool Find(int x,string s)
        {
            for (int i=0; i<bf_D; i++)
            {
                Q_in++;
                int p=bf_hash[x][i]->run(s.c_str(),s.size()) % M;
                if (!bf[x][p]) return false;
            }
            return true;
        }
        void Insert(string s,int V)
        {
            Item++;
            int p=bobhash->run(s.c_str(),s.size()) % W;
            int tot=0; while (bit[p]==(1<<D)-1) {tot++; F_in++; if (tot>=500/D) break; p++; if (p==W) p=0;}
            if (tot>=500/D) {False=1; return;} else if (!False) sum++;
            int q=bit[p],MIN=bf_D+2,X=0;
            for (int i=0; i<D; i++) if (!(q&(1<<i))) {int t=cal(i,s); if (t<MIN) {MIN=t; X=i;} }
            work(X,s); q+=(1<<X); bit[p]=q;
            F_out++; out[X][p]=s;
            MAXI=max(MAXI,1);
            Value[X][p]=V;
        }
        int Query(string x)
        {
            int p=bobhash->run(x.c_str(),x.size()) % W; Q_out2=0;
            for (int i=0; i<D; i++)
            if (Find(i,x))
            {
                int tot=0;
                while (bit[p]==(1<<D)-1 && out[i][p]!=x) {tot++; Q_out++; Q_out2++; MAX=max(MAX,Q_out2); if (tot>=500/D) break; p++; if (p==W) p=0;}
                Q_out++; Q_out2++; MAX=max(MAX,Q_out2); if (out[i][p]==x) return Value[i][p];
            }
            return -1;
        }
        void print()
        {
            puts("segment hash & 15bit : ");
            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F_out/(Item+0.0),Q_out/(Item+0.0),MAXI,MAX,sum/(D*W+0.0));
            puts("");
        }
};
#endif
