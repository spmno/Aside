#pragma once
#include <QtWidgets/qdialog.h>
#include <QtGui/QMouseEvent>
#include "ui_tomato.h"

class TomatoTimeDialog : public QDialog
{
	Q_OBJECT
public:
	TomatoTimeDialog(QWidget* parent = 0);
	~TomatoTimeDialog(void);
private:
	Ui::tomatoDialog ui;
    QPoint last;
private slots:
	void updateTime();
};
