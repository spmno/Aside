#include "aside.h"
#include <windows.h>
#include <QtWidgets/qmessagebox.h>
#include "CollectDialog.h"
#include "CollectInfoDialog.h"

Aside::Aside(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ATOM registerId = GlobalAddAtom(L"collectgtd");
	if (!RegisterHotKey((HWND)winId(), registerId, MOD_WIN, 'G')) {
		QMessageBox::StandardButton rb = 
			QMessageBox::critical(NULL, tr("error"), tr("shortcut error"), QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::No) {
			ExitProcess(0);
		}
	}
	GlobalDeleteAtom(registerId);
}

Aside::~Aside()
{
	ATOM registerId = GlobalAddAtom(L"collectgtd");
	UnregisterHotKey((HWND)winId(), registerId);
	GlobalDeleteAtom(registerId);
}

void Aside::collectThing()
{
	//CollectDialog collectDialog;
	//collectDialog.exec();
	CollectInfoDialog collectInfoDialog;
	collectInfoDialog.exec();
}
