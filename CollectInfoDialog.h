#pragma once
#include <QtWidgets\qdialog.h>
#include "ui_collectionInfo.h"

class CollectInfoDialog :
	public QDialog
{
	Q_OBJECT
public:
	CollectInfoDialog(QWidget* parent = 0);
	~CollectInfoDialog(void);
private:
	Ui::collectionInfo ui;
};

