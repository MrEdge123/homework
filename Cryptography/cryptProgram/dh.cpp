#include "dh.h"

DH::DH()
{

}

std::pair<UINT, UINT> DH::generate_PG()
{
    P = CLIB::generate_prime();
    G = CLIB::prime_primitive_root(P);
    return std::pair<UINT, UINT>(P, G);
}

UINT DH::generate_Akey()
{
    Akey = CLIB::generate_bit(32) % (P - 2) + 1;
    return Akey;
}

UINT DH::generate_Bkey()
{
    Bkey = CLIB::generate_bit(32) % (P - 2) + 1;
    return Bkey;
}

UINT DH::send_ga()
{
    B_get_ga = CLIB::quick_pow(G, Akey, P);
    return B_get_ga;
}

UINT DH::send_gb()
{
    A_get_gb = CLIB::quick_pow(G, Bkey, P);
    return A_get_gb;
}

UINT DH::cal_A_share_key()
{
    A_share_key = CLIB::quick_pow(A_get_gb, Akey, P);
    return A_share_key;
}

UINT DH::cal_B_share_key()
{
    B_share_key = CLIB::quick_pow(B_get_ga, Bkey, P);
    return B_share_key;
}
