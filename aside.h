#ifndef ASIDE_H
#define ASIDE_H

#include <QtWidgets/QMainWindow>
#include <QtSql/qsqlquerymodel.h>
#include <QtSql/QSqlTableModel>
#include <QtWidgets/qsystemtrayicon.h>
#include <QtWidgets/qmenu.h>
#include "DragStandItemModel.h"
#include "TomatoTimeDialog.h"

#include "ui_aside.h"

class Aside : public QMainWindow
{
	Q_OBJECT

public:
	Aside(QWidget *parent = 0);
	~Aside();
	
private:
	Ui::AsideClass ui;
	QSqlTableModel* collectionModel_;
	DragStandItemModel* projectTreeModel_;
	QSystemTrayIcon* systemTrayIcon_;
	QMenu* trayIconMenu_;
	QAction* minimumAction_;
	QAction* maximumAction_;
	QAction* tomatoAction_;
	TomatoTimeDialog* tomatoDialog_;
	void createAction_();
	void createTrayIcon_();
	
private slots:
	void collectThing();
	void disposeCollection(QModelIndex index);
	void addProject();
	void addCollection();
	void updateCollection();
	void updateProjectTree();
	void selectNextAction();
	void addReview();
	void showReview(const QDate& date);
	void showListMenu(const QPoint& point);
	void startTomatoTime();
};

#endif // ASIDE_H
