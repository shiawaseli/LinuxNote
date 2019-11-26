#include <stdio.h>

extern int fee_count, fie_count, foe_count, fum_count;
extern int yylex(void);

int main(int argc, char* argv[])
{
    yylex();
    printf("fee_count = %d \nfie_count = %d \nfoe_count = %d \nfum_count = %d \n",  
            fee_count, fie_count, foe_count, fum_count);
    return 0;
}
