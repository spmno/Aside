#pragma once
#include <QtSql\QtSql>
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
	bool saveCollection(QString& content);
private:
	explicit DBManager(void);	
	QSqlDatabase db_;
};
