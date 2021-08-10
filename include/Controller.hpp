#include <systemc.h>

SC_MODULE (controller) {
    sc_in_clk clk;
    sc_out<sc_uint<32> > counter_out;
    sc_in<bool> enable;

    sc_in < sc_uint<32> > reg_a;
    sc_in <sc_uint<4>> op_code;
    sc_uint<32>	count;

    sc_in<bool> n;
    sc_in<bool> z;

    /**
     * Incrementa os endereços das intruções e ao ler e executar todas realiza o fim da aplicação
    */
    void increment () {
        while (true) {
            wait();
            if (enable.read() == true) {
                // verifica se é uma instrução de jump. caso seja faz o devido salto
                if (op_code.read() == 8 or op_code.read() == 9 or op_code.read() == 10) {
                    if((op_code.read() == 9 and n.read() == true) or (op_code.read() == 10 and z.read() == true)){
                        count = reg_a.read();
                    } else if(op_code.read() == 9 or op_code.read() == 10){
                        count +=1;
                    }else{
                        count = reg_a.read();
                    }
                } else {
                    count += 1;
                }
                counter_out.write(count);
            } else sc_stop();
        }

    }
    void print() {
        while (true) {
            wait();
            cout << "@" << sc_time_stamp() << " :: Counter Value " << counter_out.read() <<endl;
        }
    }

    SC_CTOR(controller) {
        std::cout << "starting processor..." << std::endl;
        cout << "@" << sc_time_stamp() << " :: Counter Value 0" << endl;

        SC_CTHREAD(increment, clk.pos());
        SC_THREAD(print);

        sensitive << counter_out;
    }
};