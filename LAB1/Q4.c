#include <stdio.h>
#include <math.h>
long long move_count = 0;//tracking no.of moves
void towers_of_hanoi(int n, char from, char to, char aux, int print) {
    if (n == 1) {
        move++;
        if (print) {
            printf("Move disc 1 from %c to %c\n", from, to);
        }
        return;
    }

    //move top (n-1) discs from s to a
    towers_of_hanoi(n - 1, from, aux, to, print);

    //move the nth disc from s to t
    move++;
    if (print) {
        printf("move disc %d from %c to %c\n", n, from, to);
    }

    //move (n-1) discs from a to t
    towers_of_hanoi(n - 1, aux, to, from, print);
}

int main() {
    printf("                        TOWERS OF HANOI SIMULATION                            \n");
    printf("%-10s | %-20s | %-20s\n", "discs (n)", "simulated moves", "theoretical (2^n - 1)");

    for (int n = 1; n <= 15; n++) {
        move = 0;
        //simulating without printing step-by-step disc moves to keep output clean
        towers_of_hanoi(n, 'A', 'C', 'B', 0);

        long long calcmoves= (1LL << n) - 1; //calculates 2^n - 1
        printf("%-10d | %-20lld | %-20lld\n", n, move, calcmoves);
    }

    printf("========================================================\n");

    return 0;
}
