// dzd77598 11/2018 
// Tests for the calculate_drift aSubRecord. 

#include <cxxtest/TestSuite.h>
#include <ios>
#include "../drift_utils.h"

#define TOLERANCE 1

class DriftTestSuite : public CxxTest::TestSuite {
    public:
        void test_GIVEN_no_prev_drift_WHEN_new_reading_added_THEN_new_drift_correct()
        {
            // note that this test will not use the smoothing factor, because
            // prev_drift is 0
            double expected_new_drift = -55.8816;
            // GIVEN
            double prev_drift = 0;
            double new_temp_delta = -2.3284;
            double new_time_delta = 0.05;
            double prev_temp = 93.8092;

            // WHEN
            double calculated_drift = drift_function_impl(new_temp_delta, new_time_delta,
                                                prev_drift, prev_temp);
            // THEN
            TS_ASSERT_DELTA(calculated_drift, expected_new_drift, TOLERANCE);
        }

        void test_GIVEN_prev_drift_WHEN_new_reading_added_THEN_new_drift_correct()
        {
            // Not that this test WILL use the smoothing factor
            double expected_new_drift = -87.7367;
            // GIVEN
            double prev_drift = -54.4848;
            double new_temp_delta = -1.4309;
            double new_time_delta = 0.05;
            double prev_temp = 91.4808; 

            // WHEN
            double calculated_drift = drift_function_impl(new_temp_delta, new_time_delta,
                                                prev_drift, prev_temp);
            
            TS_ASSERT_DELTA(calculated_drift, expected_new_drift, TOLERANCE);
        }
};