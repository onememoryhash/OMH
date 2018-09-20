#ifndef _peacock_H
#define _peacock_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
//#include "params.h"
#include "BOBHASH32.h"
#define pc_D 8
using namespace std;
class peacock
{
    private:
        BOBHash32 * bobhash[pc_D+2];
        string *out[pc_D];
        int *Value[pc_D+2],td;
        bool *sk[pc_D+2];
        bool *in[pc_D+2];
        BOBHash32 * bobhash2[10][6];
        int M,M3,Item,Q_Item;
    public:
        int F_in,Q_in,F_out,Q_out,sum,Q_out2,MAX,MEM,MAXI,False;
        peacock(int x)
        {
            False=0;
            for (M=int(x/1.111111111);;M++) {int sum=0; int MM=M; while (MM) {sum+=MM;MM/=10;} if (sum>x) {MEM=sum; break;}}
            for (M3=int(x*15/0.111111111);;M3++) {int sum=0; int MM=M3; while (MM) {sum+=MM;MM/=10;} if (sum-M3>x*15) break;}
            int M2=M;
            for (int i=0; i<pc_D; i++)
            if (M2)
            {
                Value[i] = new int [M2];
                in[i] =new bool [M2];
                out[i] = new string [M2];
                M2/=10;
            }
            M2=M3;
            for (int i=1; i<pc_D; i++)
            if (M2)
            {
                sk[i] = new bool [M2];
                M2/=10;
            }
            F_in=Q_in=F_out=Q_out=sum=Q_out2=MAX=0;
            for (int i=0; i<pc_D; i++) bobhash[i]=new BOBHash32(1000+i);
            for (int i=0; i<pc_D; i++) for (int j=0; j<4; j++) bobhash2[i][j]=new BOBHash32(1000-i*4-j-1);
        }
        void Ins(string s,int d)
        {
            F_in+=4;
            int MM=M3;
            for (int i=1; i<d; i++) MM/=10;
            for (int i=0; i<4; i++)
            {
                int p=bobhash2[d][i]->run(s.c_str(),s.size()) %MM;
                sk[d][p]++;
            }
        }
        bool Find(string s,int d)
        {
            int MM=M3;
            for (int i=1; i<d; i++) MM/=10;
            if (!MM) return true;
            for (int i=0; i<4; i++)
            {
                Q_in++;
                int p=bobhash2[d][i]->run(s.c_str(),s.size()) %MM;
                if (!sk[d][p]) return false;
            }
            return true;
        }
        void Insert(string s,int V)
        {
            Item++;
            int M2=M; int i;
            for (i=0; i<pc_D; i++)
            if (M2)
            {
                int p=bobhash[i]->run(s.c_str(),s.size()) % M2; F_out++; MAXI=max(MAXI,1);
                F_in++; if (!in[i][p]) {in[i][p]=true;  out[i][p]=s; Value[i][p]=V; if (i) Ins(s,i); if (!False) sum++; break;}
                p++; if (p==M2) p=0; F_out++; MAXI=max(MAXI,2);
                F_in++; if (!in[i][p]) {in[i][p]=true; out[i][p]=s; Value[i][p]=V; if (i) Ins(s,i); if (!False) sum++; break;}
                M2/=10;
            }
            if (i==pc_D) False=1;
        }
        int Query(string x)
        {
            Q_Item++;
            int M2=M/10; Q_out2=0;
            for (int i=1; i<pc_D; i++)
            if (M2)
            {
                if (Find(x,i))
                {
                    int p=bobhash[i]->run(x.c_str(),x.size()) % M2;
                    if (!in[i][p]) break;
                    Q_out++; Q_out2++; MAX=max(MAX,Q_out2); if (out[i][p]==x) return Value[i][p];
                    p++; if (p==M2) p=0;
                    if (!in[i][p]) break;
                    Q_out++; Q_out2++; MAX=max(MAX,Q_out2); if (out[i][p]==x) return Value[i][p];
                }
                M2/=10;
            }
            Q_out++; Q_out2++; MAX=max(MAX,Q_out2);
            if (out[0][bobhash[0]->run(x.c_str(),x.size()) % M]==x) return Value[0][bobhash[0]->run(x.c_str(),x.size()) % M];
            Q_out++; Q_out2++; MAX=max(MAX,Q_out2);
            if (out[0][((bobhash[0]->run(x.c_str(),x.size()) % M)+1)%M]==x) return Value[0][((bobhash[0]->run(x.c_str(),x.size()) % M)+1)%M];
            return -1;
        }
        void print()
        {
            puts("peacock_hash & 15bit : ");
            printf("Insertion AMA : %.5f\nQuery AMA : %.5f\nInsertion WCMA : %d\nQuery WCMA : %d\nPLF : %.5f\n",F_out/(Item+0.0),Q_out/(Item+0.0),MAXI,MAX,sum/(MEM+0.0));
            puts("");
            F_out=0; Item=0; Q_out=0; MAXI=0; MAX=0;
        }
};
#endif
