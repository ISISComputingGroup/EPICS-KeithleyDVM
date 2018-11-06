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

Keithley2700_LIBS += $(EPICS_BASE_IOC_LIBS)
Keithley2700_LIBS += seqDev seq pv

# aSub record
Keithley2700_LIBS += asyn utilities
Keithley2700_LIBS += asubFunctions
Keithley2700_SRCS += parse_buffer_readings.c calculate_drift.c drift_utils.cpp

# Test Runner
TESTPROD_HOST += runner
runner_CPPFLAGS += -I$(CXXTEST)
runner_SRCS += runner.cpp drift_utils.cpp
runner_LIBS += Keithley2700
runner_SYS_LIBS_WIN32 += wldap32

#=======================================
include $(TOP)/configure/RULES

../runner.cpp:
	$(CXXTEST)/bin/cxxtestgen --xunit-printer -w keithley2700 -o runner.cpp ../tests/*tests.h