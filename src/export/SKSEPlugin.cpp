#pragma once


#include "hooks/hooks.h"

namespace
{
	void InitializeLog([[maybe_unused]] spdlog::level::level_enum a_level = spdlog::level::info)
	{
	#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	#else
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= std::format("{}.log"sv, Plugin::Name);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
	#endif

		const auto level = a_level;

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(spdlog::level::info);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%t] [%s:%#] %v");
	}
};






extern "C" DLLEXPORT constinit auto SKSEPlugin_Version = []()
	{
		SKSE::PluginVersionData v{};

		v.PluginVersion(Plugin::Version);
		v.PluginName(Plugin::Name);
		v.AuthorName("Original by SeaSparrow - backport by Lucio"sv);
		v.UsesAddressLibrary();



			// v.UsesStructsPost629();		// <--- I'm not sure about 353, I don't have the runtime at all; ***IF*** this works for them, shouldn't stop it
			v.HasNoStructUse();


		return v;
	}();

extern "C" DLLEXPORT bool SKSEAPI
SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = SKSEPlugin_Version.pluginName;
	a_info->version = SKSEPlugin_Version.pluginVersion;

	

	if (a_skse->IsEditor()) {
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_SSE_1_6_317) {		
		stl::report_and_fail("!! You are using a pre-1.6 game runtime, which this version does not support. There is a 1.5.97 version by Styxx, available on this mod's NexusMods page.");
		return false;
	}
	if (ver > SKSE::RUNTIME_SSE_1_6_678) {		
		stl::report_and_fail("!! You are using a 1.6.1130+ game runtime, which this version does not support. You should use the original by Shekhinaga directly.");
		return false;
	}	

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::Name, Plugin::VersionString);

	SKSE::Init(a_skse);
	SKSE::AllocTrampoline(14);

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_SSE_1_6_317) {		
		stl::report_and_fail("!! You are using a pre-1.6 game runtime, which this version does not support. There is a 1.5.97 version by Styxx, available on this mod's NexusMods page.");
		return false;
	}
	if (ver > SKSE::RUNTIME_SSE_1_6_678) {		
		stl::report_and_fail("!! You are using a 1.6.1130+ game runtime, which this version does not support. You should use the original by Shekhinaga directly.");
		return false;
	}	

	Hooks::BoundItemMonitor::Install();
	return true;
}