/* This file will contain the main function */
#include <stdio.h>
#include "candidate/candidate.h"

int main(void)
{
    election best;
    int num;
    char code;

    best = create_election();

    for (; ;) {
        printf("Enter code: ");
        scanf(" %c", &code);

        switch(code) {
            case 'a':
                make_candidate(best); break;
            case 'b':
                printf("Enter candidate number: ");
                scanf("%d", &num);
                print_profile(best, num);
                break;
            case 'q': return 0;

            default: printf("what!\n");
                break;
        }
    }
    return 0;
}
