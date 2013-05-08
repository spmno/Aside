#include "ReviewAddDialog.h"
#include "DB/DBManager.h"
#include <QtWidgets/qmessagebox.h>
ReviewAddDialog::ReviewAddDialog(QWidget* parent)
{
	ui.setupUi(this);
}


ReviewAddDialog::~ReviewAddDialog(void)
{

}

void ReviewAddDialog::saveReview()
{
	if (DBManager::getInstance().saveReview(ui.plainTextEdit->toPlainText())){
		done(0);
	} else {
		QMessageBox::critical(NULL, ("error"), ("sql save review error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
	}
}
