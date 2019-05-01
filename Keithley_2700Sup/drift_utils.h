#ifdef __cplusplus
extern "C" {
#endif

extern double drift_function_impl(double temp_delta, 
                                  double time_delta, 
                                  double previous_drift,
                                  double prev_temp);

#ifdef __cplusplus
}
#endif
