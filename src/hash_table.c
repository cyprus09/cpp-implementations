#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

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
    if (item != NULL)
    {
      del_ht_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

// hashing a hash table item
int hash_item(const char *s, const int arr, const int m)
{
  const int stringLen = strlen(s);
  long hashValue = 0;
  for (int i = 0; i < stringLen; i++)
  {
    hashValue += (long)pow(arr, stringLen - (i + 1)) * s[i];
    hashValue = hashValue % m;
  }

  return (int)hashValue;
}

static int get_hash(const char *s, const int num_buckets, const int attempt)
{
  const int hash_a = hashItem(s, HT_PRIME_1, num_buckets);
  const int hash_b = hashItem(s, HT_PRIME_2, num_buckets);

  return (hash_a + (attempt * (hash_b + 1)) % num_buckets);
}

// insert a value into the hash table
void ht_insert(ht_hash_table *ht, const char *key, const char *value)
{
  ht_item *item = new_item(key, value);
  int index = hash_item(ht, ht->size, 0);
  ht_item *curr_item = ht->items[index];

  int i = 1;
  while (curr_item != NULL)
  {
    if (item != &HT_DELETED_ITEM)
    {
      if (strcmp(key, item->key) == 0)
      {
        ht_delete(ht, key);
        ht->items[index] = item;
        return;
      }
    }
    index = get_hash(item->key, ht->size, i);
    curr_item = ht->items[index];
    i++;
  }
  ht->items[index] = item;
  ht->count++;
}

char *ht_search(ht_hash_table *ht, const char *key)
{
  int index = hash_item(key, ht->size, 0);
  ht_item *item = ht->items[index];
  int i = 1;

  while (item != NULL)
  {
    if (item != &HT_DELETED_ITEM)
    {
      if (strcmp(key, item->key) == 0)
      {
        return item->value;
      }
    }
    index = get_hash(item->key, ht->size, i);
    item = ht->items[index];
    i++;
  }

  return NULL;
}

void ht_delete(ht_hash_table *ht, const char *key)
{
  int index = hash_item(key, ht->size, 0);
  ht_item *item = ht->items[index];
  int i = 1;
  while (item != NULL)
  {
    if (item != &HT_DELETED_ITEM)
    {
      if (strcmp(item->key, key) == 0)
      {
        del_ht_item(item);
        ht->items[index] = &HT_DELETED_ITEM;
      }
    }
    index = get_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }
  ht->count--;
}