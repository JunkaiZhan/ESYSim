/******* PowerStone Benchmark *******/

#ifdef STATIC_SIZE
unsigned char poptab[] = {0, 1};
unsigned long src[] = {  0x00005678,0x12340000 };
unsigned long dst[2];
#else
volatile unsigned char poptab[256] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
        4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

volatile unsigned long src[1024] =
{
    0x00005678,0x12340000,0x02040608,0x00000001,
        0x12345678,0x12345678,0x12345678,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x12345678,0x12345678,0x12345678,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x12345678,0x12345678,0x12345678,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x12345678,0x12345678,0x12345678,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x12345678,0x12345678,0x12345678,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x10101010,0x12345678,0x10101010,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x10101010,0x12345678,0x10101010,0x12345678,
        0x00005678,0x12340000,0x02040608,0x00000001,
        0x10101010,0x12345678,0x10101010,0x12345678,
        0
};

volatile unsigned long dst[1024];
#endif

int main()
{
    #ifdef TSIM_DISABLE_CACHE
    /*Now I can disable the caches*/
    #ifdef LEON3_CACHE
    asm("sta %g0, [%g0] 2");
    #else
    asm("sethi %hi(0xfd800000), %g1");
    asm("or %g1,%lo(0xfd800000),%g1");
    asm("sethi %hi(0x80000014), %g2");
    asm("or %g2,%lo(0x80000014),%g2");
    asm("st %g1, [%g2]");
    #endif
    #endif

    volatile unsigned long   *s, *d;
    volatile unsigned long   x;
    volatile int k, t=0;
    int i = 0;

    #ifdef SHORT_BENCH
    for(i = 0; i < 50; i++){
    #else
    for(i = 0; i < 5000; i++){
    #endif
        t = 0;
        for (s = src, d = dst, t = 0 ; *s ; s += 4, d += 4)
        {       x  = s[0] ^ d[0];
        k  = poptab[x & 0xff];
        k += poptab[(x >>  8) & 0xff];
        k += poptab[(x >> 16) & 0xff];
        k += poptab[x >> 24];
        t += k;
        x  = s[1] ^ d[1];
        k = poptab[x & 0xff];
        k += poptab[(x >>  8) & 0xff];
        k += poptab[(x >> 16) & 0xff];
        k += poptab[x >> 24];
        t += k;
        x  = s[2] ^ d[2];
        k  = poptab[x & 0xff];
        k += poptab[(x >>  8) & 0xff];
        k += poptab[(x >> 16) & 0xff];
        k += poptab[x >> 24];
        t += k;
        x  = s[3] ^ d[3];
        k  = poptab[x & 0xff];
        k += poptab[(x >>  8) & 0xff];
        k += poptab[(x >> 16) & 0xff];
        k += poptab[x >> 24];
        t += k;
        }
    }

    return 0;
}
