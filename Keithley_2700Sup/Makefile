TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files

# Keithley 2700 Library 
LIBRARY_IOC += Keithley2700
DATA += devKeithley_2700.proto
DBD += Keithley_2700.dbd


Keithley2700_DBD += asyn.dbd
Keithley2700_DBD += utilities.dbd
Keithley2700_DBD += asubFunctions.dbd
Keithley2700_DBD += asSupport.dbd
Keithley2700_DBD += stream.dbd
Keithley2700_DBD += sseqRecord.dbd
Keithley2700_LIBS += $(EPICS_BASE_IOC_LIBS)

# aSub record
Keithley2700_LIBS += asyn utilities
Keithley2700_LIBS += asubFunctions
Keithley2700_SRCS += parse_buffer_readings.c calculate_drift.c

# Test Runner
TESTPROD_HOST += runner
runner_CPPFLAGS += -I$(CXXTEST)
runner_SRCS += runner.cpp calculate_drift.c
runner_LIBS += Keithley_2700
runner_SYS_LIBS_WIN32 += wldap32

#=======================================
include $(TOP)/configure/RULES

../runner.cpp:
	$(CXXTEST)/bin/cxxtestgen --xunit-printer -w keithley2700 -o runner.cpp ../../tests/*tests.h