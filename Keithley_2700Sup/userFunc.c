/*  For use with the cvt Record. This file produces a spline fit for a set of data passed to it via the SPEC field
    field in the cvt record.

    The function must be named *** userFunc.c *** because there is no clean way (without significant restructure
    of the cvt record) to pass in a user defined function name AND a clibration file to produce a fit from. 
    Therefore, the record (the backend cvtRecord.c) just looks for a function signature of a hardcoded name

    userFunc

    and calls this. 

    The function creates a spline fit and an accelerator (essentially a lookup table of previously evaluated
    values) and bundles them into a struct to push to the DPVT field so that it can be retrieved each time 
    an evaluation is called. This means that the fit does not need to be produced, nor an accelerator allocated 
    each time the function is called.

    The record backend produces a value by calling 

    VAL = userFunc(x, y, &DPVT)

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

// Struct may need to contain more things. TBD
struct Spline_data_container {
    gsl_interp_accel *accelerator;
    gsl_spline *spline;
};

/*  args:
        bool isInit:        flag passed by caller to determine if the fit is being initialised 
        double x_data[]:    array of calibration data
        double y_data[]:    array of calibration data
        int len_arr:        length of x and y arrays
        double x:           value to be evaluated by fit
        void ** dpvt:       pointer to record's dpvt field for storing data between calls       
*/
double user1DTableSub(bool isInit, double x_data[], double y_data[], int len_arr, double x, void ** dpvt) {

    gsl_interp_accel *acc;
    gsl_spline *spline;
    struct Spline_data_container *spline_d_cont;

    if (isInit) {
        spline_d_cont = (Spline_data_container *)malloc(sizeof(Spline_data_container));

        acc = gsl_interp_accel_alloc();
        spline = gsl_spline_alloc(gsl_interp_cspline, len_arr);
        gsl_spline_init(spline, x_data, y_data, len_arr);

        spline_d_cont->accelerator = acc;
        spline_d_cont->spline = spline;
        
        // put struct into DPVT memory
        if (spline_d_cont) {
            *dpvt = spline_d_cont;
        }
    }
    else { // is evaluating
        double val;
        spline_d_cont = (Spline_data_container *) *dpvt;

        val = gsl_spline_eval(spline_d_cont->spline, x, spline_d_cont->acc);
        return val;
    }

    return 0;
}