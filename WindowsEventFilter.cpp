#include "WindowsEventFilter.h"
#include <Windows.h>
#include "CollectDialog.h"
#include "ValueContainer.h"
#include "WindowsManager.h"


WindowsEventFilter::WindowsEventFilter(void)
{
}


WindowsEventFilter::~WindowsEventFilter(void)
{
}

bool WindowsEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
	MSG* msg = static_cast<MSG *>(message);
	if ((msg->message == WM_HOTKEY)) {// && (msg->wParam == ValueContainer::getInstance().collectHotkeyId)) {
		if (msg->wParam == ValueContainer::getInstance().collectHotkeyId) {
			CollectDialog collectDialog;
			QObject::connect((QObject*)(&collectDialog), SIGNAL(updateMainWindow()), (QObject*)(WindowsManager::getInstance().mainWindow),SLOT(updateCollection()));
			collectDialog.exec();
			QObject::disconnect((QObject*)(&collectDialog), SIGNAL(updateMainWindow()), (QObject*)(WindowsManager::getInstance().mainWindow),SLOT(updateCollection()));
			return true;
		}

	}

	return false;
}