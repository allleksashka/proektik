#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  if(scanf("%s", &buff)!=1)
    return NULL;
  return strdup(buff);
}
#if 1 //que
typedef int QueueElementType;
typedef struct Queue
{
  QueueElementType  *Elements;
  int  Front;
  int  Back;
  int  NumElements;
  int  Capacity;
} Queue;
Queue *newQueue();
void   DeleteQueue(Queue *Q);
int    empty(Queue *Q);
int    push(Queue *Q, QueueElementType e);
QueueElementType pop(Queue *Q);

Queue *newQueue()
{
  int N=1024;
  Queue *Q;
  if (N < 1)
  {
    printf("\n**Error in newQueue invalid parameter N (%d)\n\n", N);
    return NULL;
  }
  Q = (Queue *)malloc(sizeof(Queue));
  if (Q == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Elements = (QueueElementType *)malloc(N * sizeof(QueueElementType));
  if (Q->Elements == NULL)
  {
    printf("\n**Error in newQueue: malloc failed to allocate\n\n");
    exit(-1);
  }
  Q->Front = 0;  
  Q->Back = -1;  
  Q->NumElements = 0;
  Q->Capacity = N;
  return Q;
}
void DeleteQueue(Queue *Q)
{
  free(Q->Elements);
  free(Q);
}
int empty(Queue *Q)
{
  return Q->NumElements == 0;
}
int size(Queue *Q)
{
  return Q->NumElements;
}
int push(Queue *Q, QueueElementType e)
{
  if (Q->NumElements == Q->Capacity)  
  {
    int N = 2 * Q->Capacity;
    QueueElementType *newE = (QueueElementType *)malloc(N * sizeof(QueueElementType));
    if (newE == NULL)
    {
      printf("\n**Error in push: malloc failed to allocate\n\n");
      exit(-1);
    }
    int  i = Q->Front;
    int  j = 0;
    int  n;
    for (n = 0; n < Q->NumElements; ++n)
    {
      newE[j] = Q->Elements[i];
      ++j;
      ++i;
      if (i >= Q->Capacity)
        i = 0;
    }
    free(Q->Elements);
    Q->Front = 0;
    Q->Back = j - 1;
    Q->Elements = newE;
    Q->Capacity = N;
  }
  Q->Back++;
  if (Q->Back >= Q->Capacity) 
    Q->Back = 0;
  Q->Elements[Q->Back] = e;  
  Q->NumElements++;
  return 1;  
}
QueueElementType pop(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  Q->Front++;
  if (Q->Front >= Q->Capacity)  
    Q->Front = 0;
  Q->NumElements--;
  return e;
}
QueueElementType front(Queue *Q)
{
  if (empty(Q))  
  {
    printf("\n**Error in pop: Q is empty?!\n\n");
    exit(-1);
  }
  QueueElementType e = Q->Elements[Q->Front];
  return e;
}
#endif
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
#if 1///////////////////////////msi
#include <limits.h>
#include <stdint.h>
#include <string.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdlib.h>
typedef struct HashMap HashMap;
HashMap *newHashMap(void);
int mapHas(HashMap *karta, const char key[]);
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr);
size_t mapSize(const HashMap *karta);
int hashMapIsEmpty(const HashMap *karta);
void hashMapClear(HashMap *karta);
void hashMapDestroy(HashMap *karta);
#endif
void DUMMYfree(const void*pp){
    ;
}
typedef struct HashMapEntry {
  char                *key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;
struct HashMap {
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(HashMap *karta, HashMapEntry **table, size_t capacity) {
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(const char key[]) {
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  if (key == NULL)
    return 0;
  length = strlen(key);
  for (i = 0; i < length; ++i) {
    h = (31 * h) + key[i];
  }
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length) {
  return ha6 & (length - 1);
}
static int isHit(HashMapEntry *e, const char key[], uint32_t ha6) {
  return (e->ha6 == ha6
          && (e->key == key || (key != NULL && strcmp(e->key, key) == 0)));
}
static void copyOrFree( int value, const void **valPtr) {
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
static int updateValue(HashMap *karta, HashMapEntry *e, int newVal, const void **oldValPtr) {
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
HashMap *newHashMap(void ) {
  HashMapEntry **table;
  HashMap       *karta = malloc(sizeof(*karta));
  if (karta == NULL)
    return NULL;
  table = calloc(INITIAL_CAPACITY, sizeof(*karta->table));
  if (table == NULL) {
    free(karta);
    return NULL;
  }
  setTable(karta, table, INITIAL_CAPACITY);
  karta->size = 0;
  return karta;
}
int mapPut(HashMap *karta, const char key[], int value){
  const void**oldValPtr=NULL;
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6) == 0)
      continue;
    return updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(HashMapEntry));
  if (e == NULL)
    return 0;
  if (key != NULL) {
    e->key = strdup(key);
    if (e->key == NULL) {
      free(e);
      return 0;
    }
  }
  if (updateValue(karta, e, value, oldValPtr) == 0) {
    free(e->key);
    free(e);
    return 0;
  }
  e->ha6 = ha6;
  e->next = karta->table[gIndex];
  karta->table[gIndex] = e;
  if (karta->size++ < karta->threshold)
    return 1;
  newCapacity = 2 * karta->capacity;
  if (karta->capacity == MAXIMUM_CAPACITY) {
    karta->threshold = UINT_MAX;
    return 1;
  }
  newTable = calloc(newCapacity, sizeof(*newTable));
  if (newTable == NULL)
    return 0;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      gIndex   = indexFor(e->ha6, newCapacity);
      next    = e->next;
      e->next = newTable[gIndex];
      newTable[gIndex] = e;
    }
  }
  free(karta->table);
  setTable(karta, newTable, newCapacity);
  return 1;
}
int mapGet(HashMap *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return e->value;
  }
  return NULL;
}
int mapHas(HashMap *karta, const char key[]) {
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void hashMapRemove(HashMap *karta, const char key[], const void **valPtr) {
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  HashMapEntry *prev  = karta->table[gIndex];
  HashMapEntry *e     = prev;
  while (e != NULL) {
    HashMapEntry *next = e->next;
    if (isHit(e, key, ha6)) {
      karta->size--;
      if (prev == e)
        karta->table[gIndex] = next;
      else
        prev->next = next;
      break;
    }
    prev = e;
    e    = next;
  }
  if (e == NULL) {
    return;
  }
  free(e->key);
  free(e);
}
size_t mapSize(const HashMap *karta) {
  return karta->size;
}
int hashMapIsEmpty(const HashMap *karta) {
  return (karta->size == 0);
}
void hashMapClear(HashMap *karta) {
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      free(e->key);
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void hashMapDestroy(HashMap *karta) {
  if (karta == NULL)
    return;
  hashMapClear(karta);
  free(karta->table);
  free(karta);
}
#endif

///////////////////////////////
char*word;
int  nodes = 0;
HashMap*words;
bool*commas;
vec  fixed_commas;
vecs text;
vec  dots; // of bool
vec* sides;

void bfs(int node){
    Queue*q=newQueue();
    push(q, node);
    while(!empty(q)){
        int act = front(q); pop(q);
        if(!commas[act]){
            commas[act] = true;
            for(int i = 0; i < sides[act].sz; ++i)
                push(q, sides[act].ptr[i]);
        }
    }
}
int main(){
    words=newHashMap();
    bool first = true;
    while(word=getstr()){
        bool dot   = false,
             comma = false;
        if(word[strlen(word)-1] == ','){
            word[strlen(word)-1]='\0';
            comma = true;
        }
        else if(word[strlen(word)-1] == '.'){
            word[strlen(word)-1]='\0';
            dot = true;
        }
        if(!mapHas(words, word))
            mapPut(words, word, nodes++);
        int index = mapGet(words, word);
        if(comma)
            fixed_commas.ptr = pushback(fixed_commas.ptr, &fixed_commas.sz, index);
        if(first || dots.ptr[dots.sz-1]){
            first = false;
            text.ptr=pushbackS(text.ptr, &text.sz, word);
            dots.ptr=pushback (dots.ptr, &dots.sz, dot);
            continue;
        }
        text.ptr=pushbackS(text.ptr, &text.sz, word);
        dots.ptr=pushback (dots.ptr, &dots.sz, dot);
    }
    sides =calloc(2*nodes+5, sizeof(vec) );
    commas=calloc(2*nodes+5, sizeof(bool));
    for(int i = 1; i < text.sz; ++i){
        int y = mapGet(words, text.ptr[i]  );
        int x = mapGet(words, text.ptr[i-1]);
        if(dots.ptr[i-1])
            continue;
        sides[2*x+1].ptr=pushback(sides[2*x+1].ptr, &sides[2*x+1].sz, 2 * y);
        sides[2*y  ].ptr=pushback(sides[2*y  ].ptr, &sides[2*y  ].sz, 2 * x + 1);
    }
    for(int i = 0; i < fixed_commas.sz; ++i)
        bfs(2 * fixed_commas.ptr[i] + 1);
    for(int i = 0; i < text.sz; ++i){
        printf("%s", text.ptr[i]);
        int index = mapGet(words, text.ptr[i]);
        if(dots.ptr[i])
            printf(".");
        else if(commas[2 * index + 1])
            printf(",");
        if(i + 1 < text.sz)
            printf(" ");
    }
    return 0;
}
