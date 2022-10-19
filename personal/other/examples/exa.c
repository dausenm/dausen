#include <stdio.h>
#include <string.h>

int main(){
    char str[15] = "penis cock poop";

    char str1[12];

    strcpy(str1, str);

    printf("%s\n", str1);

    return 0;
}