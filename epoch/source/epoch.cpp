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

    void vm_instance::set_variable_field(map<string, size_t> field, std::vector<any> data)
    {
        stack.top().local_variables = std::move(field);
        for (auto &it:data)
            stack.top().local_slots.push(std::move(it));
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

    void vm_instance::push_int(types::vm_int val)
    {
        stack.top().local_stack.push(val);
    }

    void vm_instance::push_uint(types::vm_uint val)
    {
        stack.top().local_stack.push(val);
    }

    void vm_instance::push_char(types::vm_char val)
    {
        stack.top().local_stack.push(val);
    }

    void vm_instance::push_bool(types::vm_bool val)
    {
        stack.top().local_stack.push(val);
    }

    void vm_instance::push_float(types::vm_float val)
    {
        stack.top().local_stack.push(val);
    }

    void vm_instance::push_string(types::vm_string val)
    {
        stack.top().local_stack.push(std::move(val));
    }

    void vm_instance::cal_add()
    {
        any_view rhs = stack.top().local_stack.pop();
        any_view lhs = stack.top().local_stack.pop();
        if (lhs.get().data_type() == typeid(types::vm_int))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() + rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() + rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() + rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_uint))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() + rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() + rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() + rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_float))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() + rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() + rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() + rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else
            throw_ex<runtime_error>("VM: add numerical values failed.");
    }

    void vm_instance::cal_sub()
    {
        any_view rhs = stack.top().local_stack.pop();
        any_view lhs = stack.top().local_stack.pop();
        if (lhs.get().data_type() == typeid(types::vm_int))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() - rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() - rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() - rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_uint))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() - rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() - rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() - rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_float))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() - rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() - rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() - rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else
            throw_ex<runtime_error>("VM: add numerical values failed.");
    }

    void vm_instance::cal_mul()
    {
        any_view rhs = stack.top().local_stack.pop();
        any_view lhs = stack.top().local_stack.pop();
        if (lhs.get().data_type() == typeid(types::vm_int))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() * rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() * rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() * rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_uint))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() * rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() * rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() * rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_float))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() * rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() * rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() * rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else
            throw_ex<runtime_error>("VM: add numerical values failed.");
    }

    void vm_instance::cal_div()
    {
        any_view rhs = stack.top().local_stack.pop();
        any_view lhs = stack.top().local_stack.pop();
        if (lhs.get().data_type() == typeid(types::vm_int))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() / rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() / rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_int>() / rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_uint))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() / rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() / rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_uint>() / rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else if (lhs.get().data_type() == typeid(types::vm_float))
        {
            if (rhs.get().data_type() == typeid(types::vm_int))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() / rhs.get().get<types::vm_int>());
            else if (rhs.get().data_type() == typeid(types::vm_uint))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() / rhs.get().get<types::vm_uint>());
            else if (rhs.get().data_type() == typeid(types::vm_float))
                stack.top().local_stack.push(lhs.get().get<types::vm_float>() / rhs.get().get<types::vm_float>());
            else
                throw_ex<runtime_error>("VM: add numerical values failed.");
        } else
            throw_ex<runtime_error>("VM: add numerical values failed.");
    }
}
