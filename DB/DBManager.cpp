#include "DBManager.h"
#include <QtSql\QtSql>
#include <QtWidgets\qmessagebox.h>
#include <QtWidgets\qtableview.h>
#include <Windows.h>



//db relation define
const QString DB_NAME = "aside.db";
#define COLLECTION_TABE_NAME "collection"
#define ACTION_TABLE_NAME "action"
#define PROJECT_TABLE_NAME "project"
#define REVIEW_TABLE_NAME "review"
#define NEXT_ACTION_TABLE_NAME "nextaction"

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

	// create collection table
	QStringList tableList = db_.tables();
	if (!tableList.contains(COLLECTION_TABE_NAME)) {
		if (!query.exec("create table collection (id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(80), logtime TIMESTAMP default (datetime('now', 'localtime')));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create content table error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}

	//create project table
	if (!tableList.contains(PROJECT_TABLE_NAME)) {
		if (!query.exec("create table project (id INTEGER PRIMARY KEY AUTOINCREMENT, name varchar(80));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create project table error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}
	
	// create action table
	if (!tableList.contains(ACTION_TABLE_NAME)) {
		if (!query.exec("create table action (id INTEGER PRIMARY KEY AUTOINCREMENT, content varchar(80), state integer, project_id integer, foreign key(project_id) references project(id));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create action table error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}

	//create next action table
	if (!tableList.contains(NEXT_ACTION_TABLE_NAME)) {
		if (!query.exec("create table nextaction (id INTEGER PRIMARY KEY AUTOINCREMENT, action_id integer, foreign key(action_id) references action(id));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create next action table error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}
	// create review table
	if (!tableList.contains(REVIEW_TABLE_NAME)) {
		if (!query.exec("create table review (id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT, reviewdate date default (date('now')));")) {
			QMessageBox::critical(NULL, ("error"), ("sql create review table error"),  QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes); 
			return false;
		}
	}
	return true;
}


bool DBManager::saveCollection(const QString& content)
{
	QString sqlContent = QString("insert into collection(name) values('%1');").arg(content);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}


bool DBManager::deleteCollection(const QString& content)
{
	QString sqlContent = QString("delete from collection where name = ('%1');").arg(content);
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::saveProject(const QString& content)
{
	if (getProjectIndex(content) != -1) {
		throw -1;
	}
	QString sqlContent = QString("insert into project(name) values('%1');").arg(content);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::deleteProject(const QString& content)
{
	QString sqlContent = QString("delete from project where name = ('%1');").arg(content);
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

int DBManager::getProjectIndex(const QString& projectName)
{
	QString sqlContent = QString("select id from project where name = ('%1');").arg(projectName);
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		if (query.next()) {
			return query.value(0).toInt();
		} else {
			return -1;
		}
	} else { 
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::saveAction(const QString& content, int projectId)
{
	QString sqlContent = QString("insert into action(content, state, project_id) values('%1', '%2', '%3');").arg(content).arg(0).arg(projectId);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::getProjectActions(const QString& projectName, QVector<AsideAction>& actionContainer)
{
	int projectId = getProjectIndex(projectName);
	QString sqlContent = QString("select id, content from action where project_id = ('%1');").arg(projectId);
	QSqlQuery query;
	bool findFlag = false;
	if (query.exec(sqlContent)) {
		while (query.next()) {
			findFlag = true;
			AsideAction asideAction;
			asideAction.actionID = query.value(0).toInt();
			asideAction.actionContent = query.value(1).toString();
			actionContainer.push_back(asideAction);
		}
		return findFlag;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::getProjects(QVector<QString>& projectContainer) 
{
	QString sqlContent = QString("select name from project;");
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		while (query.next()) {
			projectContainer.push_back(query.value(0).toString());
		}
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::hasNextAction(const int actionId)
{
	QString sqlContent = QString("select * from nextaction where action_id = ('%1');").arg(actionId);
	qDebug() << sqlContent;
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		if (query.next()) {
			return true;
		} else {
			return false;
		}
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::saveNextAction(const int actionId)
{
	if (hasNextAction(actionId)) {
		return true;
	}
	QString sqlContent = QString("insert into nextaction(action_id) values('%1');").arg(actionId);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	qDebug() << (sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::deleteNextAction(const int actionId)
{
	QString sqlContent = QString("delete from nextaction where id = ('%1');").arg(actionId);
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::saveReview(const QString& content)
{
	QString sqlContent = QString("insert into review(content) values('%1');").arg(content);
	//sqlContent.sprintf("insert into collection values %s", content.toLatin1());
	//OutputDebugStringA(content.toLatin1());
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		return true;
	} else {
		qDebug() << query.lastError();
		return false;
	}
}

bool DBManager::getReview(const QDate& date, QString& content)
{
	QString sqlContent = QString("select content from review where reviewdate = date('%1');").arg(date.toString(Qt::ISODate));
	OutputDebugStringA(sqlContent.toLatin1());
	QSqlQuery query;
	if (query.exec(sqlContent)) {
		if (query.next()) {
			content = query.value(0).toString();
			return true;
		} else {
			return false;
		}
		
	} else {
		qDebug() << query.lastError();
		return false;
	}

}

int DBManager::getActionId(const QString& content)
{
	return -1;	
}