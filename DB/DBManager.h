#pragma once
#include <QtSql\QtSql>
#include <QtCore\qvector.h>
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
	bool getProjectActions(const QString& projectName, QVector<QString>& actionContainer);
	bool getProjects(QVector<QString>& projectContainer);
private:
	explicit DBManager(void);	
	QSqlDatabase db_;
};
