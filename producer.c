#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

int empty = BUFFER_SIZE; // number of empty slots
int full = 0;            // number of filled slots
int mutex = 1;           // mutual exclusion

int main()
{
    int item;
    int i;

    srand(time(NULL));

    for(i = 1; i <= 10; i++)
    {
        // PRODUCER
        item = rand() % 9 + 1;   // random number from 1–9

        if(empty > 0 && mutex == 1)
        {
            mutex = 0; // lock

            buffer[in] = item;
            printf("Produced: %d\n", item);

            in = (in + 1) % BUFFER_SIZE;

            mutex = 1; // unlock
            empty--;
            full++;
        }

        // CONSUMER
        if(full > 0 && mutex == 1)
        {
            mutex = 0; // lock

            item = buffer[out];
            printf("Consumed: %d\n", item);

            out = (out + 1) % BUFFER_SIZE;

            mutex = 1; // unlock
            full--;
            empty++;
        }
    }

    return 0;
}
