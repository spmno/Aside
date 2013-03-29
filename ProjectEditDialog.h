#pragma once
#include <QtWidgets\qdialog.h>

#include "treemodel.h"

class ProjectEditDialog : public QDialog
{
public:
	ProjectEditDialog(QWidget* parent = 0);
	~ProjectEditDialog(void);
private:
	//Ui::projectAddDialog ui;
	//TreeModel projectTreeModel_;
};

