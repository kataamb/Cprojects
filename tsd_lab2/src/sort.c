#include "sort.h"

/*
    get picoseconds
*/
double get_picoseconds(int beg, int end)
{
    double ms = (double)((end - beg) *1000 * 1000);
    return (double)(ms / CLOCKS_PER_SEC);
}


int comparator_prf(const void *prf1, const void *prf2)
{
    return strcmp(((perform *)prf1)->perform_name, ((perform *)prf2)->perform_name);
}
/*
    sort with qsort
*/
double qsort_time_p(perform **darr_perf, size_t size, int (*comp)(const void *, const void *))
{
    time_t beg, end;

    beg = clock();

    
    qsort(*darr_perf, size, sizeof(perform), comp);
    end = clock();

    return get_picoseconds(beg, end);
}

/*
    sort with bubble sort
*/
double bubble_time_p(perform **darr_perf, size_t size, int (*comp)(const void *, const void *))
{
    time_t beg, end;

    beg = clock();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (comp( (const perform *)(*darr_perf) + i, (const perform *)(*darr_perf) + j) < 0)
            {
                swap_perf((*darr_perf) + i, (*darr_perf) + j);
            }
        }
    }
    end = clock();

    return get_picoseconds(beg, end);
}




int comparator_key(const void *k1, const void *k2)
{
    return strcmp(((key_t *)k1)->perform_name, ((key_t *)k2)->perform_name);
}
/*
    sort with qsort
*/
double qsort_time_k(key_t **darr_perf, size_t size, int (*comp)(const void *, const void *))
{
    time_t beg, end;

    beg = clock();

    qsort(*darr_perf, size, sizeof(key_t), comp);

    end = clock();

    return get_picoseconds(beg, end);
}

/*
    sort with bubble sort
*/
double bubble_time_k(key_t **darr_perf, size_t size, int (*comp)(const void *, const void *))
{
    time_t beg, end;

    beg = clock();

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i + 1; j < size; j++)
        {
            if (comp( (const perform *)(*darr_perf) + i, (const perform *)(*darr_perf) + j) < 0)
            {
                swap_key((*darr_perf) + i, (*darr_perf) + j);
            }
        }
    }
    end = clock();

    return get_picoseconds(beg, end);
}