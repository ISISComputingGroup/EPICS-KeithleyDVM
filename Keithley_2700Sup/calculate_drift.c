#include <registryFunction.h>
#include <epicsExport.h>
#include "aSubRecord.h"
#include "stdlib.h"
#include <stdio.h>
#include <menuFtype.h>
#include <math.h>

#define SMOOTHING_FACTOR 50

/*
*	Keithley 2700 Drift Calculator
*
* 	Calculates drift value based on time and temperature data.
*
*/

double previous_proportion = 1 - (1/SMOOTHING_FACTOR);

static void assign_value_to_pv(double *val, epicsEnum16 ftv, double reading) {
	// Check that the input type is a double
	if(ftv != menuFtypeDOUBLE) {
		printf("\nIncorrect input type, cannot process this value");
	}
	else {
		((double *)val)[0] = reading;
	}
}

static long calculate_drift(aSubRecord *prec) {

  prec->pact = 1;

  double *current_temp_pv = (double *)prec->a;
  double *previous_temp_pv = (double *)prec->b;
  double *current_time_pv = (double *)prec->c;
  double *previous_timeious_pv = (double *)prec->d;
	double *previous_drift_pv = (double *)prec->e;

	// These PV references contain a single item but are still accessed as an array index.
	double current_temp = current_temp_pv[0];
	double previous_temp = previous_temp_pv[0];
	double current_time = current_time_pv[0];
	double previous_time = previous_timeious_pv[0];
	double previous_drift = previous_drift_pv[0];

	double temp_delta = current_temp - previous_temp;
	double time_delta = current_time - previous_time;
	double new_drift_value = previous_drift;

	// If we have a new timestamped value, calculate the drift
	if (time_delta > 0) {
		double temp_change_over_time = 0;
		previous_drift = previous_drift * previous_proportion;

		// If there is previous temperatura data
		if (previous_temp > 0) {
			temp_change_over_time = ((temp_delta/time_delta)*60); // seconds in minute
		}
		temp_change_over_time = temp_change_over_time/SMOOTHING_FACTOR;

		// If temp_change_over_time and previous_drift are valid values (not infinity or NaN)
		if ((!isnan(temp_change_over_time)) && (isnan(previous_drift))) {
			new_drift_value = temp_change_over_time;
		}
		else {
			new_drift_value = temp_change_over_time + previous_drift;
		}
	}

	// Assign current temperature to $(CHANNEL):TEMP:PREV
	assign_value_to_pv(prec->valb, prec->ftvb, current_temp);
	// Assign current timestamp to $(CHANNEL):TIME:PREV
	assign_value_to_pv(prec->valc, prec->ftvc, current_time);
	// Assign new drift calculation to $(CHANNEL):DRIFT
	assign_value_to_pv(prec->vala, prec->ftva, new_drift_value);

    prec->pact = 0;
    return 0;
}

epicsRegisterFunction(calculate_drift);
