#include "elgamal.h"

ELGamal::ELGamal()
{

}

std::pair<UINT, UINT> ELGamal::generate_PG()
{
    P = CLIB::generate_prime();
    G = CLIB::prime_primitive_root(P);
    return std::pair<UINT, UINT>(P, G);
}

UINT ELGamal::gen_private_key()
{
    private_key = CLIB::generate_bit(32) % (P - 3) + 2;
    return private_key;
}

UINT ELGamal::gen_public_key()
{
    public_key = CLIB::quick_pow(G, private_key, P);
    return public_key;
}

UINT ELGamal::generate_M()
{
    M = CLIB::generate_bit(32) % (P - 1);
    return M;
}

bool ELGamal::set_M(UINT msg)
{
    if(msg >= P) return false;
    M = msg;
    return true;
}

UINT ELGamal::generate_K()
{
    K = CLIB::generate_bit(32) % (P - 3) + 2;
    return K;
}

UINT ELGamal::calculate_U()
{
    U = CLIB::quick_pow(public_key, K, P);
    return U;
}

pair<UINT, UINT> ELGamal::encrypt()
{
    C1 = CLIB::quick_pow(G, K, P);
    C2 = (ULL)U * M % P;
    return pair<UINT, UINT>(C1, C2);
}

UINT ELGamal::calculate_V()
{
    V = CLIB::quick_pow(C1, private_key, P);
    return V;
}

UINT ELGamal::decrypt()
{
    return (ULL)C2 * CLIB::quick_pow(V, P-2, P) % P;
}
