#ifndef CLIB_H
#define CLIB_H

#include <cstdlib>
#include <ctime>
#include <QString>
#include <vector>
#include <algorithm>
#include <map>
#include <QDebug>

typedef unsigned long long ULL;
typedef long long LL;
typedef unsigned int UINT;

class CLIB
{
private:
    //进行一次米勒罗宾素性测试, 是合数返回true
    static bool Miller_Rabin(UINT a, UINT n, UINT x, UINT t);

public:
    CLIB();

    //随机生成cnt位bit(最多64位)
    static ULL generate_bit(int cnt);

    //把num转化为cnt位的二进制字符串
    static QString num_to_bit(ULL num, int cnt);

    //把num的第cnt位改变, 从0开始
    static ULL change_bit(ULL num, int cnt);

    //从1到num中随机选出cnt个数
    static std::vector<int> select_random_num(int num, int cnt);

    //对比有多少不同的二进制位
    static int cmp_bit(ULL num1, ULL num2);

    //计算a*b % mod
    static ULL multi(ULL a, ULL b, ULL mod);

    //快速幂: 计算pow(a, b) % mod
    static UINT quick_pow(UINT a, UINT b, UINT mod);
    static ULL quick_pow(ULL a, ULL b, ULL mod);

    //求gcd
    static ULL gcd(ULL a, ULL b);

    //扩展欧几里得, 解方程：ax+by=gcd(a,b), 返回gcd(a,b)
    static ULL exgcd(ULL a, ULL b, LL &x, LL &y);

    //求a模mod的逆元
    static UINT inverse(UINT a, UINT mod);

    //判断一个数是否为质数
    static bool is_prime(UINT n);

    //求质数的最小原根
    static UINT prime_primitive_root(UINT prime);

    //生成bit位的质数
    static ULL generate_prime(int bit = 32);

    //把64位二进制写入len字节buf, 默认len = 8, 如果数据不够8字节, 则取低位为有效数据
    static void write_ULL_to_buf(ULL num, char *buf, int len = 8);
    
    //把len字节buf变成64位二进制, 默认len = 8, 如果数据不够8字节, 则取低位为有效数据
    static ULL read_buf_to_ULL(char *buf, int len = 8);
};

#endif // CLIB_H
