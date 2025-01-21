#pragma once

// This templated function can be passed to lf_set_destructor so that
// the C-runtimes token management uses `delete` instead of the default `free`.
// This is necessary if the tokens were created with `new`.
template<typename T>
void cpp_delete(void * value) {
		delete static_cast<T*>(value);
}