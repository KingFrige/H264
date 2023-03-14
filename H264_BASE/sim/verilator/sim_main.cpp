// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// Include common routines
#include <verilated.h>

#include <memory>
#include "verilated_vcd_c.h"
#include "verilator.h"

// Include model header, generated from Verilating "top.v"
#include "Vh264i.h"

static uint64_t trace_count = 0;

int main(int argc, char** argv) {
    // See a similar example walkthrough in the verilator manpage.

    // This is intended to be a minimal example.  Before copying this to start a
    // real project, it is better to start with a more complete example,
    // e.g. examples/c_tracing.

    // Construct a VerilatedContext to hold simulation time, etc.
    VerilatedContext* contextp = new VerilatedContext;

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    contextp->commandArgs(argc, argv);


    FILE * vcdfile = NULL;
    uint64_t start = 0;
    vcdfile = fopen("dump.vcd", "w");
    if (!vcdfile) {
      std::cerr << "Unable to open dump.vcd for VCD write\n";
      return 1;
    }
    Verilated::traceEverOn(true); // Verilator must compute traced signals
    std::unique_ptr<VerilatedVcdFILE> vcdfd(new VerilatedVcdFILE(vcdfile));
    std::unique_ptr<VerilatedVcdC> tfp(new VerilatedVcdC(vcdfd.get()));
    if (vcdfile) {
      tfp.get();
      tfp->open("");
    }

    // Construct the Verilated model, from Vh264i.h generated from Verilating "top.v"
    Vh264i* top = new Vh264i{contextp};

    int async_reset_cycles = 2;
    int sync_reset_cycles = 10;
    bool done_reset;

    while (trace_count < 100000) {

      top->clk = 0;
      top->reset_n = trace_count < async_reset_cycles*2 ? trace_count % 2 : trace_count < async_reset_cycles*2 + sync_reset_cycles;
      done_reset = !top->reset_n;
      top->eval();
      bool dump = tfp && trace_count >= start;
      if (dump)
        tfp->dump(static_cast<vluint64_t>(trace_count * 2));

      top->clk = trace_count >= async_reset_cycles*2;
      top->ai_data = 36;
      top->ai_we = 1;
      top->eval();
      if (dump)
        tfp->dump(static_cast<vluint64_t>(trace_count * 2 + 1));

      trace_count++;
    }

    if (tfp)
      tfp->close();
    if (vcdfile)
      fclose(vcdfile);

    // Final model cleanup
    top->final();

    // Destroy model
    delete top;

    // Return good completion status
    return 0;
}
