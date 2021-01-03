#ifndef ELGAMAL_H
#define ELGAMAL_H

#include "clib.h"
using namespace std;

class ELGamal
{
private:
    UINT P, G;
    UINT public_key;

    UINT private_key;

    UINT M;
    UINT K;
    UINT U;
    UINT C1, C2;

    UINT V;

public:
    ELGamal();

    /*
     * 密钥生成
    */

    //生成(P, G), P为质数, G为模P意义下的生成元
    pair<UINT, UINT> generate_PG();

    //生成私钥
    UINT gen_private_key();

    //生成公钥
    UINT gen_public_key();

    /*
     * 加密
    */

    //生成一个密文
    UINT generate_M();

    //设置密文
    bool set_M(UINT msg);

    //生成一个整数K
    UINT generate_K();

    //计算U
    UINT calculate_U();

    //加密, 返回(C1, C2)
    pair<UINT, UINT> encrypt();

    /*
     * 解密
    */

    //计算V
    UINT calculate_V();

    //解密得到明文
    UINT decrypt();
};

#endif // ELGAMAL_H
