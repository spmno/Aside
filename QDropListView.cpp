#include "QDropListView.h"
#include <QtGui/QDropEvent>
#include <QtCore/qmimedata.h>
#include <QtCore/qdebug.h>
#include <QtGui/qstandarditemmodel.h>
#include <QtWidgets/qmessagebox.h>
#include "DB/DBManager.h"

QDropListView::QDropListView(QWidget *parent)
{

}


QDropListView::~QDropListView(void)
{
}

void QDropListView::dropEvent(QDropEvent *event) {
    /*
	ListWidget *source =
            qobject_cast<ListWidget *>(event->source());
    if (source && source != this) {        
        QIcon icon = event->mimeData()->imageData().value<QIcon>();
        QString text = event->mimeData()->text(); 
        addItem(new QListWidgetItem(icon, text));
        
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
	*/
	//event->accept();
	
	QString format = QLatin1String("application/x-qasidedatalist");
	if (event->mimeData()->hasFormat(format)) {
		QByteArray itemsData = event->mimeData()->data(format);
		QDataStream dataStream(&itemsData,QIODevice::ReadOnly);

		QString idString;
		QString actionContent;

		dataStream >> actionContent >> idString ;
		qDebug() << actionContent << "and" << idString;
		if (!DBManager::getInstance().saveNextAction(idString.toInt())) {
			QMessageBox::critical(NULL, "error", "save next action failed");
		}
	}

}

void QDropListView::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void QDropListView::dragMoveEvent(QDragMoveEvent* event)
{
	event->accept();
}