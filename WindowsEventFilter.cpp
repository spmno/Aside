#include "WindowsEventFilter.h"
#include <Windows.h>
#include "CollectDialog.h"

WindowsEventFilter::WindowsEventFilter(void)
{
}


WindowsEventFilter::~WindowsEventFilter(void)
{
}

bool WindowsEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = static_cast<MSG *>(message);
	if (msg->message == WM_HOTKEY) {
		CollectDialog collectDialog;
		collectDialog.exec();
	}

	return false;
}