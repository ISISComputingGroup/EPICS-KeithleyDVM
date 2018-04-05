#include <registryFunction.h>
#include <epicsExport.h>
#include "aSubRecord.h"
#include "stdlib.h"
#include <stdio.h>

/*
*	Keithley 2700 Resistance Readings Parser
*
* 	Takes data from aSub record BUFFER:READINGS, finds the READING value and 
*	puts it into the correct Channel. 
*
*	VALA (value A) = channel 101 reading = CHNL:101:READING
*
*	"Why are there two C scripts that do very similar things (parse_channel_timestamps.c 
*	and parse_channel_readings.c)?"
*
*	Good question. aSub records have a limited number of outputs and so all of the channel
* 	:READING and :TIMESTAMP PVs couldn't be outputs for one record. An alternate solution could 
*	be to write the channel values to a waveform PV for each channel (e.g. CHNL:101:RAWVALS) and 
*	have a calc record in each channel which splits the waveform into :READING and :TIMESTAMP PVs.
*
*/

long i;
double *a;
double *vala, *valb,*valc,*vald,*vale,*valf,*valg,*valh,*vali,*valj,*valk,
*vall,*valm,*valn,*valo,*valp,*valq,*valr,*vals,*valt;

	
static long parse_channel_readings(aSubRecord *prec) {

	// prec = INPA from keithley2700.db, BUFF:READ - a waveform PV
    prec->pact = 1;

    a = (double *)prec->a;
	
	i = 0;
	
	while(a[i] > 0) {
		
		//printf("\nReading: %f\t\t Timestamp: %f\t\tChannel: %f", (a[i], a[i+1], a[i+2]));
		// Check for valid channel to start the parse

		int channel = a[i+2];
		double reading = a[i];
		// Find the channel and add reading value to correct channel PV
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
				printf("\n>>No Channel Found for reading: %f", reading);
				i=i+1;
				break;
		}		
		i=i+3;
    }

    prec->pact = 0;
    return 0;
}
epicsRegisterFunction(parse_channel_readings);
