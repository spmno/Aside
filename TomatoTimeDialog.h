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
    QPoint last;	int displayTime_;	QTimer* tomatoTimer_;protected:    void mousePressEvent(QMouseEvent *e);    void mouseMoveEvent(QMouseEvent *e);    void mouseReleaseEvent(QMouseEvent *e);
private slots:
	void updateTime();
};

