#include "DBManager.h"
#include <QtSql\QtSql>
#include <QtWidgets\qmessagebox.h>
#include <QtWidgets\qtableview.h>
#include <Windows.h>
const QString DB_NAME = "aside.db";
#define COLLECTION_TABE_NAME "collection"
DBManager::DBManager(void)
{

}


DBManager::~DBManager(void)
{
		
}

bool DBManager::init()
{
	db_ = QSqlDatabase::addDatabase("QSQLITE");
	db_.setDatabaseName(DB_NAME);
	
	if (!db_.open()) {
		QMessageBox::critical(NULL, ("error"), ("sql open error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
		return false;
	}

	QSqlQuery query;

	QStringList tableList = db_.tables();
	if (!tableList.contains(COLLECTION_TABE_NAME)) {
		if (!query.exec("create table collection (name varchar(80), logtime TIMESTAMP default (datetime('now', 'localtime')));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create talbe error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}


	return true;
}


bool DBManager::saveCollection(QString& content)
{
	QString sqlContent = QString("insert into collection values (%1)").arg(content);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	//OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		return false;
	}
}