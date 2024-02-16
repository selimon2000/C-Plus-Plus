#include <stdio.h>
#include <math.h>

void update(int *a,int *b) {
    // Complete this function
    int old_a = *a, old_b = *b;
    
    *a = old_a + old_b;
    *b = abs(old_a - old_b);    
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}