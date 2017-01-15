#include "kremlib.h"
#include "testlib.h"
#include "NaCl.h"
#include "sodium.h"


#define MESSAGE_LEN 44
#define secretbox_MACBYTES   16
#define CIPHERTEXT_LEN (secretbox_MACBYTES + MESSAGE_LEN)
#define secretbox_NONCEBYTES 24
#define secretbox_KEYBYTES   32
#define box_MACBYTES         16
#define box_PUBLICKEYBYTES   32
#define box_SECRETKEYBYTES   32
#define box_NONCEBYTES       24

uint8_t *msg = (uint8_t*) "testtesttesttesttesttesttesttesttesttesttest";

uint8_t nonce[secretbox_NONCEBYTES] = {
  0x00, 0x01, 0x02, 0x03,
  0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x10, 0x11,
  0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19,
  0x20, 0x21, 0x22, 0x23,
};

uint8_t key[secretbox_KEYBYTES] = {
  0x85, 0xd6, 0xbe, 0x78,
  0x57, 0x55, 0x6d, 0x33,
  0x7f, 0x44, 0x52, 0xfe,
  0x42, 0xd5, 0x06, 0xa8,
  0x01, 0x03, 0x80, 0x8a,
  0xfb, 0x0d, 0xb2, 0xfd,
  0x4a, 0xbf, 0xf6, 0xaf,
  0x41, 0x49, 0xf5, 0x1b
};


uint8_t sk1[secretbox_KEYBYTES] = {
  0x85, 0xd6, 0xbe, 0x78,
  0x57, 0x55, 0x6d, 0x33,
  0x7f, 0x44, 0x52, 0xfe,
  0x42, 0xd5, 0x06, 0xa8,
  0x01, 0x03, 0x80, 0x8a,
  0xfb, 0x0d, 0xb2, 0xfd,
  0x4a, 0xbf, 0xf6, 0xaf,
  0x41, 0x49, 0xf5, 0x1b
};
uint8_t sk2[secretbox_KEYBYTES] = {
  0x85, 0xd6, 0xbe, 0x78,
  0x57, 0x55, 0x6d, 0x33,
  0x7f, 0x44, 0x52, 0xfe,
  0x42, 0xd5, 0x06, 0xa8,
  0x01, 0x03, 0x80, 0x8a,
  0xfb, 0x0d, 0xb2, 0xfd,
  0x4a, 0xbf, 0xf6, 0xaf,
  0x41, 0x49, 0xf5, 0x1c
};

void print_results(char *txt, double t1, unsigned long long d1, int rounds, int plainlen){
  printf("Testing: %s\n", txt);
  printf("Cycles for %d times 2^20 bytes: %llu (%.2fcycles/byte)\n", rounds, d1, (double)d1/plainlen/rounds);
  printf("User time for %d times 2^20 bytes: %f (%fus/byte)\n", rounds, t1/CLOCKS_PER_SEC, (double)t1*1000000/CLOCKS_PER_SEC/plainlen/rounds);
}

#define PLAINLEN (1024*1024)
#define ROUNDS 1000

int32_t test_api()
{
  uint8_t ciphertext[CIPHERTEXT_LEN+16], ciphertext2[CIPHERTEXT_LEN+16],
    mac[16],mac2[16],
    decrypted[MESSAGE_LEN], decrypted2[MESSAGE_LEN],
    pk1[box_PUBLICKEYBYTES], pk2[box_PUBLICKEYBYTES],
    test1[box_PUBLICKEYBYTES], test2[box_PUBLICKEYBYTES],
    basepoint[box_PUBLICKEYBYTES] = {9};
  uint32_t res;
  int i;

  /* Testing the secret box primitives */  
  /* Hacl_SecretBox_crypto_secretbox_detached(ciphertext, mac, msg, MESSAGE_LEN, nonce, key); */
  /* res = crypto_secretbox_open_detached(decrypted, ciphertext, mac, MESSAGE_LEN, nonce, key); */
  Hacl_SecretBox_crypto_secretbox_easy(ciphertext, msg, MESSAGE_LEN, nonce, key);
  res = crypto_secretbox_open_easy(decrypted, ciphertext, MESSAGE_LEN+16, nonce, key);

  printf("SecretBox decryption with libsodium was a %s.\n", res == 0 ? "success" : "failure");
  TestLib_compare_and_print("HACL secretbox", msg, decrypted, MESSAGE_LEN);

  for(i = 0; i < MESSAGE_LEN; i++) decrypted[i] = 0;
  for(i = 0; i < CIPHERTEXT_LEN; i++) ciphertext[i] = 0;
  // Creating public/private key couples
  Hacl_EC_crypto_scalarmult(pk1, basepoint, sk1);
  Hacl_EC_crypto_scalarmult(pk2, basepoint, sk2);

  Hacl_Box_crypto_box_beforenm(test1, pk1, sk2);
  res = crypto_box_beforenm(test2, pk2, sk1);
  TestLib_compare_and_print("HACL beforenm", test1, test2, 32);
  
  /* Testing the box primitives */
  /* i = crypto_box_detached(ciphertext, mac, msg, MESSAGE_LEN, nonce, pk, sk); */
  /* res = Hacl_Box_crypto_box_open_detached(decrypted, ciphertext, mac, MESSAGE_LEN, nonce, pk2, key); */
  i = crypto_box_easy(ciphertext, msg, MESSAGE_LEN, nonce, pk1, sk2);
  res = Hacl_Box_crypto_box_open_easy(decrypted, ciphertext, MESSAGE_LEN+16, nonce, pk2, sk1);
  printf("Box decryption with libsodium was a %s.\n", res == 0 ? "success" : "failure");
  
  TestLib_compare_and_print("Box", msg, decrypted, MESSAGE_LEN);
}

int32_t perf_api() {
  return exit_success;
}

int32_t main()
{
  if (sodium_init() == -1) {
    printf("libsodium not installed? sodium_init failed\n");
    exit(EXIT_FAILURE);
  }
  int32_t res = test_api();
  if (res == exit_success) {
    res = perf_api();
  }
  return res;
}
  