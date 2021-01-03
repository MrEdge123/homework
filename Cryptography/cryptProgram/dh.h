#ifndef DH_H
#define DH_H

#include "clib.h"

class DH
{
private:
    UINT P, G;
    UINT Akey;
    UINT Bkey;

    UINT A_get_gb;
    UINT B_get_ga;

    UINT A_share_key;
    UINT B_share_key;

public:
    DH();

    //生成(P, G), P为质数, G为模P意义下的生成元
    std::pair<UINT, UINT> generate_PG();

    //A, B自己生成的随机数
    UINT generate_Akey();
    UINT generate_Bkey();

    //A发送g^a % P
    UINT send_ga();

    //B发送g^b % P
    UINT send_gb();

    //A计算共享密钥
    UINT cal_A_share_key();

    //B计算共享密钥
    UINT cal_B_share_key();
};

#endif // DH_H
