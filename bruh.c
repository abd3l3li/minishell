#include <unistd.h>
#include <stdio.h>
void print_recursive(void)
{
    int i = 10;
    if(i >= 1)
        print_recursive();
    printf("%d\n",i);
}
int main()
{
    print_recursive();
}