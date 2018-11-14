import traceback

from lewis.adapters.stream import StreamInterface
from lewis_emulators.utils.command_builder import CmdBuilder
from lewis.core.logging import has_log

MEASUREMENT_TYPE = {0: "VOLT:DC", 1: "VOLT:AC", 2: "CURR:DC", 3: "CURR:AC", 4: "RES", 5: "FRES", 6: "CONT",
                    7: "FREQ", 8: "PER"}
BUFFER_SOURCE = {0: "SENS", 1: "CALC", 2: "NONE"}
BUFFER_CONTROL_MODE = {0: "NEXT", 1: "ALW", 2: "NEV"}
TIMESTAMP_FORMAT = {0: "ABS", 1: "DELT"}
CONTROL_SOURCE = {0: "IMM", 1: "TIM", 2: "MAN", 3: "BUS", 4: "EXT"}
SCAN_STATE = {0: "INT", 1: "NONE", 2: "TODO: FIGURE THIS OUT"}


@has_log
class Keithley2700StreamInterface(StreamInterface):
    in_terminator = "\r\n"
    out_terminator = "\r\n"
    commands = {
        CmdBuilder("get_idn").escape("*IDN?").eos().build(),
        CmdBuilder("empty_queue").escape(":SYST:CLE").eos().build(),
        CmdBuilder("clear_buffer").escape("TRAC:CLE").eos().build(),
        CmdBuilder("set_measurement").escape(":FUNC '").eos().
        arg("VOLT:DC|VOLT:AC|CURR:DC|CURR:AC|RES|FRES|CONT|FREQ|PER")
        .escape("'").eos().build(),
        CmdBuilder("get_measurement").escape(":FUNC?").eos().build(),
        CmdBuilder("set_buffer_feed").escape("TRAC:FEED ").arg("SENS|CALC|NONE").eos().build(),
        CmdBuilder("set_buffer_control").escape("TRAC:FEED:CONT ").arg("NEV|NEXT|ALW").eos().build(),
        CmdBuilder("set_buffer_state").escape("TRAC:CLE:AUTO ").arg("OFF|ON").eos().build(),
        CmdBuilder("get_buffer_state").escape("TRAC:CLE:AUTO?").eos().build(),
        CmdBuilder("get_next_buffer_location").escape("TRAC:NEXT?").eos().build(),
        CmdBuilder("get_buffer_stats").escape("TRAC:FREE?").eos().build(),
        CmdBuilder("get_readings_from_range",  arg_sep="").escape("TRAC:DATA:SEL? ").int().escape(",").int().eos().
        build(),
        CmdBuilder("set_buffer_size").escape("TRAC:POIN ").int().eos().build(),
        CmdBuilder("get_buffer_size").escape("TRAC:POIN?").eos().build(),
        CmdBuilder("set_time_stamp_format").escape("TRAC:TST:FORM ").arg("ABS|DELT").eos().build(),
        CmdBuilder("get_time_stamp_format").escape("TRAC:TST:FORM?").eos().build(),
        CmdBuilder("get_delay_state").escape("TRIG:DEL:AUTO?").eos().build(),
        CmdBuilder("set_delay_state").escape("TRIG:DEL:AUTO ").arg("OFF|ON").eos().build(),
        CmdBuilder("set_init_state").escape("INIT:CONT ").arg("OFF|ON").eos().build(),
        CmdBuilder("get_init_state").escape("INIT:CONT?").eos().build(),
        CmdBuilder("set_sample_count").escape("SAMP:COUN ").int().eos().build(),
        CmdBuilder("get_sample_count").escape("SAMP:COUN?").eos().build(),
        CmdBuilder("set_source").escape("TRIG:SOUR ").arg("IMM|TIM|MAN|BUS|EXT").eos().build(),
        CmdBuilder("set_data_elements").escape("FORM:ELEM READ, CHAN, TST").eos().build(),
        CmdBuilder("set_auto_range_status", arg_sep="").escape("FRES:RANG:AUTO ").arg("OFF|ON").eos().build(),
        CmdBuilder("get_auto_range_status").escape("FRES:RANG:AUTO?").eos().build(),
        CmdBuilder("set_resistance_digits", arg_sep="").escape(":FRES:DIG ").int().escape(", (@").
        int().escape(":").int().escape(")").eos().build(),
        CmdBuilder("set_resistance_rate").escape(":FRES:NPLC ").float().eos().build(),
        CmdBuilder("set_scan_state").escape("ROUT:SCAN:LSEL ").arg("INT|NONE").eos().build(),
        CmdBuilder("get_scan_state").escape("ROUT:SCAN:LSEL?").eos().build(),
        CmdBuilder("set_scan_channels", arg_sep="").escape("ROUT:SCAN (@").int().escape(":").int().escape(")").eos().
        build(),
        CmdBuilder("get_scan_channels").escape("ROUT:SCAN?").eos().build()
    }

    def handle_error(self, request, error):
        self.log.error("An error occurred at request" + repr(request) + ": " + repr(error))
        self.log.error(traceback.format_exc())
        print("An error occurred at request" + repr(request) + ": " + repr(error))

    def bool_onoff_value(self, string_value):
        if string_value not in ["ON", "OFF"]:
            raise ValueError("Invalid on/off value!")
        return string_value == "ON"

    def enum_onoff_value(self, bool_value):
        if bool_value not in [True, False]:
            raise ValueError("Invalid on/off value!")
        else:
            return int(bool_value)

    def get_idn(self):
        return self._device.idn

    def empty_queue(self):
        self.log.info("Error log emptied")

    def clear_buffer(self):
        self._device.clear_buffer()

    def set_measurement(self, measurement):
        if measurement in MEASUREMENT_TYPE.values():
            self._device.measurement = MEASUREMENT_TYPE.keys()[MEASUREMENT_TYPE.values().index(measurement)]
        else:
            raise ValueError("Invalid measurement value!")

    def get_measurement(self):
        return "\"{}\"".format(MEASUREMENT_TYPE[self._device.measurement])

    def set_buffer_feed(self, feed):
        if feed in BUFFER_SOURCE.values():
            self._device.buffer_feed = BUFFER_SOURCE.keys()[BUFFER_SOURCE.values().index(feed)]
        else:
            raise ValueError("Invalid feed source value!")

    def set_buffer_control(self, control):
        if control in BUFFER_CONTROL_MODE.values():
            self._device.buffer_control = BUFFER_CONTROL_MODE.keys()[BUFFER_CONTROL_MODE.values().index(control)]
        else:
            raise ValueError("Invalid buffer control source value!")

    def set_buffer_state(self, state):
        self._device.buffer_autoclear_on = state

    def get_buffer_state(self):
        return "{}".format("ON" if self._device.buffer_autoclear_on else "OFF")

    def get_next_buffer_location(self):
        """
        :return: String-formatted integer of the next buffer location to retrieve
        """
        next_location = len(self._device.buffer)
        self.log.info("Next buffer location: {}".format(next_location))
        return "{}".format(next_location)

    def get_buffer_stats(self):
        """
        :return: String containing number of bytes available, and number of bytes used
        """
        return "{}, {}".format(str(self._device.bytes_available), str(self._device.bytes_used))

    def get_readings_from_range(self, start, end):
        """
        :param start: Start location in buffer
        :param end: Index of final buffer value to retrieve
        :return: String value of readings from buffer
        """

        chunks = []
        start, end = int(start), int(end)
        for buffer_location in range(start, end + 1):
            chunks.append("{},{},{}".format(self._device.buffer[buffer_location].reading,
                                            self._device.buffer[buffer_location].timestamp,
                                            self._device.buffer[buffer_location].channel))

        self.log.info("Returned readings: {}".format("No readings" if (len(chunks) == 0) else ",".join(chunks)))
        return ", ".join(chunks)

    def set_buffer_size(self, size):
        self._device.buffer_size = size

    def get_buffer_size(self):
        return self._device.buffer_size

    def set_time_stamp_format(self, timestamp_format):
        if timestamp_format in TIMESTAMP_FORMAT.values():
            self._device.time_stamp_format = TIMESTAMP_FORMAT.keys()[TIMESTAMP_FORMAT.values().index(timestamp_format)]
        else:
            raise ValueError("Invalid timestamp format value")

    def get_time_stamp_format(self):
        return TIMESTAMP_FORMAT[self._device.time_stamp_format]

    def get_delay_state(self):
        return self.enum_onoff_value(self._device.auto_delay_on)

    def set_delay_state(self, state):
        self._device.auto_delay_on = self.bool_onoff_value(state)

    def set_init_state(self, state):
        self._device.init_state_on = self.bool_onoff_value(state)

    def get_init_state(self):
        return self.enum_onoff_value(self._device.init_state_on)

    def set_sample_count(self, count):
        self._device.sample_count = count

    def get_sample_count(self):
        return "{0}".format(self._device.sample_count)

    def set_source(self, source):
        if source in CONTROL_SOURCE.values():
            self._device.source = CONTROL_SOURCE.keys()[CONTROL_SOURCE.values().index(source)]
        else:
            raise ValueError("Invalid control source value")

    def set_data_elements(self):
        self._device.data_elements = "READ, CHAN, TST"

    def set_auto_range_status(self, state):
        self._device.auto_range_on = self.bool_onoff_value(state)

    def get_auto_range_status(self):
        return self.enum_onoff_value(self._device.auto_range_on)

    def set_resistance_digits(self, digit, start, end):
            self._device.measurement_digits = digit

    def set_resistance_rate(self, rate):
        self._device.nplc = rate

    def set_scan_state(self, state):
        if state in SCAN_STATE.values():
            self._device.scan_state_status = SCAN_STATE.keys()[SCAN_STATE.values().index(state)]
        else:
            raise ValueError("Invalid scan state source value")

    def get_scan_state(self):
        return SCAN_STATE[self._device.scan_state_status]

    def get_scan_channels(self):
        return "(@{}:110,201:{})".format(self._device.scan_channel_start, self._device.scan_channel_end)

    def set_scan_channels(self, start, end):
        self._device.scan_channel_start = start
        self._device.scan_channel_end = end
