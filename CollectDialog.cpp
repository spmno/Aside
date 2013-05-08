#include "CollectDialog.h"
#include <QtWidgets\qmessagebox.h>
#include "DB\DBManager.h"

CollectDialog::CollectDialog(QWidget* parent)
{
	ui.setupUi(this);

}


CollectDialog::~CollectDialog(void)
{

}

void CollectDialog::saveCollection()
{
	if (DBManager::getInstance().saveCollection(ui.collectionEdit->toPlainText())) {

		done(0);
	} else {
		QMessageBox::critical(NULL, ("error"), ("sql save collection error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
	}
	emit updateMainWindow();
}

void CollectDialog::nextCollection()
{
	if (DBManager::getInstance().saveCollection(ui.collectionEdit->toPlainText())) {
		ui.collectionEdit->clear();
	} else {
		QMessageBox::critical(NULL, ("error"), ("sql save collection error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
	}
	emit updateMainWindow();
}