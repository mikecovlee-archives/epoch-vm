#pragma once

#include <unordered_map>
#include <cstdint>
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
        void push_frame();

        void pop_frame();

        // Variable
        size_t add_variable(const string&, const any&);

        void load_variable(size_t);

        void load_variable(const string &);

        void load_variable_dyn(const string &);

        // Immediate Value
        void push_int(types::vm_int);

        void push_uint(types::vm_uint);

        void push_char(types::vm_char);

        void push_bool(types::vm_bool);

        void push_float(types::vm_bool);

        void push_string(types::vm_string);
    };
    class vm_instance_builder final {

    };
}