#ifndef CONTEXT_MIPS_HPP
#define CONTEXT_MIPS_HPP

#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

class Context_MIPS;

typedef Context_MIPS* ContextPtr_MIPS;


class Context_MIPS{
    private:
        int label_count = 0;
        bool global_ = 1;
        bool globl_func = 0;
        bool globl_func2 = 0;
        bool func = 0;
        bool int_dec = 0;
        bool op = 0;
        bool ass = 0;
        bool ret = 0;
        bool param = 0;
        bool arg = 0;
        bool array = 0;
        bool array_access = 0;
        bool case_ = 0;
        bool switch_ = 0;
        bool default_ = 0;

    public:
        Context_MIPS(){};

        void set_global() {
          global_ = 1;
        }

        void unset_global() {
          global_ = 0;
        }

        bool is_global(){
            return global_;
        }

        void set_globl_func() {
            if(globl_func == 0){
                globl_func = 1;
            }
            else{
                globl_func = 0;
            }
        }

        bool is_globl_func(){
            return globl_func;
        }

        void set_globl_func2() {
            if(globl_func2 == 0){
                globl_func2 = 1;
            }
            else{
                globl_func2 = 0;
            }
        }

        bool is_globl_func2(){
            return globl_func2;
        }

        void set_int_dec() {
          if(int_dec == 0){
              int_dec = 1;
          }
          else{
              int_dec = 0;
          }
        }

        bool is_int_dec(){
            return int_dec;
        }

        void set_func() {
            if(func == 0){
                func = 1;
            }
            else{
                func = 0;
            }
        }

        bool is_func(){
            return func;
        }

        void set_op() {
          op = 1;
        }

        void unset_op() {
          op = 0;
        }

        bool is_op(){
            return op;
        }

        void set_ass() {
          if(ass == 0){
              ass = 1;
          }
          else{
              ass = 0;
          }
        }

        bool is_ass(){
            return ass;
        }

        void set_ret() {
          if(ret == 0){
              ret = 1;
          }
          else{
              ret = 0;
          }
        }

        bool is_ret(){
            return ret;
        }

        void set_param() {
          if(param == 0){
              param = 1;
          }
          else{
              param = 0;
          }
        }

        bool is_param(){
            return param;
        }

        void set_arg() {
          if(arg == 0){
              arg = 1;
          }
          else{
              arg = 0;
          }
        }

        bool is_arg(){
            return arg;
        }

        bool is_array(){
            return array;
        }

        void set_array() {
          if(array == 0){
              array = 1;
          }
          else{
              array = 0;
          }
        }

        bool is_array_access(){
            return array_access;
        }

        void set_array_access() {
          if(array_access == 0){
              array_access = 1;
          }
          else{
              array_access = 0;
          }
        }

        bool is_case(){
            return case_;
        }

        void set_case() {
            case_ = 1;
        }

        void unset_case() {
            case_ = 0;
        }

        bool is_switch(){
            return switch_;
        }

        void set_switch() {
            switch_ = 1;
        }

        void unset_switch() {
            switch_ = 0;
        }

        bool is_default(){
            return default_;
        }

        void set_default() {
            default_ = 1;
        }

        void unset_default() {
            default_ = 0;
        }


        std::string make_Label(const std::string& base) {
            return base + std::to_string(label_count++); 
        }

        std::unordered_map<std::string, int> bindings;

        int offset = -8;

        int arg_reg = 4;

        std::vector<std::string> scope_start_labels;

        std::vector<std::string> scope_end_labels;
        
        std::vector<std::string> case_start_labels;

        std::vector<int> case_number; 

        int enum_count = -1;

};



#endif
