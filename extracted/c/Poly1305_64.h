/* This file auto-generated by KreMLin! */
#ifndef __Hacl_MAC_H
#define __Hacl_MAC_H


#include "kremlib.h"
#include "testlib.h"

typedef struct {
  uint64_t *x00;
  uint64_t *x01;
}
Hacl_MAC_Poly1305_64_poly1305_state;

void
Hacl_MAC_Poly1305_64_crypto_onetimeauth(
  uint8_t *output,
  uint8_t *input,
  uint64_t len,
  uint8_t *k
);
#endif