#include <stdio.h>
#include <stdlib.h>
#include "./utils.h"

typedef struct KVPair {
  char *key;
  int value;
  struct KVPair *next;
} KVPair;
typedef struct HashMap {
  KVPair **list;
  unsigned int capacity;
  unsigned int length;
} HashMap;

HashMap *new_hash_map(int capacity) {
  HashMap *hm = malloc(sizeof(*hm));
  hm->capacity = capacity;
  hm-> length = 0;
  hm->list = calloc(hm->capacity, sizeof(KVPair*));
  return hm;
}

int basic_hash_str(char *str, int max_value) {
  int hashcode = 0;

  int i = 0;
  while (str[i] != '\0') {
    if (!is_letter(str[i]) && !is_number(str[i])) {
      printf("ERROR: Attempted to hash non-digit non-alphabetic key. This hashing function doesn't support that.");
      exit(1);
    }

    // '0' is the lowest ascii value that this hashing function accepts
    // `num` can never be lower than 1
    int num = str[i] - '0' + 1;
    hashcode += num;

    i++;
  }
  
  return hashcode % max_value;
}

int hm_get(HashMap *hm, char *key) {
  int hashcode = basic_hash_str(key, hm->capacity);
  KVPair *pair;
  for (pair = hm->list[hashcode]; pair; pair = pair->next) {
    if (cmp_str(pair->key, key)) {
      return pair->value;
    }
  }

  // cannot find value
  return 0;
}

void hm_set(HashMap *hm, char *key, int value) {
  int hashcode = basic_hash_str(key, hm->capacity);
  KVPair *pair;
  for (pair = hm->list[hashcode]; pair; pair = pair->next) {
    if (cmp_str(pair->key, key)) {
      // found, update value
      pair->value = value;
      return;
    }
  }

  // not found, setup new pair
  KVPair *new_pair = malloc(sizeof(*new_pair));
  new_pair->key = key;
  new_pair->value = value;
  new_pair->next = hm->list[hashcode];
  hm->list[hashcode] = new_pair;
  hm->length++;

}
