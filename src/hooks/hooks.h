#pragma once


#include "common/PCH.h"


namespace Hooks {
	class BoundItemMonitor {
	public:
		static void Install();
		static RE::EffectSetting* GetBaseObject(RE::ActiveEffect* a_effect);
		inline static REL::Relocation<decltype(&GetBaseObject)> _getBaseObject;
	};
}