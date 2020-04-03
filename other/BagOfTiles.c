#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


#if 1////////////////mpi
#define mp newpair
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}
#include<stdint.h>
static const size_t INITIAL_CAPACITY = 16;
static const size_t MAXIMUM_CAPACITY = (1U << 31);
static const float  LOAD_FACTOR      = 0.75;
#ifndef HASHMAP_H
#define HASHMAP_H
typedef struct mpi mpi;
mpi*newMap(void);
bool   mapHas(mpi*karta, pair key);
void   mapDel(mpi*karta, pair key);
size_t mapSize(const mpi *karta);
bool   mapEmpty(const mpi *karta);
void   mapClear(mpi *karta);
void   mapDestroy(mpi *karta);
#endif
void DUMMYfree(const void*pp){
  ;
}
typedef struct HashMapEntry{
  pair                 key;
  int                  value;
  struct HashMapEntry *next;
  uint32_t             ha6;
} HashMapEntry;

struct mpi{
  HashMapEntry **table;
  size_t         capacity;
  size_t         size;
  size_t         threshold;
};
static void setTable(mpi*karta, HashMapEntry**table, size_t capacity){
  karta->table     = table;
  karta->capacity  = capacity;
  karta->threshold = (size_t) (capacity * LOAD_FACTOR);
}
static uint32_t doHash(pair key){
  size_t   length;
  size_t   i;
  uint32_t h = 0;
  h = (31*h) + key.first;
  h = (31*h) + key.second;
  h ^= (h >> 20) ^ (h >> 12);
  return h ^ (h >> 7) ^ (h >> 4);
}
static size_t indexFor(uint32_t ha6, size_t length){
  return ha6 & (length - 1);
}
bool isHit(HashMapEntry *e, pair key, uint32_t ha6){
  return(e->ha6 == ha6
          &&cmpP(e->key, key)==0);
}
static void copyOrFree(int value, const void**valPtr){
  if (valPtr != NULL)
    ;;//*valPtr = value;
}
int updateValue(mpi*karta, HashMapEntry*e, int newVal, const void**oldValPtr){
  copyOrFree( e->value, oldValPtr);
  e->value = newVal;
  return 1;
}
mpi *newMap(){
  HashMapEntry **table;
  mpi       *karta = malloc(sizeof(*karta));
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
int mapPut(mpi*karta, pair key, int value){
  const void**oldValPtr=NULL;
  HashMapEntry  *e;
  size_t         newCapacity;
  HashMapEntry **newTable;
  size_t         i;
  uint32_t ha6  = doHash(key);
  size_t   gIndex = indexFor(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(isHit(e, key, ha6) == 0)
      continue;
    return updateValue(karta, e, value, oldValPtr);
  }
  e = calloc(1, sizeof(HashMapEntry));
  if (e == NULL)
    return 0;
  e->key = (key);
  if (updateValue(karta, e, value, oldValPtr) == 0) {
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
int mapGet(mpi*karta, pair key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for(e = karta->table[gIndex]; e != NULL; e = e->next) {
    if(isHit(e, key, ha6))
      return e->value;
  }
  return 0;
}
bool mapHas(mpi*karta, pair key){
  HashMapEntry *e;
  uint32_t      ha6  = doHash(key);
  size_t        gIndex = indexFor(ha6, karta->capacity);
  for (e = karta->table[gIndex]; e != NULL; e = e->next) {
    if (isHit(e, key, ha6))
      return 1;
  }
  return 0;
}
void mapDel(mpi*karta, pair key){
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
  if (e == NULL)
    return;
  free(e);
}
size_t mapSize(const mpi*karta){
  return karta->size;
}
bool mapEmpty(const mpi*karta){
  return (karta->size == 0);
}
void mapClear(mpi*karta){
  size_t i;
  for (i = 0; i < karta->capacity; ++i) {
    HashMapEntry *e;
    HashMapEntry *next;
    for (e = karta->table[i]; e != NULL; e = next) {
      next = e->next;
      free(e);
    }
    karta->table[i] = NULL;
  }
}
void mapDestroy(mpi*karta){
  if (karta == NULL)
    return;
  mapClear(karta);
  free(karta->table);
  free(karta);
}
void inc(mpi*map, pair off){
  mapPut(map, off, mapGet(map, off)+1);
}
#endif


int kase, M, N, T, arr[35], combo[35][35], ret;
mpi*freq;// map{pair,int}

int main(){
    scanf("%d", &kase);
    combo[0][0] = 1;
    for(int i=1; i<35; i++){
        combo[i][0] = 1;
        for(int j=1; j<35; j++)
            combo[i][j] = combo[i-1][j]+combo[i-1][j-1];
    }
    for(int kk=1; kk<=kase; kk++){
        scanf("%d", &M);
        freq = newMap();
        ret = 0;
        for(int i=0; i<M; i++)
            scanf("%d", &arr[i]);
        scanf("%d %d", &N, &T);
        for(int mask=0; mask<(1<<((M+1)/2)); mask++){
            int sum = 0,
                num = 0;
            for(int i=0; i<(M+1)/2; i++)
                if(mask&(1<<i)){
                    sum += arr[i];
                    num++;
                }
            if(sum <= T && num >= N-(M-(M+1)/2) && num <= N)
               inc(freq, mp(sum, num));
        }
        for(int mask=0; mask<(1<<(M-(M+1)/2)); mask++){
            int sum = 0,
                num = 0;
            for(int i=0; i<M-(M+1)/2; i++)
                if(mask&(1<<i)){
                    sum += arr[i+(M+1)/2];
                    num++;
                }
            if(mapHas(freq, mp(T-sum, N-num)))
                ret += mapGet(freq, mp(T-sum, N-num));
        }
        printf("Game %d -- %d : %d\n", kk, ret, combo[M][N]-ret);
        mapDestroy(freq);
    }
    return 0;
}
