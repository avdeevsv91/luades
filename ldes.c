/*
 * Based on https://github.com/mirror/busybox/blob/master/libbb/pw_encrypt.c
 */

#include <stdio.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"

#include "pw_encrypt_des.h"

static struct const_des_ctx *des_cctx;
static struct des_ctx *des_ctx;

// Die if we can't allocate and zero size bytes of memory.
void* xzalloc(size_t size)
{
	void *ptr = xmalloc(size);
	memset(ptr, 0, size);
	return ptr;
}

/* my_crypt returns malloc'ed data */
static char *my_crypt(const char *key, const char *salt)
{
	if (!des_cctx)
		des_cctx = const_des_init();
	des_ctx = des_init(des_ctx, des_cctx);
	/* Can return NULL if salt is bad ("" or "<one_char>") */
	return des_crypt(des_ctx, xzalloc(DES_OUT_BUFSIZE), (unsigned char*)key, (unsigned char*)salt);
}

/* So far nobody wants to have it public */
static void my_crypt_cleanup(void)
{
	free(des_cctx);
	free(des_ctx);
	des_cctx = NULL;
	des_ctx = NULL;
}

static int ldes_crypt(lua_State * L)
{
    size_t passwd_length, salt_length;
    const char *passwd = luaL_checklstring(L, 1, &passwd_length);
    const char *salt = luaL_checklstring(L, 2, &salt_length);
    
    char *encrypted;
    encrypted = my_crypt(passwd, salt);
    
    if (!encrypted)
        luaL_error(L, "bad salt");
    
    my_crypt_cleanup();
    
    lua_pushlstring(L, encrypted, 13L);
    
    free(encrypted);
    
    return 1;
}

static const struct luaL_Reg ldeslib[] = {
    { "crypt", ldes_crypt },
    { NULL, NULL },
};

LUALIB_API int luaopen_ldes(lua_State *L)
{
    luaL_newlib(L, ldeslib);
    return 1;
}

