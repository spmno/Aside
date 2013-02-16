#include "CollectDialog.h"
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
	DBManager::getInstance().saveCollection(ui.collectionEdit->toPlainText());
}