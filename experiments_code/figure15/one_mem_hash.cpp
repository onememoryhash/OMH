#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
//#include "BOBHASH32.h"
#define mix(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

using namespace std;
const unsigned int prime32[1229] = {
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
	127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
	179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
	233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
	283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
	419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
	467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
	547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
	607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
	661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
	739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
	811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
	947, 953, 967, 971, 977, 983, 991, 997,
	1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061,
	1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123,
	1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213,
	1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
	1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361,
	1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439,
	1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493,
	1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571,
	1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627,
	1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721,
	1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789,
	1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877,
	1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973,
	1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029,
	2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111,
	2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203,
	2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273,
	2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347,
	2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411,
	2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503,
	2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593,
	2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677,
	2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729,
	2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801,
	2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887,
	2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969,
	2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061,
	3067, 3079, 3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167,
	3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251,
	3253, 3257, 3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323,
	3329, 3331, 3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391,
	3407, 3413, 3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491,
	3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557,
	3559, 3571, 3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631,
	3637, 3643, 3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709,
	3719, 3727, 3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797,
	3803, 3821, 3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881,
	3889, 3907, 3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947,
	3967, 3989, 4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049,
	4051, 4057, 4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129,
	4133, 4139, 4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219,
	4229, 4231, 4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283,
	4289, 4297, 4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391,
	4397, 4409, 4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481,
	4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561,
	4567, 4583, 4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649,
	4651, 4657, 4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729,
	4733, 4751, 4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813,
	4817, 4831, 4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931,
	4933, 4937, 4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993,
	4999, 5003, 5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077,
	5081, 5087, 5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167,
	5171, 5179, 5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261,
	5273, 5279, 5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351,
	5381, 5387, 5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437,
	5441, 5443, 5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507,
	5519, 5521, 5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591,
	5623, 5639, 5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683,
	5689, 5693, 5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779,
	5783, 5791, 5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849,
	5851, 5857, 5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923,
	5927, 5939, 5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043,
	6047, 6053, 6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121,
	6131, 6133, 6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211,
	6217, 6221, 6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287,
	6299, 6301, 6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359,
	6361, 6367, 6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451,
	6469, 6473, 6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563,
	6569, 6571, 6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659,
	6661, 6673, 6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733,
	6737, 6761, 6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827,
	6829, 6833, 6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907,
	6911, 6917, 6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983,
	6991, 6997, 7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069,
	7079, 7103, 7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187,
	7193, 7207, 7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253,
	7283, 7297, 7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369,
	7393, 7411, 7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487,
	7489, 7499, 7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549,
	7559, 7561, 7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621,
	7639, 7643, 7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703,
	7717, 7723, 7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817,
	7823, 7829, 7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901,
	7907, 7919, 7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009,
	8011, 8017, 8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093,
	8101, 8111, 8117, 8123, 8147, 8161, 8167, 8171, 8179, 8191,
	8209, 8219, 8221, 8231, 8233, 8237, 8243, 8263, 8269, 8273,
	8287, 8291, 8293, 8297, 8311, 8317, 8329, 8353, 8363, 8369,
	8377, 8387, 8389, 8419, 8423, 8429, 8431, 8443, 8447, 8461,
	8467, 8501, 8513, 8521, 8527, 8537, 8539, 8543, 8563, 8573,
	8581, 8597, 8599, 8609, 8623, 8627, 8629, 8641, 8647, 8663,
	8669, 8677, 8681, 8689, 8693, 8699, 8707, 8713, 8719, 8731,
	8737, 8741, 8747, 8753, 8761, 8779, 8783, 8803, 8807, 8819,
	8821, 8831, 8837, 8839, 8849, 8861, 8863, 8867, 8887, 8893,
	8923, 8929, 8933, 8941, 8951, 8963, 8969, 8971, 8999, 9001,
	9007, 9011, 9013, 9029, 9041, 9043, 9049, 9059, 9067, 9091,
	9103, 9109, 9127, 9133, 9137, 9151, 9157, 9161, 9173, 9181,
	9187, 9199, 9203, 9209, 9221, 9227, 9239, 9241, 9257, 9277,
	9281, 9283, 9293, 9311, 9319, 9323, 9337, 9341, 9343, 9349,
	9371, 9377, 9391, 9397, 9403, 9413, 9419, 9421, 9431, 9433,
	9437, 9439, 9461, 9463, 9467, 9473, 9479, 9491, 9497, 9511,
	9521, 9533, 9539, 9547, 9551, 9587, 9601, 9613, 9619, 9623,
	9629, 9631, 9643, 9649, 9661, 9677, 9679, 9689, 9697, 9719,
	9721, 9733, 9739, 9743, 9749, 9767, 9769, 9781, 9787, 9791,
	9803, 9811, 9817, 9829, 9833, 9839, 9851, 9857, 9859, 9871,
	9883, 9887, 9901, 9907, 9923, 9929, 9931, 9941, 9949, 9967,
	9973
};
unsigned int
BOB2(string s, unsigned int initval)
{
    unsigned int len = s.size();
    const char * str = s.c_str();
    initval=prime32[initval];
	//register ub4 a,b,c,len;
	unsigned int a,b,c;
	/* Set up the internal state */
	//len = length;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
	c = initval;         /* the previous hash value */

	/*---------------------------------------- handle most of the key */
	while (len >= 12)
	{
		a += (str[0] +((unsigned int)str[1]<<8) +((unsigned int)str[2]<<16) +((unsigned int)str[3]<<24));
		b += (str[4] +((unsigned int)str[5]<<8) +((unsigned int)str[6]<<16) +((unsigned int)str[7]<<24));
		c += (str[8] +((unsigned int)str[9]<<8) +((unsigned int)str[10]<<16)+((unsigned int)str[11]<<24));
		mix(a,b,c);
		str += 12; len -= 12;
	}

	/*------------------------------------- handle the last 11 bytes */
	c += len;
	switch(len)              /* all the case statements fall through */
	{
		case 11: c+=((unsigned int)str[10]<<24);
		case 10: c+=((unsigned int)str[9]<<16);
		case 9 : c+=((unsigned int)str[8]<<8);
		/* the first byte of c is reserved for the length */
		case 8 : b+=((unsigned int)str[7]<<24);
		case 7 : b+=((unsigned int)str[6]<<16);
		case 6 : b+=((unsigned int)str[5]<<8);
		case 5 : b+=str[4];
		case 4 : a+=((unsigned int)str[3]<<24);
		case 3 : a+=((unsigned int)str[2]<<16);
		case 2 : a+=((unsigned int)str[1]<<8);
		case 1 : a+=str[0];
		/* case 0: nothing left to add */
	}
	mix(a,b,c);
	/*-------------------------------------------- report the result */
	return c;
}

int Insert_IN,Insert_OUT,Insert_OUT1,Insert_OUT2,Insert_OUT3,Insert_OUT4,Insert_OUT5,sum_bucket,sum_Insert,Time_of_hash_fail;

int D;//line num
int e_b,size_stash;//entry per bucket, stash size
int n = 0; // number of strings to be readed in
int half_D, exp_D;
int read_rate;
double rate;

//int M[D+2],f[D+2],t=0;
int *M, *f, t = 0;

string st[140];

int *fp_sum, *FP;  // fp_sum[i] means the number of hash functions for the ith bucket, FP[i] means the length of fingerprint for the ith bucket.

const int gb=2;

struct OUT{vector<string> v; string *S;};
OUT **out;  //out[i][j].v[] stores the link of the jth cell in the ith bucket, while out[i][j].S[] stores the key.

struct IN{unsigned int fp,idx;};
IN ***in; // corresponds to the OUT array

char s[105]; // buffer used in reading strings
string RE[5000005]; // string array storing the data

int failnum = 0;

void init(int argc, char ** argv)
{
	char file[100];
	//sscanf(argv[1], "%s", file); // file name
    freopen("docid600w.dat","r",stdin);
	//sscanf(argv[2], "%d", &D);  // the number of arrays
	//sscanf(argv[3], "%d", &e_b); // the number of cells for every bucket
	//sscanf(argv[4], "%d", &n);  // the number of packets / items
	//sscanf(argv[5], "%d", &read_rate); // the rate of exponential decrease

    D = 8; e_b=6;
    n = 1000000;
    read_rate=102;

	rate = (double)read_rate / 100;
	half_D = D/2, exp_D= (1<<(D/2));
	size_stash = 32;  // stash size is fixed at 32

	M = new int[D+2];
	f = new int[D+2];
	memset(M, 0, sizeof(M));
	memset(f, 0, sizeof(f));

	fp_sum = new int[D+D];
	FP = new int[D+D];
	for(int i=0;i<D/2;i++) // the length of the fingerprint, first D/2 5 + 5, second D/2 7+7
		fp_sum[i] = 64, FP[i] = 63, fp_sum[i+D/2] = 512, FP[i+D/2] = 511, fp_sum[i+D] = 64 , FP[i+D] = 63, fp_sum[i+D+D/2] = 512, FP[i+D+D/2] = 511;

	out = new OUT*[D+1];
	for(int i=0;i<D+1;i++) // the structure of the off-chip tables
        out[i] = new OUT[500000];
	//memset(out,0,sizeof(out));
	for(int i = 0; i<D+1;i++)
		for(int j=0;j<500000;j++)
			out[i][j].S = new string[e_b + 1];

	in  = new IN**[D+1]; // the structure of the on-chip tables
	for(int i=0;i<D+1;i++)
	{
		in[i] = new IN*[500000];
		for(int j=0;j<500000;j++)
			in[i][j] = new IN[e_b+1];
	}

	int sum2=1; int SS=0; // calcuate number of buckets for each sub-table
    for (int i=0; i<D; i++) {SS+=sum2; sum2*=gb;}
    M[D-1]=n*rate/e_b/(SS);
    for (int i=D-2; i>=0; i--) M[i]=gb*M[i+1];

    for (int i=0; i<D; i++) sum_bucket+=M[i]*e_b;
}

bool cal_in(int x,int y,int z)
{
    Insert_IN++;
    if (x%D<half_D)
    {
        int p=out[x%D][y].v.size();
        Insert_OUT1++;
        for (int i=0; i<fp_sum[x]; i++)
        {
            bool FLAG=true;
            for (int j=0; j<p; j++) if (BOB2(out[x][y].S[z],i+500) % FP[x]==BOB2(out[x%D][y].v[j],i+500) % FP[x] && out[x][y].S[z]!=out[x%D][y].v[j]) {FLAG=false; break;}
            if (FLAG) {in[x][y][z].idx=i; in[x][y][z].fp=BOB2(out[x][y].S[z],i+500) % FP[x]; return true;}
        }
    }
    else
    {
        int p[20];
        for (int i=y*exp_D; i<(y+1)*exp_D; i++)
        {
            p[i-y*exp_D]=out[x%D-half_D][i].v.size();
            Insert_OUT2++;
        }
        for (int k=0; k<fp_sum[x]; k++)
        {
            bool FLAG=true;
            for (int i=0; i<exp_D; i++)
              for (int j=0; j<p[i]; j++) if (BOB2(out[x][y].S[z],k+500) % FP[x]==BOB2(out[x%D-half_D][y*exp_D+i].v[j],k+500) % FP[x] && out[x][y].S[z]!=out[x%D-half_D][y*exp_D+i].v[j]) {FLAG=false; break;}
            if (FLAG) {in[x][y][z].idx=k; in[x][y][z].fp=BOB2(out[x][y].S[z],k+500) % FP[x]; return true;}
        }
    }
    return false;
}

int Query(string x,int e_b)
{
    int sum=0;
    for (int j=0; j<half_D; j++)
    {
        f[j]=(BOB2(x,j+500) % M[j]);
        for (int k=0; k<e_b; k++) if (out[j][f[j]].S[k]!="" && BOB2(x,in[j][f[j]][k].idx+500) %FP[j] == in[j][f[j]][k].fp) sum++;
    }
    for (int j=0; j<half_D; j++)
    {
        f[j]>>=half_D;
        for (int k=0; k<e_b; k++) if (out[j+half_D][f[j]].S[k]!="" && BOB2(x,in[j+half_D][f[j]][k].idx+500) %FP[j+half_D] == in[j+half_D][f[j]][k].fp) sum++;
    }
    return sum==1;
}

int main(int argc, char** argv)
{
	init(argc, argv);

    // prepare for the input content
    for (int i=1; i<=n; i++) {scanf("%s",s); for (int j=0; j<strlen(s); j++) RE[i]+=s[j];}

    for (int i=1; i<=n; i++)
    {
        string S=RE[i];
        bool FLAG=false; // whether have found an empty bucket

        // the first half of the buckets
        int X,Y,Z; // the location of the updated data
        bool hash_fail=true;

      //  cout<<i<<endl;
        for (int add=0; add<=failnum; add++)  // additional memory
        {
            for (int j=0; j<half_D; j++)
            {
      //  cout<<j<<endl;
                f[j]=BOB2(S,j+500) % M[j];
                int T=-1;
                if (!FLAG){
                    Insert_OUT3++;
                    for (int k=0; k<e_b; k++){
                        if (out[j+add*D][f[j]].S[k]=="")
                        {
                            out[j+add*D][f[j]].S[k]=S; FLAG=true; hash_fail&=cal_in(j+add*D,f[j],k); T=k;
                            X=j+add*D; Y=f[j]; Z=k; break;
                        } // an empty bucket -> calculate "in"
                    }
                }

                if (!add) {Insert_OUT4++; out[j][f[j]].v.push_back(S);}  // chain
                for (int k=0; k<e_b; k++){
                    if (out[j+add*D][f[j]].S[k]!="" && BOB2(S,in[j+add*D][f[j]][k].idx+500) % FP[j+add*D]==in[j+add*D][f[j]][k].fp && T!=k)
                    {
                        IN tmp=in[j+add*D][f[j]][k];
                        hash_fail&=cal_in(j+add*D,f[j],k);
                        if (!hash_fail) in[j+add*D][f[j]][k]=tmp;
                    }
                    if (out[j+add*D+half_D][f[j]>>half_D].S[k]!="" && BOB2(S,in[j+add*D+half_D][f[j]>>half_D][k].idx+500) % FP[j+add*D+half_D]==in[j+add*D+half_D][f[j]>>half_D][k].fp)
                    {
                        IN tmp=in[j+add*D+half_D][f[j]>>half_D][k];
                        hash_fail&=cal_in(j+add*D+half_D,f[j]>>half_D,k);
                        if (!hash_fail) in[j+add*D+half_D][f[j]>>half_D][k]=tmp;
                    }
                }
            }

            // the second half of the buckets
            if (!FLAG)
            for (int j=0; j<half_D; j++)
            {
                f[j]>>=half_D;
                if (!FLAG) Insert_OUT5++;
                if (!FLAG)
                for (int k=0; k<e_b; k++)
                  if (out[j+add*D+half_D][f[j]].S[k]=="")
                  {
                      out[j+add*D+half_D][f[j]].S[k]=S; FLAG=true;
                      hash_fail&=cal_in(j+add*D+half_D,f[j],k); X=j+add*D+half_D; Y=f[j]; Z=k;
                      break;
                  } // an empty bucket
            }
        }

        //
		if (!FLAG || !hash_fail)
		{
		     for (int j=0; j<half_D; j++)
		     {
                f[j]=BOB2(S,j+500) % M[j];
                out[j][f[j]].v.pop_back();
		     }
		     if (FLAG) out[X][Y].S[Z]="";
		}
        if (!hash_fail) Time_of_hash_fail++;
        if ((!FLAG || !hash_fail) && t<size_stash) {st[t++]=S;} else sum_Insert++;// stash

		if ((!FLAG || !hash_fail) && t==size_stash)
		{
			size_stash*=2;
		    failnum++; // the number of extensions
	    }
        if (i%500000==0) {printf("load : %d\%,  AMA: %.5f\n",i/500000,(double)(Insert_OUT1+Insert_OUT2+Insert_OUT3+Insert_OUT4+Insert_OUT5-Insert_OUT)/500000); Insert_OUT=Insert_OUT1+Insert_OUT2+Insert_OUT3+Insert_OUT4+Insert_OUT5;}
	}
	return 0;
}
