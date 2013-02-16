#ifndef ASIDE_H
#define ASIDE_H

#include <QtWidgets/QMainWindow>
#include "ui_aside.h"

class Aside : public QMainWindow
{
	Q_OBJECT

public:
	Aside(QWidget *parent = 0);
	~Aside();
private:
	Ui::AsideClass ui;
private slots:
	void collectThing();
};

#endif // ASIDE_H
