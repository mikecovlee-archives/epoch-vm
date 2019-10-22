#pragma once

#include <string>
#include <cstdint>
#include <cstddef>

#include "utility.hpp"
#include "memory.hpp"
#include "any.hpp"

namespace epoch {
	namespace types {
		using vm_int = long;
		using vm_float = double;
		using vm_bool = bool;
		using vm_char = signed char;
		using vm_string = std::string;
	}
	class vm_stack final {
	public:
		enum class frame_type : std::uint8_t {
			null, data, scope
		};
	private:
		struct stack_frame {
			stack_type<any> field;
			event_type frame_pop;
			~stack_frame()
			{
				frame_pop.touch(this);
			}
		};
		stack_type<stack_frame> m_stack;
	public:
		vm_stack()
		{
			push_scope();
		}
		vm_stack(const vm_stack&) = delete;
		~vm_stack() = default;
		void push_data(any val)
		{
			m_stack.top().field.push(std::move(val));
		}
		any& top_data()
		{
			return m_stack.top().field.top();
		}
		const any& top_data() const
		{
			return m_stack.top().field.top();
		}
		any& access_data(size_t offset)
		{
			return m_stack.top().field.at(offset);
		}
		const any& access_data(size_t offset) const
		{
			return m_stack.top().field.at(offset);
		}
		stack_type<any>& access_field(size_t field)
		{
			return m_stack.at(field).field;
		}
		const stack_type<any>& access_field(size_t field) const
		{
			return m_stack.at(field).field;
		}
		any& access_data_field(size_t field, size_t offset)
		{
			return m_stack.at(field).field.at(offset);
		}
		const any& access_data_field(size_t field, size_t offset) const
		{
			return m_stack.at(field).field.at(offset);
		}
		void pop_data()
		{
			m_stack.top().field.pop_no_return();
		}
		any pop_data_rt()
		{
			return m_stack.top().field.pop();
		}
		void push_scope()
		{
			m_stack.push();
		}
		void pop_scope()
		{
			m_stack.pop();
		}
	};
	class instrument_base {
	public:
		instrument_base() = default;
		instrument_base(const instrument_base &) = default;
		virtual ~instrument_base() = default;
		virtual void exec() = 0;
	};
	class vm_instance final {
		any_view register_lhs, register_rhs;
	};
} // namespace epoch
