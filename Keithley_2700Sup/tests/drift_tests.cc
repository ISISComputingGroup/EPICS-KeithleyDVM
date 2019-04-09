#include "gtest/gtest.h"
#include <ios>
#include "../drift_utils.h"

// Magic number test values are all taken from real historical run data

#define TOLERANCE 0.1

namespace {
    TEST(DriftTests, test_GIVEN_no_prev_drift_WHEN_new_reading_added_THEN_new_drift_correct) {
        // note that this test will not use the smoothing factor, because
        // prev_drift is 0
        double expected_new_drift = -0.000666667;
        // GIVEN
        double prev_drift = 0;
        double new_temp_delta = -0.16;
        double new_time_delta = 360;
        double prev_temp = 51.56;

        // WHEN
        double calculated_drift = drift_function_impl(new_temp_delta, new_time_delta,
                                            prev_drift, prev_temp);
        // THEN
        ASSERT_NEAR(calculated_drift, expected_new_drift, TOLERANCE);
    }

    TEST(DriftTests, test_GIVEN_prev_drift_WHEN_new_reading_added_THEN_new_drift_correct) {
        // Not that this test WILL use the smoothing factor
        double expected_new_drift = -0.00135333;
        // GIVEN
        double prev_drift = -0.000666667;
        double new_temp_delta = -0.25;
        double new_time_delta = 360;
        double prev_temp = 51.40; 

        // WHEN
        double calculated_drift = drift_function_impl(new_temp_delta, new_time_delta,
                                            prev_drift, prev_temp);
        
        ASSERT_NEAR(calculated_drift, expected_new_drift, TOLERANCE);
    }
} // namespace
