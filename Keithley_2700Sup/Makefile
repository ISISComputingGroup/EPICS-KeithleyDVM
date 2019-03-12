TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files

# Keithley 2700 Library 
LIBRARY_IOC += Keithley2700
DATA += devKeithley_2700.proto
DBD += Keithley2700.dbd


Keithley2700_LIBS += $(EPICS_BASE_IOC_LIBS)

Keithley2700_LIBS += gsl
Keithley2700_SRCS += parse_buffer_readings.c calculate_drift.c drift_utils.cpp user1DTableSub.c

USR_CFLAGS += -DGSL_DLL -DWIN32 /Od
 
# googletest Test Runner

SRC_DIRS += $(TOP)/Keithley_2700Sup/tests

TESTPROD_HOST += runner
USR_CPPFLAGS += -I$(GTEST)/googletest/include
runner_LIBS += gtest
runner_SRCS += run_all_tests.cc drift_tests.cc
runner_SRCS += drift_utils.cpp

#=======================================
include $(TOP)/configure/RULES
