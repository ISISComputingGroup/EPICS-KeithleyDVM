#include <registryFunction.h>
#include <epicsExport.h>
#include "aSubRecord.h"
#include "stdlib.h"
#include <stdio.h>
#include <menuFtype.h>

/*
*	Keithley 2700 Drift Calculator
*
* 	Calculates drift value based on time and temperature data.
*
*	VALA (value A) = channel 101 reading = CHNL:101:READ etc
*
*
*/
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
	
	double *temperature_delta_record;
	double temperature_delta;
	double *time_delta_record;
	double time_delta;
	double *previous_drift_record;
	double previous_drift;

    prec->pact = 1;
	
    temperature_delta_record = (double *)prec->a;	
    time_delta_record = (double *)prec->b;	
    previous_drift_record = (double *)prec->c;	
	
	for (int i=0; i<prec->noa; i++) {
           temperature_delta = temperature_delta_record[i];
		   time_delta = time_delta_record[i];
		   previous_drift = previous_drift_record[i];
       }
	//printf("\n>> time_delta: %f", time_delta);
	//printf("\n>> temperature_delta: %f", temperature_delta);
	
	/*
	! need prev_temp!
	! calculate deltas in program?
	
	pseudo:
	A = (temp_delta/time_delta)*60
	if previ_temp = 0, B = 0, otherwise B = A
	C = B/50 + (prev_drift*.98)
	
	*/
	
	assign_value_to_pv(prec->vala, prec->ftva, 999.999);
	


    prec->pact = 0;
    return 0;
}

epicsRegisterFunction(calculate_drift);
