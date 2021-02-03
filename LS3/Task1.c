#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void v1()
{
    // Open all the required files
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    FILE *version = fopen("/proc/version", "r");
    FILE *meminfo = fopen("/proc/meminfo", "r");
    FILE *uptime = fopen("/proc/uptime", "r");

    // Check that all are opened correctly
    assert(cpuinfo != NULL);
    assert(version != NULL);
    assert(meminfo != NULL);
    assert(uptime != NULL);

    size_t n = 0;
    char *line = NULL;
    double time = 0;

    // Print cpu model name
    while (getline(&line, &n, cpuinfo) > 0)
    {
        if (strstr(line, "model name"))
        {
            printf("%s\n", line);
            break;
        }
    }

    // Print kernel version
    getline(&line, &n, version);
    printf("%s\n", line);

    // Print kernel version
    getline(&line, &n, meminfo);
    printf("%s\n", line);

    // Print uptime since boot
    fscanf(uptime, "%lf", &time);
    printf("The uptime since boot is %f\n", time);

    free(line);
    fclose(cpuinfo);
    fclose(version);
    fclose(meminfo);
    fclose(uptime);
}

void processorTime()
{
    FILE *stat = fopen("/proc/stat", "r");
    long long total = 0, ut, st, it, t;
    float up, sp, ip;
    for (int i = 1; i <= 8; ++i)
    {
        fscanf(stat, "%ld", &t);
        if (i == 1)
            ut = t;
        else if (i == 3)
            st == t;
        else if (i == 4)
            it = t;
        total += t;
    }
    up = 100.0 * ut / total;
    sp = 100.0 * st / total;
    ip = 100.0 * it / total;
    printf("User time percentage: %f\nSystem time percentage: %f\nIdle time percentage: %f\n", up, sp, ip);
    fclose(stat);
}

void freeMemory()
{
    FILE *meminfo = fopen("/proc/stat", "r");
    long long freeMem, total;
    float freePer;
    fscanf(meminfo, "%ld", &total);
    fscanf(meminfo, "%ld", &freeMem);
    freePer = 100.0 * freeMem / total;
    printf("Free Memory: %ld\nFree memory perentage: %f\n", freeMem, freePer);
    fclose(meminfo);
}

void diskRW()
{
    FILE *diskstats = fopen("/proc/diskstats", "r");
    long long readS, readT, writeS, writeT, t;
    float readR, writeR;
    char *line = NULL, *ts;
    size_t n = 0;
    while (getline(&line, &n, diskstats) > 0)
    {
        sscanf(line, "%d", &t);
        sscanf(line, "%d", &t);
        sscanf(line, "%s", ts);
        if (strcmp(ts, "sda") == 0)
        {
            for (int i = 1; i <= 8; ++i)
            {
                sscanf(line, "%ld", &t);
                if (i == 3)
                    readS = t;
                else if (i == 4)
                    readT == t;
                else if (i == 7)
                    writeS = t;
                else if (i == 8)
                    writeT = t;
            }
            break;
        }
    }
    readR = 1000.0 * readS / readT;
    writeR = 1000.0 * writeS / writeT;
    printf("Read rate: %d\nWrite rate: %f\n", readR, writeR);
    fclose(diskstats);
}

void contextSwitches()
{
    FILE *stat = fopen("/proc/stat", "r");
    long long switches, time;
    double rate;
    char *line = NULL;
    char t[10];
    size_t n = 0;
    while (getline(&line, &n, stat) > 0)
    {
        sscanf(line, "%s", t);
        if (strcmp(t, "ctxt") == 0)
        {
            sscanf(line, "%lld", &switches);
        }
        else if (strcmp(t, "btime") == 0)
        {
            sscanf(line, "%lld", &time);
        }
    }
    rate = 1.0 * switches / time;
    printf("Context switching rate: %lf\n", rate);
    fclose(stat);
}

void processes()
{
    FILE *stat = fopen("/proc/stat", "r");
    long long process, time;
    double rate;
    char *line = NULL;
    char t[10];
    size_t n = 0;
    while (getline(&line, &n, stat) > 0)
    {
        sscanf(line, "%s", t);
        if (strcmp(t, "processes") == 0)
        {
            sscanf(line, "%lld", &process);
        }
        else if (strcmp(t, "btime") == 0)
        {
            sscanf(line, "%lld", &time);
        }
    }
    rate = 1.0 * process / time;
    printf("Process creation rate: %lf\n", rate);
    fclose(stat);
}

void v2(int readRate, int writeRate)
{
    for (int i = 0; true; ++i)
    {
        processorTime();
        freeMemory();
        diskRW();
        contextSwitches();
        processes();
        _sleep(1000);
    }
}

int main(int argc, char *argv[])
{
    --argc, ++argv;
    if (argc == 0)
        v1();
    else
    {
        int readRate, writeRate;
        sscanf(argv++, "%d", &readRate);
        sscanf(argv, "%d", &writeRate);
        v2(readRate, writeRate);
    }
}