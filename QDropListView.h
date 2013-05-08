#pragma once
#include <QtWidgets/qlistview.h>

class QDropListView : public QListView
{
public:
	explicit QDropListView(QWidget *parent = 0);
	~QDropListView(void);
protected:
	 void dropEvent(QDropEvent *event);
	 void dragEnterEvent(QDragEnterEvent* event);
	 void dragMoveEvent(QDragMoveEvent* event);
};

