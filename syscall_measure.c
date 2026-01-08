#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define ITERATIONS 1000000

double get_time(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;

}
void measure_timer_precision(){
    printf("Measuring timer precission...\n");
    double times[100];

    for(int i = 0; i < 100; i++){
        double start = get_time();
        double end   = get_time();
        times[i] = (end - start) * 1000000.0 ; //convert to microseconds
    }
    //find minimum non zero difference
    double min_diff = times[0];
    for(int i = 0; i < 100; i++){
        if(times[i] > 0 && times[i] < min_diff){
            min_diff = times[i];
        }
    }

    printf("Timer precision: approximately %.3f microseconds\n\n", min_diff);
}
void measure_syscall_cost(){
    printf("measuring system call cost...\n");

    //open /dev/null/ for our read system call
    int fd = open("/dev/null/", O_RDONLY);
    if(fd < 0){
    perror("open");
    exit(1);
    }

    //warm up
    char buf[1];
    for(int i=0; i < 1000; i++){
    read(fd,buf,0);
    }

    //actual measurement
    double start = get_time();
    for(int i=0; i < ITERATIONS; i++){
        read(fd,buf,0);
    }
    double end = get_time();

    close(fd);

    double total_time = (end - start) * 1000000.0; // convert to microseconds
    double avg_time = total_time / ITERATIONS;

    printf("Total iteration time for %d iterations: %.2f microseconds\n",ITERATIONS, total_time);
    printf("Average system call cost: %.3f\n",avg_time);
    printf("Average system call cost: %.0f nanoseconds\n\n ", avg_time * 1000);
}

int main(){
    printf("===system call cost Measurement ==\n\n");
    measure_timer_precision();
    measure_syscall_cost();

    return 0;
}
