#ifndef _chain_H
#define _chain_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include "BOBHASH32.h"
using namespace std;
class chain
{
    private:
        BOBHash32 * bobhash;
        vector<string> *out;
        vector<int> *Value;
        int M,M2,sum,MAX,F,Q,Item,IMAX,False;
    public:
        chain(int x):M(x/2)
        {
            IMAX=0; False=0;
            out = new vector<string> [M];
            Value = new vector<int> [M];
            bobhash=new BOBHash32(1000);
            for (int i=0; i<M; i++) Value[i].clear(),out[i].clear();
        }
        void Insert(string s,int V)
        {
            Item++;
            int p=bobhash->run(s.c_str(),s.size()) % M;
            if (!out[p].size())
            {
                out[p].push_back(s); Value[p].push_back(V);
                if (!False) sum++;
            } else
              if (M2<M)
              {
                  M2++;
                  out[p].push_back(s); Value[p].push_back(V);
                  if (!False) sum++;
              } else False=1;
            F++;
            IMAX=1;
        }
        int Query(string x)
        {
            int p=bobhash->run(x.c_str(),x.size()) % M; int SS=0;
            for (int i=0; i<out[p].size(); i++) {SS++; MAX=max(MAX,SS); Q++; if (out[p][i]==x) return Value[p][i];}
            return -1;
        }
        void print()
        {
            puts("chain_hash : ");
            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F/(Item+0.0),Q/(Item+0.0),IMAX,MAX,sum/(M+M+0.0));
            puts("");
        }
};
#endif
