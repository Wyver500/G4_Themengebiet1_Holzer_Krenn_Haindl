#include <stdio.h>

/**
 * prints hello world
 **/
void my_hello_world(){
    printf("hello world!\n");
}

/**
 * sums up two numbers
 * @param a
 * @param b
 * @return a + b
 **/
int my_sum(int a, int b){
    return a+b;
}

/**
 * executes a operation and doubles the result
 * @param a
 * @param b
 * @return 2 * (a ? b)
 **/
int double_sum(int a, int b, int (*operation)(int, int)){
    return operation(a, b) * 2;
}


int main(int argc, char **argv) {
    void (*hello)();
    hello = &my_hello_world;
    hello();
    
    int (*sum)(int, int) = &my_sum;
    int x = 3, y = 5;
    {
        int z = sum(x, y);    
        printf("sum(%d, %d) = %d\n", x, y, z);
    }
    {
        int z = double_sum(x, y, sum);    
        printf("double_sum(%d, %d) = %d\n", x, y, z);
    }
    return 0;
}
