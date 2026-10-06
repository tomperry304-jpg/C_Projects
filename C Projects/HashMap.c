#include "HashMap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//data = key + number

// no input / pointer validation in any of the fuctnio calls doubaly problomatic as some functions make internal function calls

// read only map operation and inputs should accept const inputs to refelct intent

// bad naming convetion shoudl reflect usaage and orogin of vairaibles

// numeric constanct e.g 64 that apear frequently should be changed to varaibles for robustness

// duplicat varaible names "blocks"

// renaming variables at differnt stages bin ->> bucket in functions

// things like size and count should be size_t not int as they canot meaningfully be negative

int Hash_number(char* key) {
	int Hash_n = 0;
	for (int i = 0; key[i] != '\0'; i++) {
		unsigned char letter = key[i];
		Hash_n = (Hash_n * 31 + letter) % 64;

	}
	return Hash_n;
}

typedef struct {
	//char string[128];
	char* string;
	int number;
} Key_Value;


/*typedef struct {
	int capacity;
	int length;
	Key_Value blocks[20];
 } Bin;*/

 typedef struct {
	 int capacity;
	 int length;
	 Key_Value *blocks;
  } Bin;



 struct HashMapStruct {
	 Bin blocks[64];
 };

typedef struct HashMapStruct Hash_Map;

Hash_Map* New_Hash_Map(void) {
	Hash_Map* self = (Hash_Map*) malloc(sizeof(Hash_Map));// no check if malloc returns NULL
//	memset(self, 0, sizeof(Hash_Map));
	for (int i = 0; i < 64; i++) {
		self->blocks[i].capacity = 0;
		self->blocks[i].length = 0;
		self->blocks[i].blocks = NULL;
	}
	return self;
}

void Hash_Map_erase(Hash_Map* self) {
	Hash_Map_annihilation(self);
	free(self);
}

void Hash_Map_Put(Hash_Map* self, char* key, int number) {// no way to report failed allocation problem as it will be assumed to have worked
	int Hash_num = Hash_number(key);
	Bin* bucket = &(self->blocks[Hash_num]);
	if (bucket->capacity == 0) { // capacty check happend before duplicate check therefor the capacity may be incresed before necciacy
		bucket->capacity = 1;
		bucket->blocks = malloc(sizeof(Key_Value));// no check if malloc returns NULL
	}
	else if (bucket->capacity <= bucket->length) {
		bucket->capacity *= 2;// capacity doubled before allocation succeds
		Key_Value* temp = bucket->blocks;
		bucket->blocks = malloc(sizeof (Key_Value) * bucket->capacity);// failiure path corrupts the map (allso multiplication could overfloow beore malloc recives it)
		if (bucket->blocks == NULL) {
			return;
		}
		memcpy(bucket->blocks, temp, sizeof(Key_Value) * bucket->length);
		free(temp);
	}
	for (int i = 0; i < bucket->length; i++) {
		Key_Value* container = &(bucket->blocks[i]);
		if (strcmp(container->string, key) == 0) {
			container->number = number;
			return ;
		}
	}
	Key_Value* KV = &(bucket->blocks[bucket->length]);
	KV->number = number;
	//strcpy(KV->string, key);
	KV->string = malloc(strlen(key)+1);// check for failed malloc allocation the +1 can technicaly overflow but mutch less lightly
	strcpy(KV->string, key);
	bucket->length++;
}

int Hash_Map_Pull(Hash_Map* self, char* key) {
	int Hash_num = Hash_number(key);
	Bin* bucket = &(self->blocks[Hash_num]);
	for (int i = 0; i < bucket->length; i++) {
		Key_Value* container = &(bucket->blocks[i]);
		if (strcmp(container->string, key) == 0) {
			return container->number;
		}
	}
	return -1;
}

int Hash_Map_Sum(Hash_Map* self) {
	int total = 0;
	for (int i = 0; i < 64; i++) {
		Bin* bucket = &(self->blocks[i]);
		for (int j = 0; j < bucket->length; j++) {
			Key_Value* container = &(bucket->blocks[j]);
			total += container->number;// no check for intiger overflow
		}
	}
	return total;
}


int Hash_Map_annihilation(Hash_Map* self) {// int function when it should be a void fucntion (returns nothing)
	for (int i = 0; i < 64; i++) {
		Bin* bucket = &(self->blocks[i]);
		for (int j = 0; j < bucket->length; j++) {
			Key_Value* container = &(bucket->blocks[j]);
			free(container->string);
		}
		free(bucket->blocks);

	}
} // Hash map annihilation frees everything but leaves each bucket containing blocks pointers, old length, old capacity (calling it more than once will lead to undifined behaivour) - therofre always needs to be followed by free sellf and therfore shouldnt be a sepearte function




