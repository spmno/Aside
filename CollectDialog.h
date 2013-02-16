#pragma once
#include <QtWidgets\qdialog.h>
#include "ui_collect.h"

class CollectDialog : public QDialog
{
	Q_OBJECT
public:
	CollectDialog(QWidget* parent = 0);
	~CollectDialog(void);
private:
	Ui::Collect ui;
private slots:
	void saveCollection();
};

