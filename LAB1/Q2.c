#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//simulates a single coin toss given a target probability p of landing heads
//1:head, 0:tail
int simul(double p) {
    // Generate a random double between 0.0 and 1.0
    double random_val = (double)rand() / RAND_MAX;
    
    // If the random value is strictly less than p, count as head
    if (random_val < p) {
        return 1;
    }
    return 0;
}

/**
 * Runs an experiment with N tosses for a coin with head probability p.
 */
void runexp(const char *coin_type, double target_p, long trials[]) {
    printf(" Experiment: %s Coin (Target P(HEAD) = %.2f)\n", coin_type, target_p);
    printf("%-15s %-15s %-20s\n", "Tosses (N)", "Heads Count", "Empirical P(HEAD)");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        long N = trials[i];
        long heads_count = 0;

        for (long j = 0; j < N; j++) {
            heads_count += simul(target_p);
        }

        double empirical_p = (double)heads_count / N;
        printf("%-15ld %-15ld %-20.5f\n", N, heads_count, empirical_p);
    }
    printf("\n");
}

int main() {
    // seeding the random number generator with current system time
    srand((unsigned int)time(NULL));

    // array of trial counts showing convergence as N increases
    long trials[] = {100, 1000, 10000, 1000000};

    // Fair Coin Experiment (P(HEAD) = 0.5)
    runexp("Fair", 0.50, trials);

    // Biased Coin Experiment (P(HEAD) = 0.70)
    runexp("Biased", 0.70, trials);

    return 0;
}
