#include "aside.h"
#include <QtWidgets/QApplication>
#include "WindowsEventFilter.h"
#include "DB/DBManager.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WindowsEventFilter *filter = new WindowsEventFilter;
	a.installNativeEventFilter(filter);
	if (!DBManager::getInstance().init()) {
		return -1;
	}
	Aside w;
	w.show();
	
	int result = a.exec();

	delete filter;

	return result;
}
