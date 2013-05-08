#pragma once
#include <QtSql\QtSql>
#include <QtCore\qvector.h>
#include "AsideAction.h"
class DBManager
{
public:
	static DBManager& getInstance()
	{
		static DBManager instance;
		return instance;
	}
	~DBManager(void);	
	bool init();
	bool saveCollection(const QString& content);
	bool deleteCollection(const QString& content);
	bool saveProject(const QString& content);
	bool deleteProject(const QString& content);
	int  getProjectIndex(const QString& projectName);
	bool saveAction(const QString& content, int projectId = 0);
	bool deleteAction(const QString& content);
	bool getProjectActions(const QString& projectName, QVector<AsideAction>& actionContainer);
	bool getProjects(QVector<QString>& projectContainer);
	bool hasNextAction(const int actionId);
	bool saveNextAction(const int actionId);
	bool deleteNextAction(const int actionId);
	bool saveReview(const QString& content);
	bool getReview(const QDate& date, QString& content);
	int getActionId(const QString& content);
private:
	explicit DBManager(void);	
	QSqlDatabase db_;
};
