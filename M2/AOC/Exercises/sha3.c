#include "sha3.h"

#define Iota(j) do {				\
    bc[0] = st[j];				\
    bc[1] = st[j + 1];				\
    bc[2] = st[j + 2];				\
    bc[3] = st[j + 3];				\
    bc[4] = st[j + 4];				\
    						\
    st[j    ] ^= (~bc[1]) & bc[2];		\
    st[j + 1] ^= (~bc[2]) & bc[3];		\
    st[j + 2] ^= (~bc[3]) & bc[4];		\
    st[j + 3] ^= (~bc[4]) & bc[0];		\
    st[j + 4] ^= (~bc[0]) & bc[1];		\
  } while (0)

#define RhoPi_iter(i, r, j)			\
  bc[0] = st[j];				\
  st[j] = lrot64(t, r);				\
  t = bc[0];

#define Theta_iter(i)					\
  t = bc[(i + 4) % 5] ^ lrot64(bc[(i + 1) % 5], 1);	\
  							\
  for (u32 j = 0; j < 25; j += 5)			\
    st[j + i] ^= t;

static const u64 rndc[24] = { 0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
			      0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
			      0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
			      0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
			      0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
			      0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
			      0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
			      0x8000000000008080, 0x0000000080000001, 0x8000000080008008 };

void sha3_compress(u64 st[25])
{
  u64 t = 0, bc[5];
  
  for (u32 r = 0; r < 24; r++)
    {
      bc[0] = st[0] ^ st[5] ^ st[10] ^ st[15] ^ st[20];
      bc[1] = st[1] ^ st[6] ^ st[11] ^ st[16] ^ st[21];
      bc[2] = st[2] ^ st[7] ^ st[12] ^ st[17] ^ st[22];
      bc[3] = st[3] ^ st[8] ^ st[13] ^ st[18] ^ st[23];
      bc[4] = st[4] ^ st[9] ^ st[14] ^ st[19] ^ st[24];
      
      Theta_iter(0);
      Theta_iter(1);
      Theta_iter(2);
      Theta_iter(3);
      Theta_iter(4);
      
      t = st[1];
      
      RhoPi_iter(0,   1, 10);
      RhoPi_iter(1,   3,  7);
      RhoPi_iter(2,   6, 11);
      RhoPi_iter(3,  10, 17);
      RhoPi_iter(4,  15, 18);
      RhoPi_iter(5,  21,  3);
      RhoPi_iter(6,  28,  5);
      RhoPi_iter(7,  36, 16);
      RhoPi_iter(8,  45,  8);
      RhoPi_iter(9,  55, 21);
      RhoPi_iter(10,  2, 24);
      RhoPi_iter(11, 14,  4);
      RhoPi_iter(12, 27, 15);
      RhoPi_iter(13, 41, 23);
      RhoPi_iter(14, 56, 19);
      RhoPi_iter(15,  8, 13);
      RhoPi_iter(16, 25, 12);
      RhoPi_iter(17, 43,  2);
      RhoPi_iter(18, 62, 20);
      RhoPi_iter(19, 18, 14);
      RhoPi_iter(20, 39, 22);
      RhoPi_iter(21, 61,  9);
      RhoPi_iter(22, 20,  6);
      RhoPi_iter(23, 44,  1);      
	
      Iota(0);
      Iota(5);
      Iota(10);
      Iota(15);
      Iota(20);
      
      st[0] ^= rndc[r];
    }
}

void sha3_init(sha3_context_t *c, int len)
{
  hash3343_memzero(c->st.b, sizeof(c->st.b));

  c->pt = 0;
  c->mdlen = len;
  c->rsiz = 200 - (len << 1);
}

void sha3_update(sha3_context_t *c, u8 *data, u64 len)
{
  u64 b = len / c->rsiz;
  
  for (u64 i = 0; i < b; i++)
    {
      for (u64 j = 0; j < c->rsiz; j++)
	c->st.b[j] ^= data[i * c->rsiz + j];
      
      sha3_compress(c->st.q);
    }
  
  c->pt = len % c->rsiz;
  for (u64 j = 0; j < c->pt; j++)
    c->st.b[j] ^= data[b * c->rsiz + j];
}

void sha3_fini(sha3_context_t *c, u8 *hash)
{
  c->st.b[c->pt] ^= 0x06;
  c->st.b[c->rsiz - 1] ^= 0x80;
  
  sha3_compress(c->st.q);
  
  hash3343_memcpy(hash, c->st.b, c->mdlen);
}

void sha3_clean(sha3_context_t *ctx)
{
  hash3343_memzero(ctx->st.b, sizeof(ctx->st.b));

  ctx->pt  = 0;
  ctx->rsiz = 0;
  ctx->mdlen = 0;
}

void hash3343_sha3_256(u8 *in, u64 len, u8 *hash)
{
  sha3_context_t ctx;

  sha3_init(&ctx, SHA3_256_HASH_SIZE);
  sha3_update(&ctx, in, len);
  sha3_fini(&ctx, hash);
  
  sha3_clean(&ctx);
}

void hash3343_sha3_512(u8 *in, u64 len, u8 *hash)
{
  sha3_context_t ctx;

  sha3_init(&ctx, SHA3_512_HASH_SIZE);
  sha3_update(&ctx, in, len);
  sha3_fini(&ctx, hash);
  
  sha3_clean(&ctx);
}
