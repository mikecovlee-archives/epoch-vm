#pragma once

#include <string>
#include <cstdint>
#include <cstddef>

namespace epoch {
	namespace types {
		using vm_int = long;
		using vm_float = double;
		using vm_bool = bool;
		using vm_char = signed char;
		using vm_string = std::string;
	}
	class instrument_base 
	{
	public:
		instrument_base() = default;
		instrument_base(const instrument_base &) = default;
		virtual ~instrument_base() = default;
		virtual void exec() = 0;
	};
	class vm_instance final {
		
	};
} // namespace epoch
