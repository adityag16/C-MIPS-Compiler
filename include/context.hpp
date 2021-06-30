#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <unordered_map>
#include <iostream>
#include <vector>

class Context;

typedef Context* ContextPtr;

class Context{
    private:
        int indent;
        std::vector<std::string> global_vars;
        bool main = 0;
        bool func = 0;

    public:
        Context(){indent = 0;};

        void make_indent(std::ostream &dst) {
            for(int i = 0; i < indent; i++) {
                dst << "    ";
            }
        };

        void enter_scope() {
            indent++;
        };

        void exit_scope() {
            indent--;
        };

        void add_variable(std::string new_var) {
            global_vars.push_back(new_var);
        };

        std::vector<std::string> get_global_vars() {
            return global_vars;
        };

        int get_indent(){
            return indent;
        };

        void set_main() {
            //std::cout << "setting main" << std::endl;
            main = 1;
        }

        void set_func() {
            if(func == 0){
                //std::cout << "entering function" << std::endl;
                func = 1;
            }
            else{
                //std::cout << "exiting function" << std::endl;
                func = 0;
            }
        }

        bool has_main(){
            return main;
        }

        bool is_func(){
            return func;
        }
    
};

#endif
