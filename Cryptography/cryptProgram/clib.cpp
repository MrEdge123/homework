#include "clib.h"

CLIB::CLIB()
{

}

ULL CLIB::generate_bit(int cnt)
{
    ULL ans = 0;
    for(int i = 0; i < cnt; i++) {
        ans = (ans << 1) + rand() % 2;
    }
    return ans;
}

QString CLIB::num_to_bit(ULL num, int cnt)
{
    QString str = QString::number(num, 2);
    while(str.size() < cnt)
        str.prepend('0');
    return str;
}

ULL CLIB::change_bit(ULL num, int cnt)
{
    bool bit = (num >> cnt) & 1;
    if(bit) {
        return num & (~(1ull << cnt));
    }
    else {
        return num | (1ull << cnt);
    }
}

std::vector<int> CLIB::select_random_num(int num, int cnt)
{
    std::vector<int> ans;
    for(int i = 1; i <= num; i++) ans.push_back(i);

    std::random_shuffle(ans.begin(), ans.end());

    while((int)ans.size() > cnt) {
        ans.pop_back();
    }

    return ans;
}

int CLIB::cmp_bit(ULL num1, ULL num2)
{
    ULL num = num1 ^ num2;
    int cnt = 0;
    while(num) {
        if(num & 1) cnt++;
        num >>= 1;
    }
    return cnt;
}

ULL CLIB::multi(ULL a, ULL b, ULL mod)
{
    //2*mod <= ULL_MAX
    a %= mod;
    b %= mod;
    ULL ans = 0;
    while(b) {
        if(b & 1) ans = (ans + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return ans;
}

UINT CLIB::quick_pow(UINT a, UINT b, UINT mod)
{
    ULL ans = 1;
    ULL base = a;
    base %= mod;

    while(b) {
        if(b & 1) ans = ans * base % mod;
        base = base * base % mod;
        b >>= 1;
    }
    return ans;
}

ULL CLIB::quick_pow(ULL a, ULL b, ULL mod)
{
    ULL ans = 1;
    while(b) {
        if(b & 1) ans = multi(ans, a, mod);
        a = multi(a, a, mod);
        b >>= 1;
    }
    return ans;
}

ULL CLIB::gcd(ULL a, ULL b)
{
    return b ? gcd(b, a % b) : a;
}

ULL CLIB::exgcd(ULL a, ULL b, LL &x, LL &y)
{
    if(b == 0) { x = 1; y = 0; return a; }
    ULL d = exgcd(b, a % b, x, y);
    LL t = x;
    x = y; y = t - a / b * y;
    return d;
}

UINT CLIB::inverse(UINT a, UINT mod)
{
    //ax=1(mod m)
    //ax+my=1
    LL x, y;
    UINT GCD = exgcd(a, mod, x, y);
    if(GCD != 1) return 0;
    return (x % mod + mod) % mod;
}

bool CLIB::Miller_Rabin(UINT a, UINT n, UINT x, UINT t)
{
    ULL ans = quick_pow(a, x, n);
    ULL last = ans;
    for(UINT i = 1; i <= t; i++) {
        ans = ans * ans % n;
        if(ans == 1 && last != 1 && last != n-1) return true;  //合数
        last = ans;
    }
    if(ans != 1) return true;
    return false;
}

bool CLIB::is_prime(UINT n)
{
    //Miller_Rabin
    if(n < 2) return false;
    if(n == 2) return true;
    if((n & 1) == 0) return false;
    UINT x = n - 1;
    UINT t = 0;
    while((x & 1) == 0) {
        x >>= 1;
        t++;
    }

    srand(time(0));

    for(int i = 0; i < 10; i++) {
        UINT a = rand() % (n - 1) + 1;
        if(Miller_Rabin(a, n, x, t)) return false;
    }
    return true;
}

UINT CLIB::prime_primitive_root(UINT prime)
{
    if(is_prime(prime) == false) return 0;

    if(prime == 2) {
        return 1;
    }

    std::vector<UINT> factor;
    UINT num = prime - 1;
    for(UINT i = 2; i * i <= num; i++) {
        if(num % i == 0) {
            while(num % i == 0) num /= i;
            factor.push_back(i);
        }
    }

    if(num != 1) factor.push_back(num);

    for(UINT g = 2; g < prime; g++) {
        bool ok = true;
        for(UINT fac : factor) {
            if(quick_pow(g, (prime - 1) / fac, prime) == 1) {
                ok = false;
                break;
            }
        }

        if(ok) return g;
    }

    return 0;
}

ULL CLIB::generate_prime(int bit)
{
    ULL ans = generate_bit(bit);
    while(is_prime(ans) == false) ans++;
    return ans;
}

void CLIB::write_ULL_to_buf(ULL num, char *buf, int len)
{
    for(int i = 0; i < len; i++) {
        buf[len-i-1] = num % (1 << 8);
        num >>= 8;
    }
}

ULL CLIB::read_buf_to_ULL(char *buf, int len)
{
    ULL ans = 0;
    for(int i = 0; i < len; i++) {
        ans <<= 8;
        ans |= (unsigned char)buf[i];
    }
    return ans;
}
