#include "DragStandItemModel.h"
#include <QtCore/qmimedata.h>
#include <QtCore/qdebug.h>

DragStandItemModel::DragStandItemModel(void)
{
}


DragStandItemModel::~DragStandItemModel(void)
{
}

QMimeData* DragStandItemModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	QByteArray encodedData;

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach (QModelIndex index, indexes) {
		if (index.isValid()) {
			QString text = data(index, Qt::DisplayRole).toString();
			qDebug() << "tree view item data: " << text << "row: " << index.row() << "column: " << index.column();
			stream << text;
		}
	}

	mimeData->setData("application/x-qasidedatalist", encodedData);
	return mimeData;
}