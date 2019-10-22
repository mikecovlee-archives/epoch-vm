#pragma once

#include <string>
#include <cstdint>
#include <cstddef>

#include "utility.hpp"

namespace epoch {
	namespace types {
		using vm_int = long;
		using vm_float = double;
		using vm_bool = bool;
		using vm_char = signed char;
		using vm_string = std::string;
	}
	class stack final {
	public:
		enum class frame_type : std::uint8_t {
			null, data, scope
		};
	private:
		struct frame_header {
			frame_type type = frame_type::null;
			size_t size = 0;
		};
		byte_t *ss = nullptr, *sp = nullptr, *sl = nullptr;

	};
	class instrument_base {
	public:
		instrument_base() = default;
		instrument_base(const instrument_base &) = default;
		virtual ~instrument_base() = default;
		virtual void exec() = 0;
	};
	class vm_instance final {

	};
} // namespace epoch
