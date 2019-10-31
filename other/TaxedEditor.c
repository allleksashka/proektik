#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long   ll;
typedef long double ld;

#if 1 // p_q
#ifndef __HEAP_H_GUARD__
#define __HEAP_H_GUARD__
#define HEAP_STARTING_SIZE 256
struct heap_st;
typedef struct heap_st PriorityQueue;
PriorityQueue* newPriorityQueue(signed(*)(void*, void*));
int   push(PriorityQueue*, void*);
void* top(PriorityQueue*);
void* pop(PriorityQueue*);
void delPriorityQueue(PriorityQueue**, void(*)(void*));
#endif
struct heap_st {
  void** info;
  signed(*compareFunction)(void*, void*);
  unsigned used;
  unsigned currentSize;
};
PriorityQueue* newPriorityQueue(signed(*compareFunction)(void*, void*)) {
  PriorityQueue* newHeap = (PriorityQueue*)malloc(sizeof(PriorityQueue));
  if (newHeap == NULL) {
    return NULL;
  }
  newHeap->info = (void**)malloc(HEAP_STARTING_SIZE * sizeof(void*));
  if (newHeap->info == NULL) {
    free(newHeap);
    return NULL;
  }
  newHeap->used = 0;
  newHeap->currentSize = HEAP_STARTING_SIZE;
  newHeap->compareFunction = compareFunction;
  return newHeap;
}
int  push(PriorityQueue* h, void* data) {
  if (h == NULL) {
    return 0;
  }
  if (h->used == 0) {
    h->info[0] = data;
    h->used = 1;
    return 1;
  }
  if (h->used == h->currentSize) {
    unsigned newSize = h->currentSize * 2;
    void** newIndexes = (void**)realloc(h->info, newSize * sizeof(PriorityQueue));
    if (newIndexes == NULL) {
      return 0;
    }
    h->info = newIndexes;
    h->currentSize = newSize;
  }
  h->info[h->used] = data;
  unsigned index, parentIndex;
  index = h->used;
  do {
    parentIndex = (index - 1) / 2;
    if (h->compareFunction(data, h->info[parentIndex]) > 0) {
      h->info[index] = h->info[parentIndex];
      h->info[parentIndex] = data;
      index = parentIndex;
    }
    else {
      break;
    }
  } while (parentIndex != 0);
  h->used++;
  return 1;
}
void*top(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  return h->info[0];
}
void*pop(PriorityQueue*h) {
  if (h == NULL || h->used == 0) {
    return NULL;
  }
  void* toRet = h->info[0];
  if (h->used == 1) {
    h->info[0] = NULL;
    h->used--;
    return toRet;
  }
  h->used--;
  h->info[0] = h->info[h->used];
  h->info[h->used] = NULL;
  unsigned left, right, current = 0, index;
  do {
    index = current;
    left = (current * 2) + 1;
    right = (current * 2) + 2;
    if (left < h->used && h->compareFunction(h->info[left], h->info[current]) > 0) {
      if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0 &&
        h->compareFunction(h->info[right], h->info[left]) > 0) {
        current = right;
      }
      else {
        current = left;
      }
    }
    else if (right < h->used && h->compareFunction(h->info[right], h->info[current]) > 0) {
      current = right;
    }
    if (current != index) {
      void* swap = h->info[current];
      h->info[current] = h->info[index];
      h->info[index] = swap;
    }
  } while (index != current);
  return toRet;
}
void delPriorityQueue(PriorityQueue** h, void(*freeFunction)(void*)) {
  if (h == NULL || *h == NULL) {
    return;
  }
  if (freeFunction != NULL) {
    unsigned i;
    for (i = 0; i < (*h)->used; ++i) {
      freeFunction((*h)->info[i]);
    }
  }
  free((*h)->info);
  free((*h));
  *h = NULL;
}
int size(PriorityQueue*h) {
  return h->used;
}
bool empty(PriorityQueue*h){
  return h->used==0;
}
#endif

enum{ MAXJOBS = 100000};
typedef struct{
    int length, due;
}job;
int njobs;

job*mkjob(job x){
    job*rv=calloc(1, sizeof(job));
    *rv = x;
    return rv;
}
int compareDue(const void*pa, const void*pb){
    job*j1 = (job*)pa;
    job*j2 = (job*)pb;
    return(j1->due < j2->due)?-1:1;
}
int cmpJ(void*a, void*b){
    job*lhs=(job*)a;
    job*rhs=(job*)b;
    return(lhs->length < rhs->length)?-1:1;
}


int moores(ll speed, job*jobs){
    PriorityQueue*pq = newPriorityQueue(cmpJ);
    ld time = 0.;
    int count = 0;
    while(!empty(pq))
        pop(pq);
    for(int z=0; z<njobs; z++){job j = jobs[z];
        push(pq, mkjob(j));
        time += j.length/(double)speed;
        if (time > j.due && fabs(time-j.due) >= 5e-15){
            job*tq=top(pq); job removeJob = *tq; pop(pq);
            time -= removeJob.length/(double)speed;
            count++;
        }
    }
    return count;
}
int main(){
    int nlate;
    scanf("%d %d", &njobs, &nlate);
    job jobs[njobs];
    double totLength = 0;
    int    maxDue    = 0;
    for(int i=0; i<njobs; i++){
        scanf("%d %d", &jobs[i].length, &jobs[i].due);
        totLength += jobs[i].length;
    }
    qsort(jobs, njobs, sizeof(job), compareDue);
    maxDue = jobs[njobs-1].due;
    ll shigh = totLength/maxDue;
    while(moores(shigh, jobs) > nlate)
        shigh *= 2;
    ll slow = 1.0;
    int chigh = moores(shigh, jobs);
    int clow  = moores(slow , jobs);
    while (shigh - slow > 1){
        ll  smid = (shigh+slow)/2.0;
        int cmid = moores(smid, jobs);
        if (cmid > nlate){
            slow = smid;
            clow = cmid;
        }
        else if (cmid < nlate){
            shigh = smid;
            chigh = cmid;
        }
        else if (clow == nlate){
            slow = smid;
            clow = cmid;
        }
        else{
            shigh = smid;
            chigh = cmid;
        }
    }
    if(moores(slow, jobs) <= nlate)
        printf("%lld\n", slow);
    else
        printf("%lld\n", slow+1);
    return 0;
}
