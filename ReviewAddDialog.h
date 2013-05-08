#pragma once
#include <QtWidgets/qdialog.h>
#include "ui_reviewAdd.h"

class ReviewAddDialog : public QDialog
{
	Q_OBJECT
public:
	ReviewAddDialog(QWidget* parent = 0);
	~ReviewAddDialog(void);
private:
	Ui::reviewDialog ui;
private slots:
	void saveReview();
};

