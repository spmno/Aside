#include "TomatoTimeDialog.h"
#include <QtCore/qtimer.h>
#include <QtWidgets/qmessagebox.h>

TomatoTimeDialog::TomatoTimeDialog(QWidget* parent) : displayTime_(25)
{
	ui.setupUi(this);	
	setWindowFlags(Qt::WindowStaysOnTopHint);
	ui.lcdNumber->display(displayTime_);
	tomatoTimer_ = new QTimer;
	connect(tomatoTimer_,SIGNAL(timeout()),this,SLOT(updateTime()));  
    tomatoTimer_->start(1000*60);  
}


TomatoTimeDialog::~TomatoTimeDialog(void)
{
}

void TomatoTimeDialog::mousePressEvent(QMouseEvent *e)
{
    last = e->globalPos();
}

void TomatoTimeDialog::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    last = e->globalPos();
    move(x()+dx, y()+dy);
}

void TomatoTimeDialog::mouseReleaseEvent(QMouseEvent *e)
{
    int dx = e->globalX() - last.x();
    int dy = e->globalY() - last.y();

    move(x()+dx, y()+dy);
}

void TomatoTimeDialog::updateTime()
{
	--displayTime_;
	ui.lcdNumber->display(displayTime_);
	if (displayTime_ == 0) {
		tomatoTimer_->stop();
		delete tomatoTimer_;
		tomatoTimer_ = NULL;
		QMessageBox::information(this, "tomato", "time up");
		done(0);
	}
}