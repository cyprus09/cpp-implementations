#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

// initialise a new hash table item
static ht_item *new_item(const char *k, const char *v)
{
  ht_item *i = malloc(sizeof(ht_item));
  i->key = k;
  i->value = v;
  return i;
}

// initialise a new hash table 
ht_hash_table *new_hash_table()
{
  ht_hash_table *new_table = malloc(sizeof(ht_hash_table));

  new_table->size = 52;
  new_table->count = 0;
  new_table->items = calloc((size_t)new_table->size, sizeof(ht_item));
  return new_table;
}

// delete a hash table item
static void del_ht_item(ht_item *i)
{
  free(i->key);
  free(i->value);
  free(i);
}

// delete a hash table
void del_ht_hash_table(ht_hash_table *ht)
{
  for (int i = 0; i < ht->size; i++)
  {
    ht_item *item = ht->items[i];
    if(item != NULL) {
      del_ht_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

// hashing a hash table item
// formula = ()
int hashItem(const char*s, const int arr, const int m) {
  const int stringLen = strlen(s); 
  long hashValue = 0;
  for(int i = 0; i < stringLen; i++){
    hashValue += (long)pow(arr, stringLen - (i + 1)) * s[i];
    hashValue = hashValue % m;
  }

  return (int)hashValue;
}