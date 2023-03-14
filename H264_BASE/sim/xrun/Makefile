all: sim

elab:
	xrun -64bit -sv -log_ncelab elab.log -log_ncvlog vlog.log -elaborate -access +rwc \
		-notimingchecks -nospecify -timescale 1ns/1ps -f flist

sim: elab
	xrun -log_ncsim sim.log -64bit -R -q -run -unbuffered -stacksize 2048000 -nontcglitch \
		-notimingchecks -nospecify -input dump.tcl

open-wave:
	verdi -sv -f flist -top a_tb -ssf dump.fsdb &

clean:
	rm -rf xrun.key xrun.history *.log xcelium.d *.fsdb verdiLog novas.conf novas.rc
