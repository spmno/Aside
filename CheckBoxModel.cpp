#include "CheckBoxModel.h"


CheckBoxModel::CheckBoxModel(QObject* parent) : checkColumn_(0)
{

}


CheckBoxModel::~CheckBoxModel(void)
{

}

Qt::ItemFlags CheckBoxModel::flags(const QModelIndex& index) const 
{
	Qt::ItemFlags flags = QSqlQueryModel::flags(index);
	if (index.column() == checkColumn_) {
		flags |= Qt::ItemIsUserCheckable;
	} 
	return flags;
}

QVariant CheckBoxModel::data(const QModelIndex& index, int role) const
{
	//QModelIndex nextIndex(index.row(), index.column(), index.internalId(), index.model());
	QVariant value = QSqlQueryModel::data(index, role);
	//if (role == Qt::CheckStateRole && index.column() == checkColumn_) {
	//	return Qt::Unchecked;
	//}
	return value;
}

