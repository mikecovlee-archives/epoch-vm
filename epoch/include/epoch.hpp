#pragma once

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <string>
#include "any.hpp"

namespace epoch
{
    template<typename KeyT, typename ValT> using map = std::unordered_map<KeyT, ValT>;
    using string = std::string;
    using size_t = std::size_t;
    namespace types {
        using vm_int = std::int32_t;
        using vm_uint = std::uint32_t;
        using vm_char = std::int8_t;
        using vm_bool = std::uint8_t;
        using vm_float = double;
        using vm_string = std::string;
    }
    class vm_instance final {
        struct stack_frame {
            map<string, size_t>  local_variables;
            stack_type<any>      local_slots;
            stack_type<any_view> local_stack;
            stack_frame(size_t local_s, size_t frame_s) : local_slots(local_s), local_stack(frame_s) {}
        };
        stack_type<stack_frame> stack;
        size_t stack_size, local_size, frame_size;
    public:
        vm_instance() = delete;
        vm_instance(const vm_instance&) = delete;
        vm_instance(size_t stack_s, size_t local_s, size_t frame_s) : stack(stack_s), stack_size(stack_s), local_size(local_s), frame_size(frame_s) {}
        
        // Stack Frame
        inline void push_frame();

        inline void pop_frame();

        // Variable
        size_t add_variable(const string &, const any &);

        void set_variable_field(map<string, size_t>, std::vector<any>);

        inline void load_variable(size_t);

        inline void load_variable(const string &);

        void load_variable_dyn(const string &);

        // Immediate Value
        inline void push_int(types::vm_int);

        inline void push_uint(types::vm_uint);

        inline void push_char(types::vm_char);

        inline void push_bool(types::vm_bool);

        inline void push_float(types::vm_float);

        inline void push_string(types::vm_string);

        // Calculate
        void cal_add();

        void cal_sub();

        void cal_mul();

        void cal_div();
    };
    class vm_instance_builder final {

    };
}