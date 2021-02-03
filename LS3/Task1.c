#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

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
    char line[100];
    double time = 0;

    // Print cpu model name
    while (!feof(cpuinfo))
    {
        fscanf(cpuinfo, "%[^\n]", line);
        if (strstr(line, "model name"))
        {
            printf("%s\n", line);
            break;
        }
    }

    // Print kernel version
    fscanf(version, "%[^\n]", line);
    printf("%s\n", line);

    // Print kernel version
    fscanf(meminfo, "%[^\n]", line);
    printf("%s\n", line);

    // Print uptime since boot
    fscanf(uptime, "%[^\n]", line);
    printf("The uptime since boot is %f\n", time);

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
        fscanf(stat, "%lld", &t);
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
    fscanf(meminfo, "%lld", &total);
    fscanf(meminfo, "%lld", &freeMem);
    freePer = 100.0 * freeMem / total;
    printf("Free Memory: %lld\nFree memory perentage: %f\n", freeMem, freePer);
    fclose(meminfo);
}

void diskRW()
{
    FILE *diskstats = fopen("/proc/diskstats", "r");
    long long readS, readT, writeS, writeT, t;
    float readR, writeR;
    char line[100], ts[100];
    size_t n = 0;
    while (!feof(diskstats))
    {
        fscanf(diskstats, "%[^\n]", line);
        sscanf(line, "%lld", &t);
        sscanf(line, "%lld", &t);
        sscanf(line, "%s", ts);
        if (strcmp(ts, "sda") == 0)
        {
            for (int i = 1; i <= 8; ++i)
            {
                sscanf(line, "%lld", &t);
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
    printf("Read rate: %f\nWrite rate: %f\n", readR, writeR);
    fclose(diskstats);
}

void contextSwitches()
{
    FILE *stat = fopen("/proc/stat", "r");
    long long switches, time;
    double rate;
    char line[100], t[10];
    size_t n = 0;
    while (!feof(stat))
    {
        fscanf(stat, "%[^\n]", line);
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
    char line[100], t[10];
    size_t n = 0;
    while (!feof(stat))
    {
        fscanf(stat, "%[^\n]", line);
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

void delay(int s)
{
    int ms = 1000 * s;
    clock_t start = clock();
    while (clock() < start + ms)
        ;
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
        delay(2);
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
        sscanf(*argv, "%d", &readRate);
        sscanf(*(argv + 1), "%d", &writeRate);
        v2(readRate, writeRate);
    }
}
