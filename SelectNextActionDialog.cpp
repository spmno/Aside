#include "SelectNextActionDialog.h"
#include "CheckBoxModel.h"
#include "DB/DBManager.h"
#include <QtWidgets/qmessagebox.h>

SelectNextActionDialog::SelectNextActionDialog(QWidget* parent)
{
	ui.setupUi(this);
	//CheckBoxModel* checkModel = new CheckBoxModel();
	QSqlQueryModel* checkModel = new QSqlQueryModel;
	checkModel->setQuery("select * from action");
	ui.listView->setModel(checkModel);
	ui.listView->setModelColumn(1);
	ui.listView->setSelectionMode(QAbstractItemView::MultiSelection);
	ui.listView->show();
}


SelectNextActionDialog::~SelectNextActionDialog(void)
{
}
#include <Windows.h>
void SelectNextActionDialog::saveNextAction()
{
	QItemSelectionModel* selectionModel = ui.listView->selectionModel();
	QModelIndexList selectIndexs = selectionModel->selectedIndexes();
	
	for (auto actionIndex : selectIndexs) {
	
		//QString actionContent = selectionModel->model()->data(actionIndex).toString();
		//OutputDebugStringA(actionContent.toLatin1());
		QModelIndex idIndex = selectionModel->model()->index(actionIndex.row(), 0);
		int actionId = selectionModel->model()->data(idIndex).toInt();
		if (!DBManager::getInstance().saveNextAction(actionId)) {
			QMessageBox::critical(this, "error", "save next action failed");
		} else {
			done(0);
		}
	}
}
