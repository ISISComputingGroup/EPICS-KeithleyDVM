#include "drift_utils.h"
#include <math.h>
#include <stdio.h>

#define SMOOTHING_FACTOR 50

double previous_proportion = 1.0 - (1.0/SMOOTHING_FACTOR);

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
        new_drift = temp_change_over_time;
        printf("Assigned new drift with nans to %f\n", new_drift);
    }
    else {
        new_drift = temp_change_over_time + previous_drift;
        printf("Assigned new drift without nans to %f\n", new_drift);
    }
    return new_drift;
}