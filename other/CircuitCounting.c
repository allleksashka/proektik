#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ base = 402};
enum{ cap = base*base};
int  ii   [cap];
long value[cap];
long count[2][cap];
int  tot;

int main() {
    int n;
    scanf("%d", &n);
    value[0] = cap / 2;
    count[0][0] = 1;
    tot = 1;
    for(int i = 0; i < n; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        long *count_last = count[i & 1];
        long *count_now  = count[(i & 1) ^ 1];
        int delta = x * base + y;
        int old_tot = tot;
        for (int j = 0; j < old_tot; ++j) {
            count_now[j] += count_last[j];
            if (ii[value[j] + delta]) {
                count_now[ii[value[j] + delta]] += count_last[j];
            }
            else if (value[j] + delta == cap / 2) {
                count_now[0] += count_last[j];
            }
            else {
                value[tot] = value[j] + delta;
                count_now[tot] += count_last[j];
                ii[value[tot]] = tot;
                tot += 1;
            }
            count_last[j] = 0;
        }
    }
    printf("%ld\n", (count[n & 1][0] - 1) );
    return 0;
}
