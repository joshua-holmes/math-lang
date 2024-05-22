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

HashMap new_hash_map(int capacity);
int hm_get(HashMap *hm, char *key);
void hm_set(HashMap *hm, char *key, int value);
void hm_free(HashMap hm);
