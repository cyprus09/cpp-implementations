#include "hash_table.h"

int main()
{
  ht_hash_table *ht = new_hash_table();
  del_ht_hash_table(ht);
}