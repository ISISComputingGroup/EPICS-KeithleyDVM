TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files

# Keithley 2700 Library 
LIBRARY_IOC += Keithley2700
DATA += devKeithley_2700.proto
DBD += Keithley2700.dbd

Keithley2700_DBD += asyn.dbd
Keithley2700_DBD += utilities.dbd
Keithley2700_DBD += asubFunctions.dbd
Keithley2700_DBD += asSupport.dbd
Keithley2700_DBD += stream.dbd
Keithley2700_DBD += sseqRecord.dbd

Keithley2700_SRCS += parse_buffer_readings.c calculate_drift.c drift_utils.cpp

# aSub record
Keithley2700_LIBS += asyn utilities
Keithley2700_LIBS += asubFunctions
Keithley2700_LIBS += seq pv
Keithley2700_LIBS += $(EPICS_BASE_IOC_LIBS)

#=======================================
# googleTest Runner
# Does not currently build on build servers

ifeq ($(findstring 10.0,$(VCVERSION)),)

SRC_DIRS += $(TOP)/Keithley_2700Sup/tests

TESTPROD_HOST += runner
USR_CPPFLAGS += -I$(GTEST)/googletest/include
runner_LIBS += gtest
runner_SRCS += run_all_tests.cc drift_tests.cc
runner_SRCS += drift_utils.cpp

endif

#=======================================
include $(TOP)/configure/RULES
