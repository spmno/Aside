#ifndef ASIDE_H
#define ASIDE_H

#include <QtWidgets/QMainWindow>
#include <QtSql\qsqlquerymodel.h>
#include <QtSql/QSqlTableModel>
#include <QtGui\qstandarditemmodel.h>
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
	QStandardItemModel* projectTreeModel_;
	void updateProjectTree();
private slots:
	void collectThing();
	void disposeCollection(QModelIndex index);
	void addProject();
};

#endif // ASIDE_H
