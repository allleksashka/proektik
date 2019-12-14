#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int self_u  [10];
int self_r  [10];
int other_u [10];
int other_r [10];
int wait    [10];
int progress[10];

int main(){
    for (int i = 0; i < 10; ++i)
        scanf("%d %d", &self_u[i], &self_r[i]);
    for (int i = 0; i < 10; ++i)
        scanf("%d %d %d", &other_u[i], &other_r[i], &wait[i]);
    for(int i = 0; i < 10; ++i){
        progress[i] = other_r[i] - wait[i];
        if(progress[i] > 0)
           progress[i] %= other_u[i] + other_r[i];
    }
    int tot = 0;
    int t   = 0;
    int j   = 0;
    while(1){
        void run(int delta, bool block_j){
            for(int i = 0; i < 10; ++i){
                progress[i] += delta;
                if (block_j && i == j && progress[i] > other_r[i])
                    progress[i] = other_r[i];
                if (progress[i] > 0)
                    progress[i] %= other_u[i] + other_r[i];
            }
            t += delta;
        }
        if (progress[j] >= other_r[j])
            run(other_u[j] + other_r[j] - progress[j], false);
        run(self_u[j], true);
        if (j == 9) {
            tot += 1;
            if (tot == 3)
                break;
        }
        run(self_r[j], false);
        j += 1;
        j %= 10;
    }
    printf("%d\n", t);
    return 0;
}
