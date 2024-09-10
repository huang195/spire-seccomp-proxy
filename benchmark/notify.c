#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    // Number of iterations
    const int iterations = 1000;
    const char *file_path = "a.pem";

    // Create the test file if it doesn't exist
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        perror("Failed to create file");
        return 1;
    }
    fprintf(file, "Benchmarking file open speed.\n");
    fclose(file);

    // Start the benchmark
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < iterations; i++) {
        FILE *file = fopen(file_path, "r");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }
        fclose(file);
    }

    // End the benchmark
    gettimeofday(&end_time, NULL);

    unlink(file_path);

    // Calculate the time taken
    long seconds = end_time.tv_sec - start_time.tv_sec;
    long microseconds = end_time.tv_usec - start_time.tv_usec;
    double total_time = seconds + microseconds*1e-6;
    double time_per_file = total_time / iterations;

    printf("Total time for %d iterations: %f seconds\n", iterations, total_time);
    printf("Average time per file open/close: %f microseconds\n", time_per_file * 1e6);

    return 0;
}

