#include <stdio.h>
int g(int x);

int main()
{
    return !( (g(0)+g(1)+g(2)+g(3))==8);
}