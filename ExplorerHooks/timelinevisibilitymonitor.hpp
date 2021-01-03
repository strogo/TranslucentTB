#pragma once
#include "arch.h"
#include <atomic>
#include <windef.h>
#include <wil/com.h>
#include <wil/resource.h>

#include "undoc/explorer.hpp"

class TimelineVisibilityMonitor {
	static std::atomic<bool> s_ThreadRunning;
	static wil::slim_event_manual_reset s_ThreadCleanupDone;
	static HANDLE s_ThreadInfinitePostCleanupWait;
	static UINT s_TimelineNotification;
	static UINT s_GetTimelineStatus;
	static ATOM s_WindowClassAtom;
	static HANDLE s_hThread;
	static wil::com_ptr_nothrow<IMultitaskingViewVisibilityService> s_ViewService;

	static HRESULT LoadViewService() noexcept;

	static DWORD WINAPI ThreadProc(LPVOID lpParameter) noexcept;
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept;

	static void Install(HINSTANCE hInst) noexcept;
	static void Uninstall(HINSTANCE hInst) noexcept;

#ifdef EXPLORERHOOKS_EXPORTS
	friend class MultitaskingViewVisibilitySink;
	friend BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID) noexcept;
#endif
};
