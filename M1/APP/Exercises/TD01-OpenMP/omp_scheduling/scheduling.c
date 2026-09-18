#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char **argv)
{
    int n = 10000;
    omp_sched_t omp_sched = omp_sched_auto;
    int param_sched = 0;

    const int max_sched = omp_sched_auto+1;
    const char *sched_str[5] = {
        "undef",
        "static",
        "dynamic",
        "guided",
        "auto"
    };

    if (argc > 1)
    {
        for(omp_sched_t sched = omp_sched_static ; (int)sched < max_sched ; sched = (omp_sched_t)((int)sched + 1))
        {
            if (strcmp(argv[1], sched_str[(int)sched]) == 0)
            {
                omp_sched = sched;
            }
        }
    }
    if (argc > 2)
    {
        param_sched = atoi(argv[2]);
    }
    omp_set_schedule(omp_sched, param_sched);
    if (param_sched > 0)
    {
        printf("Scheduling choisi : %s,%d\n", sched_str[(int)omp_sched], param_sched);
    }
    else
    {
        printf("Scheduling choisi : %s\n", sched_str[(int)omp_sched]);
    }

#pragma omp parallel 
    {
        int trank = omp_get_thread_num();
        char nom[32];
        sprintf(nom, "iter_T%02d", trank);
        FILE *fd = fopen(nom, "w");

#pragma omp for schedule(runtime)
        for(int i = 0 ; i < n ; i++)
        {
            fprintf(fd, "%d %d\n", i, trank);
        }

        fclose(fd);
    }
    return 0;
}
