TOP=..
include $(TOP)/configure/CONFIG
#=======================================

# Install .dbd and .db files
DATA += devKeithley_2700.proto

DBD += Keithley2700.dbd

LIBRARY_IOC += Keithley2700

Keithley2700_DBD += asyn.dbd
Keithley2700_DBD += utilities.dbd
Keithley2700_DBD += asubFunctions.dbd
Keithley2700_DBD += asSupport.dbd
Keithley2700_DBD += stream.dbd

Keithley2700_LIBS += $(EPICS_BASE_IOC_LIBS)
Keithley2700_LIBS += asyn utilities
Keithley2700_LIBS += asubFunctions

Keithley2700_SRCS += parse_buffer_readings.c

#=======================================
include $(TOP)/configure/RULES
