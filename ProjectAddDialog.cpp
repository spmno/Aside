#include "ProjectAddDialog.h"
#include <QtWidgets\qmessagebox.h>
#include "DB\DBManager.h"

ProjectAddDialog::ProjectAddDialog(QWidget* parent)
{
	ui.setupUi(this);
	treeViewModel_ = new QStandardItemModel();
	ui.projectTreeView->setModel(treeViewModel_);
}


ProjectAddDialog::~ProjectAddDialog(void)
{
	delete treeViewModel_;
}

void ProjectAddDialog::addProject()
{
	try {
		DBManager::getInstance().saveProject(ui.projectNameEdit->text());
	} catch(int) {
		QMessageBox::critical(NULL, ("error"), ("project is exist"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
	}
	
	updateTreeView();
}

void ProjectAddDialog::addAction()
{
	QString projectName = ui.projectNameEdit->text();
	if (projectName == "") {
		QMessageBox::critical(NULL, ("error"), ("please input the projectName first"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
	}
	DBManager& dbManager = DBManager::getInstance();
	int projectId = dbManager.getProjectIndex(projectName);
	dbManager.saveAction(ui.actionLineEdit->text(), projectId);
	updateTreeView();
}

void ProjectAddDialog::updateTreeView()
{
	DBManager& dbManager = DBManager::getInstance();
	QString& projectName = ui.projectNameEdit->text();
	treeViewModel_->clear();

	
	QStandardItem* item = new QStandardItem(projectName);
	treeViewModel_->setItem(0, item);

	QVector<QString> actionData;
	if (!dbManager.getProjectActions(projectName, actionData)) {
		return ;
	}


	for (int i = 0; i < actionData.size(); ++i) {
		QStandardItem* item = new QStandardItem(actionData[i]);
		treeViewModel_->setItem(i+1, item);
	}

}