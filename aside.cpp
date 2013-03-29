#include "aside.h"
#include <windows.h>
#include <QtWidgets/qmessagebox.h>
#include <QtCore/QDebug>
#include <QtSQL/QSqlError>
#include "CollectDialog.h"
#include "CollectInfoDialog.h"
#include "ProjectAddDialog.h"
#include "DB/DBManager.h"
#include "ValueContainer.h"

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
	ValueContainer::getInstance().collectHotkeyId = registerId;
	GlobalDeleteAtom(registerId);

	collectionModel_ = new QSqlTableModel;
	collectionModel_->setTable("collection");
	collectionModel_->select();

	ui.collectionList_->setModel(collectionModel_);

	projectTreeModel_ = new QStandardItemModel;
	ui.projectTreeView->setModel(projectTreeModel_);
	updateProjectTree();
}

Aside::~Aside()
{
	ATOM registerId = GlobalAddAtom(L"collectgtd");
	UnregisterHotKey((HWND)winId(), registerId);
	GlobalDeleteAtom(registerId);
	delete collectionModel_;
}

void Aside::collectThing()
{
	CollectInfoDialog collectInfoDialog;
	collectInfoDialog.exec();
}

void Aside::addProject()
{
	ProjectAddDialog projectAddDialog;
	projectAddDialog.exec();
}

void Aside::disposeCollection(QModelIndex index)
{
	QAbstractItemModel *model = ui.collectionList_->model();
	
	qDebug() << index.row();
	qDebug() << ui.collectionList_->currentIndex().row();
	//QString content = ui.collectionList_->
	if (collectionModel_->removeRow(index.row())) {
		if (model->submit()) {
			collectionModel_->database().commit();
			collectionModel_->select();
		}
	} else {
		qDebug() << "row" << collectionModel_->lastError();
	}
}

void Aside::updateProjectTree()
{
	QVector<QString> projectNameContainer;
	DBManager& dbManager = DBManager::getInstance();
	if (!dbManager.getProjects(projectNameContainer)) {
		return ;
	}

	for (int i = 0; i < projectNameContainer.size(); ++i) {
		QStandardItem* projectItem = new QStandardItem(projectNameContainer[i]);
		projectTreeModel_->setItem(i, projectItem);
		QVector<QString> actionNameContainer;
		if (!dbManager.getProjectActions(projectNameContainer[i], actionNameContainer)) {
			continue;
		}
		for (int j = 0; j < actionNameContainer.size(); ++j) {
			QStandardItem* actionItem = new QStandardItem(actionNameContainer[i]);
			projectItem->setChild(j, actionItem);
		}
	}
}