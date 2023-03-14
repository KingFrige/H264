call fsdbDumpfile {dump.fsdb}
call fsdbDumpvars 0 a_tb {"+skip_cell_instance=1"}
run 1us
