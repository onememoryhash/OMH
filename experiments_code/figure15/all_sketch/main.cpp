#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <fstream>
#include <ctime>
#include "cuckoo.h"
#include "linear.h"
#include "Double.h"
#include "chain.h"
#include "d_left.h"
#include "peacock.h"
#include "segment.h"
using namespace std;
string Q[5000005];
int ans[5000005];
int main(int argc, char** argv)
{
	char file[100];
	freopen("docid600w.dat","r",stdin);
	int m = 1000000; int R=102;
	//sscanf(argv[1], "%s", file); // file name
    //freopen(file,"r",stdin);
	//sscanf(argv[2], "%d", &m); // the number of items/packets
	//int R;
	//sscanf(argv[3], "%d", &R); // the ratio of the number of cells to the number of items/packets

    int cnt=0;
    int mm=m*R/100;
    cuckoo *ck; ck=new cuckoo(mm);
    linear * ln; ln=new linear(mm);
    peacock * pc; pc=new peacock(mm);
    segment * sg; sg=new segment(mm);
    Double * db; db=new Double(mm);
    chain * ch; ch=new chain(mm);
    d_left * dl; dl=new d_left(mm);
    while (1)
    {
        string s="";
        getline(cin,s);
        Q[++cnt]=s;
        ck->Insert(s,1);
        ln->Insert(s,1);
        pc->Insert(s,1);
        sg->Insert(s,1);
        db->Insert(s,1);
        ch->Insert(s,1);
        dl->Insert(s,1);
        if (cnt==m) break;
        if (cnt%100000==0)
        {
            printf("load: %d\n",cnt/100000);
            ln->print();
            ck->print();
            pc->print();
            sg->print();
            db->print();
            ch->print();
            dl->print();
        }
    }
    return 0;
}
