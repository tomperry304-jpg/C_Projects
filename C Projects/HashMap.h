
struct HashMapStruct;

typedef struct HashMapStruct Hash_Map;

Hash_Map* New_Hash_Map(void);
void Hash_Map_erase(Hash_Map* self);
void Hash_Map_Put(Hash_Map* self, char* key, int number);
int Hash_Map_Pull(Hash_Map* self, char* key);
int Hash_Map_Sum(Hash_Map* self);

