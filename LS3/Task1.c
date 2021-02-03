#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
    fscanf(uptime, "%f", &time);
    printf("The uptime since boot is %f\n", time);

    free(line);
    fclose(cpuinfo);
    fclose(version);
    fclose(meminfo);
    fclose(uptime);
}

void v2() {}

int main(int argc, char *argv[])
{
    --argc, ++argv;
    if (argc == 0)
        v1();
    else
        v2();
}