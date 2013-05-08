#pragma once
#include <QtSql/qsqlquerymodel.h>

class CheckBoxModel : public QSqlQueryModel
{
	Q_OBJECT
public:
	CheckBoxModel(QObject* parent = 0);
	~CheckBoxModel(void);
	Qt::ItemFlags flags(const QModelIndex& index) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	//bool setData(const QModelIndex& index, const QVariant& value, int role=Qt::EditRole);
private:
	int checkColumn_;
	QVector<bool> checkContainer_;
};

