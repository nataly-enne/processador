#include <systemc.h>
#include "Memory.hpp"
SC_MODULE (ula) {
        Memory *memory;
        sc_in<sc_uint<32>> reg_a, reg_b, dest;

        sc_in<sc_uint<4>> op_code;

        sc_uint<32> data_a, data_b, res;
        sc_out<bool> n;
        sc_out<bool> z;

        sc_out<bool> operation;
        sc_out<sc_uint<32>> data_mem_in;
        sc_in<sc_uint<32>> data_mem_out;
        sc_out<sc_uint<32> > addr;

        /**
         * Ula com 12 operações 
        */

        void do_operation() {
            data_a = reg_a.read();
            data_b = reg_b.read();

            switch (op_code.read()) {
                case 1:
                    res = data_a + data_b;
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | Sum >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 2:
                    res = data_a - data_b;
                    if (data_a > data_b) {
                        n.write(true);
                    } else {
                        n.write(false);
                        if (res == 0) z.write(true);
                    }
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | Sub >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 3:
                    res = data_a && data_b;
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | AND >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 4:
                    res = data_a || data_b;
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | OR >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 5:
                    res = not (data_a || data_b);
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | XOR >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 6:
                    res = 0;
                    if (data_a > data_b) {
                        n.write(true);
                    } else if (data_a < data_b) {
                        n.write(false);
                    } else {
                        z.write(true);;
                        res = 1;
                    }
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | Comp >> (op1: "
                    << data_a << ") (op2: " << data_b << ") (res: " << res << ")" << endl;
                    break;
                case 7:
                    res = not (data_a);
                    memory->att_registers(dest.read(), res);
                    cout << "@" << sc_time_stamp() << " | Not >> (op: "
                    << data_a << ") (res: " << res << ")" << endl;
                    break;
                case 8:
                    cout << "@" << sc_time_stamp() << " | J >> (goto: "
                    << data_a << ")" << endl;
                    break;
                case 9: 
                    if (n == true)
                        cout << "@" << sc_time_stamp() << " | Jn >> (goto: "
                        << data_a << ")" << endl;
                    else
                        cout << "@" << sc_time_stamp() << " | Jn >> FALSE CONDITION" << endl;
                    break;
                case 10:
                    if (z == true)
                        cout << "@" << sc_time_stamp() << " | Jz >> (goto: "
                        << data_a << ")" << endl;
                    else
                        cout << "@" << sc_time_stamp() << " | Jz >> FALSE CONDITION" << endl;
                    break;
                case 11:
                    operation.write(false);
                    addr.write(data_b);
                    //data_mem_out.read();
                    cout << "@" << sc_time_stamp() << " | LW >> (read data: "
                    << data_a << ") reg to write: (" << data_b << ")" << endl;
                    break;
                case 12:
                    operation.write(true);
                    data_mem_in.write(data_a);
                    addr.write(data_b);
                    cout << "@" << sc_time_stamp() << " | SW >> (write data: "
                    << data_a << ") addres to write: (" << data_b << ")" << endl;
                    break;
                default:
                    std::cout << op_code.read() << std::endl;
                    break;
            }
        }

        SC_CTOR(ula) {
            SC_METHOD(do_operation);
            sensitive << reg_a << reg_b << op_code;
        }

        void load_memory(Memory *m){
            memory = m;
        }
};

