all: sim

elab:
	vcs +v2k -sverilog +vcs+lic+wait -full64 -debug_pp \
		+warn=noCDNYI,noIPDW,noILLGO,noTMR,noPHNE,noIRIID-W \
		-Mupdate +notimingcheck +nospecify \
		-fsdb \
		-f flist

sim: elab
	./simv -ucli -i dump.tcl

open-wave:
	verdi -sv -f flist -top a_tb -ssf dump.fsdb &

clean:
	rm -rf simv simv.daidir *.fsdb *.log ucli.key csrc/
