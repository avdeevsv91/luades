#include <stdint.h>
#include <stdlib.h>

#define ALIGN1
#define ALIGN4
#define NOINLINE

#define xmalloc malloc
#define ntohl(x) __builtin_bswap32(x)

static int i64c(int i) {
	i &= 0x3f;
	if (i == 0)
		return '.';
	if (i == 1)
		return '/';
	if (i < 12)
		return ('0' - 2 + i);
	if (i < 38)
		return ('A' - 12 + i);
	return ('a' - 38 + i);
}

#include "pw_encrypt_des.c"

