#include "find_min_max.h"

#include <limits.h>

struct MinMax GetMinMax(int *array, unsigned int begin, unsigned int end) {

struct MinMax min_max;

min_max.min = INT_MAX;

min_max.max = INT_MIN;

int min = array[0];

int max = array[0];

for(int i = 0; i < end; ++i)

{

if(array[i] > max){max = array[i];}

if(array[i] < min){min = array[i];}

}

min_max.min = min;

min_max.max = max;

return min_max;

}