#ifndef RSA_H
#define RSA_H

#include "clib.h"
using namespace std;

class RSA
{
private:
    UINT P, Q;

    ULL N;
    ULL PHI;
    ULL E;
    ULL D;

    ULL M;
    ULL C;

public:
    RSA();

    //随机生成两个素数P, Q
    pair<UINT, UINT> generate_PQ();

    //计算: N=P*Q
    ULL calculate_N();

    //计算: PHI=(P-1)(Q-1)
    ULL calculate_PHI();

    //选取一个E, 1<E<PHI, gcd(E, PHI) = 1
    ULL generate_E();

    //计算D, D为E模PHI意义下的逆元
    ULL generate_D();

    //随机生成明文
    ULL generate_M();

    //设置明文
    bool set_M(ULL msg);

    //加密
    ULL encrypt();

    //解密
    ULL decrypt();
};

#endif // RSA_H
