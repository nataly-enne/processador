#include <systemc.h>
#include "Controller.hpp"
#include "Pipeline.hpp"
#include "Ula.hpp"

int sc_main(int argc, char *argv[])
{
    Memory *m = new Memory();
    sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);

    sc_signal<sc_uint<32>> result, data_out, data_in, dest;
    sc_signal<sc_uint<32>> op1, op2;
    sc_signal<sc_uint<4>> op_code;
    sc_signal<sc_uint<32>> addr, addr_memory;
    sc_signal<bool> enable, z, n, operation;

    controller controller("controller");
    controller.clk(clock);
    controller.counter_out(addr);
    controller.enable(enable);
    controller.op_code(op_code);
    controller.reg_a(op1);
    controller.z(z);
    controller.n(n);

    pipeline pipeline("pipeline");
    pipeline.l_memory(m);
    pipeline.reg_a(op1);
    pipeline.reg_b(op2);
    pipeline.op_code(op_code);
    pipeline.clk(clock);
    pipeline.address(addr);
    pipeline.enable(enable);
    pipeline.dest(dest);
    
    
    ula ula("ula");
    ula.load_memory(m);
    ula.dest(dest);
    ula.reg_a(op1);
    ula.reg_b(op2);
    ula.op_code(op_code);
    ula.z(z);
    ula.n(n);
    ula.operation(operation);
    ula.data_mem_in(data_in);
    ula.data_mem_out(data_out);
    ula.addr(addr_memory);
    sc_start(); // Executa até que sc_stop seja encontrado

    m->print();
}
