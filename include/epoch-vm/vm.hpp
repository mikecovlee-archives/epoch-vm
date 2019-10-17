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
	using byte_t=uint8_t;
	using size_t=std::size_t;
	template<typename data_t, typename size_t>
	void memcpy_n(data_t *src, data_t *dest, size_t count)
	{
		if (count > 0) {
			byte_t *_src = reinterpret_cast<byte_t *>(src);
			byte_t *_dest = reinterpret_cast<byte_t *>(dest);
			size_t _count = count * sizeof(data_t);
			for (size_t idx = 0; idx < _count; ++idx)
				*(_dest + idx) = *(_src + idx);
		}
	}
} // namespace epoch
