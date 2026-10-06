#include "HashMap.h"
#include <assert.h>

int main(void) {

	Hash_Map* Map1 = New_Hash_Map();
	Hash_Map_Put(Map1, "fquwgkl", 9999999);
	Hash_Map_Put(Map1, "fquwgkl", 9999998);

	int key = Hash_Map_Pull(Map1, "fquwgkl");
	assert(key == 9999998);

	Hash_Map_erase(Map1);
	return 0;
}


// anilation function - 4 (done ?)
// dynamic string memory - 3 (done ?)
// lazy memory alocation - 1 (done)
// key replacment in bin - 2 (done)