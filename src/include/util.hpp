#pragma once

#include <memory>
#include <functional>
template <typename MsgType>
void generic_callback(void* lf_handle, const MsgType& msg) {
    auto msg_copy = new MsgType(msg);
		instant_t stamp = SEC(msg.header().stamp().sec()) + NSEC(msg.header().stamp().nsec());
		interval_t delay = stamp - lf_time_physical();
		if (delay < 0) {
			delay = 0;
		}
    lf_schedule_value(lf_handle, delay, static_cast<void*>(msg_copy), 1);
}

// This templated function can be passed to lf_set_destructor so that
// the C-runtimes token management uses `delete` instead of the default `free`.
// This is necessary if the tokens were created with `new`.
template<typename T>
void cpp_delete(void * value) {
		delete static_cast<T*>(value);
}

