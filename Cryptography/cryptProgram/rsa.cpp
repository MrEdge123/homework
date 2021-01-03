#include "rsa.h"

RSA::RSA()
{

}

pair<UINT, UINT> RSA::generate_PQ()
{
    P = CLIB::generate_prime(20);
    Q = CLIB::generate_prime(20);
    return pair<UINT, UINT>(P, Q);
}

ULL RSA::calculate_N()
{
    N = (ULL)P * Q;
    return N;
}

ULL RSA::calculate_PHI()
{
    PHI = (ULL)(P - 1) * (Q - 1);
    return PHI;
}

ULL RSA::generate_E()
{
    E = CLIB::generate_bit(20) % PHI;
    while(CLIB::gcd(E, PHI) != 1 && E) E--;
    return E;
}

ULL RSA::generate_D()
{
    //ex+phi*y=1
    //x=d
    LL x, y;
    CLIB::exgcd(E, PHI, x, y);
    D = (x % (LL)PHI + (LL)PHI) % PHI;
    return D;
}

ULL RSA::generate_M()
{
    M = CLIB::generate_bit(64) % N;
    return M;
}

bool RSA::set_M(ULL msg)
{
    if(msg >= N) return false;
    M = msg;
    return true;
}

ULL RSA::encrypt()
{
    C = CLIB::quick_pow(M, E, N);
    return C;
}

ULL RSA::decrypt()
{
    return CLIB::quick_pow(C, D, N);
}
