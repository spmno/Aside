#pragma once
#include <QtWidgets\qdialog.h>
#include "ui_projectAdd.h"
#include <QtGui\qstandarditemmodel.h>

class ProjectAddDialog : public QDialog
{
	Q_OBJECT
public:
	ProjectAddDialog(QWidget* parent = 0);
	~ProjectAddDialog(void);
private:
	Ui::projectAddDialog ui;
private slots:
	void addProject();
	void addAction();
private:
	void updateTreeView();
	QStandardItemModel* treeViewModel_;
};

