#include <registryFunction.h>
#include <epicsExport.h>
#include "aSubRecord.h"
#include "stdlib.h"
#include <stdio.h>


/*
*	Keithley 2700 Data Parser
*
* 	Takes data from aSub record BUFFER:READINGS, finds the READING value and 
*	puts it into the correct Channel. 
*
*	VALA (value A) = channel 101 reading = CHNL:101:READING
*
*/

static long parse_channel_readings(aSubRecord *prec) {
    long i;
	// vala = VALUE A from .db
    double *a;
	double *vala, *valb,*valc,*vald,*vale,*valf,*valg,*valh,*vali,*valj,*valk,
	*vall,*valm,*valn,*valo,*valp,*valq,*valr,*vals,*valt;


	int count; // how many values have we received?
	double reading[3]; // a reading containing value, timestamp and channel
	
    prec->pact = 1;

	
	// a = INPUT A
    a = (double *)prec->a;
	
    //for(i=0; i < (prec->noa); ++i)
	i = 0;
	while(a[i] > 0) {
    
		// printf("\nReading: %f\t Timestamp: %f\tChannel: %f", (a[i], a[i+1], a[i+2]));
		int channel = a[i+2];
		double reading = a[i];
		
		switch(channel) {
			case 101:
				((double *)prec->vala)[0] = reading;	
				break;
			case 102:
				((double *)prec->valb)[0] = reading;
				break;
			case 103:
				((double *)prec->valc)[0] = reading;
				break;
			case 104:
				((double *)prec->vald)[0] = reading;
				break;
			case 105:
				((double *)prec->vale)[0] = reading;
				break;
			case 106:
				((double *)prec->valf)[0] = reading;
				break;
			case 107:
				((double *)prec->valg)[0] = reading;
				break;
			case 108:
				((double *)prec->valh)[0] = reading;
				break;
			case 109:
				((double *)prec->vali)[0] = reading;
				break;
			case 110:
				((double *)prec->valj)[0] = reading;
				break;
			case 201:
				((double *)prec->valk)[0] = reading;
				break;
			case 202:
				((double *)prec->vall)[0] = reading;
				break;
			case 203:
				((double *)prec->valm)[0] = reading;
				break;
			case 204:
				((double *)prec->valn)[0] = reading;
				break;
			case 205:
				((double *)prec->valo)[0] = reading;
				break;
			case 206:
				((double *)prec->valp)[0] = reading;
				break;
			case 207:
				((double *)prec->valq)[0] = reading;
				break;
			case 208:
				((double *)prec->valr)[0] = reading;
				break;
			case 209:
				((double *)prec->vals)[0] = reading;
				break;
			case 210:
				((double *)prec->valt)[0] = reading;
				break;
			default: 
				printf("\nNo Channel Found for reading: %f", reading);
		}
		
		
		// TO DO
		// split into groups of 3
		// check for channel
		// assign to correct val variable
		
		// sets first element of CHNL:101:RAWDATA waveform
		// How to access other elements?
		//((double *)prec->vala)[0] = 99.88;
		i=i+3;
    }

    prec->pact = 0;
    //Debug message - prints to IOC
    //printf("my_asub_routine called");
    return 0;
}
epicsRegisterFunction(parse_channel_readings);