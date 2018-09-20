#ifndef _d_left_H
#define _d_left_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHASH32.h"
#define dl_D 8
using namespace std;
class d_left
{
    private:
        BOBHash32 * bobhash[dl_D];
        vector<string> *out[dl_D];
        vector<int> *Value[dl_D];
        int W,M,M2,Item,F,Q,sum,MAX,False,MAXI,F2,mem;
    public:
        d_left(int m):W(int(m/10.0*8)/8),M(int(m/10.0*2)/8)
        {
            mem=m;
            False=0; MAXI=0;
            for (int i=0; i<dl_D; i++) {out[i]=new vector<string> [W]; Value[i]=new vector<int> [W];}
            for (int i=0; i<dl_D; i++) bobhash[i]=new BOBHash32(1000+i);
            for (int i=0; i<dl_D; i++) for (int j=0; j<W; j++) Value[i][j].clear(),out[i][j].clear();
        }
        void Insert(string s,int V)
        {
            Item++; F2=0;
            int MIN=1000000,X=0;
            for (int i=0; i<dl_D; i++)
            {
                F++; F2++; if (F2>MAXI) MAXI=F2;
                int p=bobhash[i]->run(s.c_str(),s.size()) % W;
                if (out[i][p].size()<MIN) MIN=out[i][p].size(),X=i;
                if (MIN==0) break;
            }
            int p=bobhash[X]->run(s.c_str(),s.size()) % W;
            if (!out[X][p].size())
            {
                out[X][p].push_back(s); Value[X][p].push_back(V);
                if (!False) sum++;
            } else
              if (M2<M)
              {
                  M2++;
                  out[X][p].push_back(s); Value[X][p].push_back(V);
                  if (!False) sum++;
              } else
                False=1;
        }
        int Query(string x)
        {
            int SS=0;
            for (int i=0; i<dl_D; i++)
            {
                int p=bobhash[i]->run(x.c_str(),x.size()) % W;
                if (out[i][p].size()==0) return -1;
                for (int j=0; j<out[i][p].size(); j++)
                  {SS++; Q++; MAX=max(MAX,SS); if (out[i][p][j]==x) return Value[i][p][j];}
            }
            return -1;
        }

        void print()
        {
            puts("d_left_hash : ");

            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F/(Item+0.0),Q/(Item+0.0),MAXI,MAX,sum/(mem+0.0));
            puts("");
            F=0; Item=0; Q=0; MAXI=0; MAX=0;
        }
};
#endif
