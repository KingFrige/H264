ifeq ($(VERILATOR_ROOT),)
VERILATOR = verilator
VERILATOR_COVERAGE = verilator_coverage
else
export VERILATOR_ROOT
VERILATOR = $(VERILATOR_ROOT)/bin/verilator
VERILATOR_COVERAGE = $(VERILATOR_ROOT)/bin/verilator_coverage
endif

# VERILATOR_FLAGS += --CFLAGS "-include verilator.h"
# Generate C++ in executable form
VERILATOR_FLAGS += -cc --exe --binary
# Generate makefile dependencies (not shown as complicates the Makefile)
#VERILATOR_FLAGS += -MMD
# Optimize
VERILATOR_FLAGS += -x-assign fast
# Warn abount lint issues; may not want this on less solid designs
VERILATOR_FLAGS += -Wall -Wno-fatal
# Make waveforms
VERILATOR_FLAGS += --trace
# Check SystemVerilog assertions
VERILATOR_FLAGS += --assert
# Generate coverage analysis
VERILATOR_FLAGS += --coverage
# Run Verilator in debug mode
#VERILATOR_FLAGS += --debug
# Add this trace to get a backtrace in gdb
#VERILATOR_FLAGS += --gdbbt

# Input files for Verilator
VERILATOR_INPUT = -f input.vc -f flist --top-module h264i

test-build:
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT)

sim:
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILATOR_INPUT) sim_main.cpp
	@echo "-- BUILD -------------------"
	$(MAKE) -j -C obj_dir -f ../Makefile_obj
	@echo "-- RUN ---------------------"
	obj_dir/Vh264i
	@echo "-- DONE --------------------"

open-wave:
	gtkwave dump.vcd &

clean:
	-rm -rf obj_dir *.log *.dmp *.vpd core
	-rm -rf verdiLog novas.conf novas.rc
