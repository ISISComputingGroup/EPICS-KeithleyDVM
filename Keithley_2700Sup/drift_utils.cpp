#include "drift_utils.h"
#include <math.h>


#define SMOOTHING_FACTOR 50

double previous_proportion = 1 - (1/SMOOTHING_FACTOR);

double drift_function_impl(double temp_delta, double time_delta, double previous_drift, 
                           double prev_temp)
{
    double temp_change_over_time, new_drift = 0;
    previous_drift = previous_drift * previous_proportion;

    // If there is previous temperature data
    if (prev_temp > 0) {
        temp_change_over_time = ((temp_delta/time_delta)*60); // seconds in minute
    }
    temp_change_over_time = temp_change_over_time/SMOOTHING_FACTOR;

    // If temp_change_over_time and previous_drift are valid values (not infinity or NaN)
    if ((!isnan(temp_change_over_time)) && (isnan(previous_drift))) {
        return new_drift = temp_change_over_time;
    }
    else {
        return new_drift = temp_change_over_time + previous_drift;
    }
}