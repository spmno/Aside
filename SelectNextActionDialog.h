#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_selectNextAction.h"

class SelectNextActionDialog : public QDialog
{
	Q_OBJECT
public:
	SelectNextActionDialog(QWidget* parent = 0);
	~SelectNextActionDialog(void);
private:
	Ui::selectActionDialog ui;
private slots:
	void saveNextAction();
};

