#include <registryFunction.h>
#include <epicsExport.h>
#include <aSubRecord.h>
#include <stdlib.h>
#include <stdio.h>
#include <menuFtype.h>

/*
*	Keithley 2700 Resistance Buffer Readings Parser
*
* 	Takes data from aSub record BUFF:READ, finds the Reading and Timestamp value and
*	puts it into the correct Channel.
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

static long parse_buffer_readings(aSubRecord *prec, long array_offset) {

	/* 	'array_offset' refers to the index of the buffer array. This value will be 0 or 1, allowing
	* 	this script to parse the timestamp and reading value depending on the value of array_offset.
	* 	a[i] = channel reading
	* 	a[i+1] = channel timestamp
	* 	a[i+2] = channel
	*/

	double *a;
	// We have 3 values per channel - reading, timestamp and channel
	const int channel_values_count = 3;
	unsigned long i = 0;
	// prec = INPA from keithley2700.db, BUFF:READ - a waveform PV
    prec->pact = 1;

    a = (double *)prec->a;

	while((a[i] > 0) && (i < (prec->noa)-channel_values_count)) {

		int channel = (int)(a[i+2]+0.5); // protection against double to int rounding errors
		double value = a[i+array_offset];

		// Find the channel and add reading value to correct channel PV
		switch(channel) {
			case 101:
				assign_value_to_pv(prec->vala, prec->ftva, value);
				break;
			case 102:
				assign_value_to_pv(prec->valb, prec->ftva, value);
				break;
			case 103:
				assign_value_to_pv(prec->valc, prec->ftva, value);
				break;
			case 104:
				assign_value_to_pv(prec->vald, prec->ftva, value);
				break;
			case 105:
				assign_value_to_pv(prec->vale, prec->ftva, value);
				break;
			case 106:
				assign_value_to_pv(prec->valf, prec->ftva, value);
				break;
			case 107:
				assign_value_to_pv(prec->valg, prec->ftva, value);
				break;
			case 108:
				assign_value_to_pv(prec->valh, prec->ftva, value);
				break;
			case 109:
				assign_value_to_pv(prec->vali, prec->ftva, value);
				break;
			case 110:
				assign_value_to_pv(prec->valj, prec->ftva, value);
				break;
			case 201:
				assign_value_to_pv(prec->valk, prec->ftva, value);
				break;
			case 202:
				assign_value_to_pv(prec->vall, prec->ftva, value);
				break;
			case 203:
				assign_value_to_pv(prec->valm, prec->ftva, value);
				break;
			case 204:
				assign_value_to_pv(prec->valn, prec->ftva, value);
				break;
			case 205:
				assign_value_to_pv(prec->valo, prec->ftva, value);
				break;
			case 206:
				assign_value_to_pv(prec->valp, prec->ftva, value);
				break;
			case 207:
				assign_value_to_pv(prec->valq, prec->ftva, value);
				break;
			case 208:
				assign_value_to_pv(prec->valr, prec->ftva, value);
				break;
			case 209:
				assign_value_to_pv(prec->vals, prec->ftva, value);
				break;
			case 210:
				assign_value_to_pv(prec->valt, prec->ftva, value);
				break;
			default:
				printf("\n>>No Channel Found for value: %f (channel %d)", value, channel);
				i=i+1;
				break;
		}
		i=i+channel_values_count;
    }

    prec->pact = 0;
    return 0;
}

static long parse_channel_readings(aSubRecord *prec) {
	return parse_buffer_readings(prec, 0);
}

static long parse_channel_timestamps(aSubRecord *prec) {
	return parse_buffer_readings(prec, 1);
}

epicsRegisterFunction(parse_channel_readings);
epicsRegisterFunction(parse_channel_timestamps);
