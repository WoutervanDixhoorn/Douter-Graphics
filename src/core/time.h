#pragma once

#include <chrono>

namespace DG {

	class Time {
	public:
		static void Update() 
		{
			TimePoint currentTime = std::chrono::steady_clock::now();
			m_deltaTime = currentTime - m_prevTime;
			m_prevTime = currentTime;
		}

		static float GetDeltaTime()
		{
			return m_deltaTime.count();
		}

	private:
		using TimePoint = std::chrono::steady_clock::time_point;
		using Duration = std::chrono::duration<float>;

		inline static TimePoint m_prevTime = std::chrono::steady_clock::now();
		inline static Duration m_deltaTime = Duration::zero();
	};

}