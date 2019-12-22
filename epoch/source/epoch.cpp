#include "../include/epoch.hpp"

namespace epoch {
    void vm_instance::push_frame()
    {
        stack.push(local_size, frame_size);
    }

    void vm_instance::pop_frame()
    {
        stack.pop_no_return();
    }

    size_t vm_instance::add_variable(const string &id, const any &val)
    {
        stack.top().local_slots.push(val);
        size_t idx = stack.top().local_slots.size() - 1;
        stack.top().local_variables.emplace(id, idx);
        return idx;
    }

    void vm_instance::load_variable(size_t idx)
    {
        stack.top().local_stack.push(stack.top().local_slots.at(idx));
    }

    void vm_instance::load_variable(const string &id)
    {
        load_variable(stack.top().local_variables.at(id));
    }

    void vm_instance::load_variable_dyn(const string &id)
    {
        for (auto &frame:stack)
            if (frame.local_variables.count(id) > 0)
                stack.top().local_stack.push(frame.local_slots.at(frame.local_variables.at(id)));
        throw_ex<runtime_error>("VM: Dynamically load variable failed.");
    }
}
