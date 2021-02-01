#include "stdinc.hpp"

namespace scheduler
{
	namespace
	{
		struct task_t
		{
			int index;
			std::function<bool()> callback;
			std::chrono::milliseconds interval{};
			std::chrono::high_resolution_clock::time_point last_call{};
		};

		std::vector<task_t> tasks;

		void execute()
		{
			for (auto &task : tasks)
			{
				const auto now = std::chrono::high_resolution_clock::now();
				const auto diff = now - task.last_call;

				if (diff < task.interval)
				{
					continue;
				}

				task.last_call = now;

				const auto res = task.callback();

				if (res)
				{
					tasks.erase(tasks.begin() + task.index);
				}
			}
		}

		void server_frame()
		{
			reinterpret_cast<void (*)()>(0x50C1E0)();
			execute();
		}
	}

	void schedule(const std::function<bool()>& callback, const std::chrono::milliseconds delay)
	{
		task_t task;
		task.index = tasks.size();
		task.callback = callback;
		task.interval = delay;
		task.last_call = std::chrono::high_resolution_clock::now();

		tasks.push_back(task);
	}

	void loop(const std::function<void()>& callback, const std::chrono::milliseconds delay)
	{
		schedule([callback]()
		{
			callback();
			return false;
		}, delay);
	}

	void once(const std::function<void()>& callback, const std::chrono::milliseconds delay)
	{
		schedule([callback]()
		{
			callback();
			return true;
		}, delay);
	}

	void chai_schedule(const chaiscript::Boxed_Value& callback, int ms)
	{
		const auto delay = std::chrono::milliseconds(ms);
		const auto _callback = chaiscript::boxed_cast<std::function<void()>>(callback);

		scheduler::once([_callback, ms]() {
			_callback();
		}, delay);
	}

	void init()
	{
		utils::hook::call(0x50CEDC, server_frame);
	}
}