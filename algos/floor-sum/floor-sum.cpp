__int128 floor_sum(__int128 n, __int128 m, __int128 a, __int128 b) ///sum(floor(a*i+b)/m) i=0...n-1
{
    __int128 ret = 0;
    if (a >= m)
    {
        ret += ((__int128)n - 1) * n / 2 * (a / m);
        a %= m;
    }
    if (b >= m)
    {
        ret += (__int128)(n) * (b / m);
        b %= m;
    }
    __int128 c = (__int128)(a) * n + b;
    if (c < m)
    {
        return ret;
    }
    return ret + floor_sum(c / m, a, m, c % m);
}
