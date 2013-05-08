#pragma once
#include <QtGui/qstandarditemmodel.h>

class DragStandItemModel : public QStandardItemModel
{
	Q_OBJECT
public:
	DragStandItemModel(void);
	~DragStandItemModel(void);
	QMimeData* mimeData(const QModelIndexList &indexes) const;
};

