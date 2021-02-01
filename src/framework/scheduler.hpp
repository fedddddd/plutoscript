#pragma once

namespace scheduler
{
	void chai_schedule(const chaiscript::Boxed_Value& callback, int ms);

	void schedule(const std::function<bool()>& callback, const std::chrono::milliseconds delay = 0ms);

	void loop(const std::function<void()>& callback, const std::chrono::milliseconds delay = 0ms);
	void once(const std::function<void()>& callback, const std::chrono::milliseconds delay = 0ms);

	void init();
}
