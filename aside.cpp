#include "aside.h"
#include <windows.h>
#include <QtWidgets/qmessagebox.h>
#include <QtCore/QDebug>
#include <QtSQL/QSqlError>

#include "CollectDialog.h"
#include "CollectInfoDialog.h"
#include "ProjectAddDialog.h"
#include "SelectNextActionDialog.h"
#include "ReviewAddDialog.h"
#include "DB/DBManager.h"
#include "ValueContainer.h"
#include "WindowsManager.h"


Aside::Aside(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	WindowsManager::getInstance().mainWindow = this;
	
	ATOM registerId = GlobalAddAtom(L"collectgtd");
	if (!RegisterHotKey((HWND)winId(), registerId, MOD_WIN, 'G')) {
		QMessageBox::StandardButton rb = 
			QMessageBox::critical(NULL, tr("error"), tr("shortcut error"), QMessageBox::Yes|QMessageBox::No, QMessageBox::Yes);
		if (rb == QMessageBox::No) {
			ExitProcess(0);
		}
	}
	ValueContainer::getInstance().collectHotkeyId = registerId;
	GlobalDeleteAtom(registerId);

	collectionModel_ = new QSqlTableModel;
	collectionModel_->setTable("collection");
	collectionModel_->select();
	
	ui.collectionList_->setModel(collectionModel_);
	ui.collectionList_->setModelColumn(1);

	projectTreeModel_ = new DragStandItemModel;
	ui.projectTreeView->setModel(projectTreeModel_);
	updateProjectTree();

	QSqlQueryModel* nextActionModel = new QSqlQueryModel;
	nextActionModel->setQuery("select * from nextaction");
	ui.nextActionList_->setModel(nextActionModel);
	ui.nextActionList_->setModelColumn(1);
	ui.nextActionList_->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.nextActionList_->show();

	QObject::connect(ui.nextActionList_, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showListMenu(const QPoint&)));


	createAction_();
	createTrayIcon_();
	systemTrayIcon_->show();



}

Aside::~Aside()
{
	ATOM registerId = GlobalAddAtom(L"collectgtd");
	UnregisterHotKey((HWND)winId(), registerId);
	GlobalDeleteAtom(registerId);
	delete collectionModel_;
}

void Aside::collectThing()
{
	CollectInfoDialog collectInfoDialog;
	collectInfoDialog.exec();
}

void Aside::addProject()
{
	ProjectAddDialog projectAddDialog;
	projectAddDialog.exec();
}

void Aside::disposeCollection(QModelIndex index)
{
	QAbstractItemModel *model = ui.collectionList_->model();
	
	qDebug() << index.row();
	qDebug() << ui.collectionList_->currentIndex().row();
	//QString content = ui.collectionList_->
	if (collectionModel_->removeRow(index.row())) {
		if (model->submit()) {
			collectionModel_->database().commit();
			collectionModel_->select();
		}
	} else {
		qDebug() << "row" << collectionModel_->lastError();
	}
}

void Aside::updateProjectTree()
{
	QVector<QString> projectNameContainer;
	DBManager& dbManager = DBManager::getInstance();
	if (!dbManager.getProjects(projectNameContainer)) {
		return ;
	}
		
	projectTreeModel_->setColumnCount(2);
	for (int i = 0; i < projectNameContainer.size(); ++i) {
		QStandardItem* projectItem = new QStandardItem(projectNameContainer[i]);
		projectTreeModel_->setItem(i, projectItem);
		QVector<AsideAction> actionNameContainer;
		if (!dbManager.getProjectActions(projectNameContainer[i], actionNameContainer)) {
			continue;
		}
		projectItem->setColumnCount(2);
		for (int j = 0; j < actionNameContainer.size(); ++j) {
			QStandardItem* actionItem = new QStandardItem(actionNameContainer[j].actionContent);
			
			QStandardItem* idItem = new QStandardItem(QString::number(actionNameContainer[j].actionID, 10));
			//actionItem->setColumnCount(2);			
		
			projectItem->setChild(j, 0, actionItem);
			projectItem->setChild(j, 1, idItem);
		}
	}
}

void Aside::updateCollection()
{
	collectionModel_->select();
}

void Aside::createAction_()
{
	minimumAction_ = new QAction(("Mi&n"), this);
	connect(minimumAction_, SIGNAL(triggered()), this, SLOT(hide()));
	maximumAction_ = new QAction(("Ma&x"), this);
	connect(maximumAction_, SIGNAL(triggered()), this, SLOT(showMaximized()));
	tomatoAction_ = new QAction(tr("tomato"),  ui.nextActionList_);
	connect(tomatoAction_, SIGNAL(triggered()), this, SLOT(startTomatoTime()));
}

void Aside::createTrayIcon_()
{
	trayIconMenu_ = new QMenu(this);
	trayIconMenu_->addAction(minimumAction_);
	trayIconMenu_->addAction(maximumAction_);
	systemTrayIcon_ = new QSystemTrayIcon(this);
	systemTrayIcon_->setIcon(QIcon("IMG/aside.ico"));
	systemTrayIcon_->setContextMenu(trayIconMenu_);
}

void Aside::addCollection()
{
	CollectDialog collectDialog;
	QObject::connect((QObject*)(&collectDialog), SIGNAL(updateMainWindow()), (QObject*)(WindowsManager::getInstance().mainWindow),SLOT(updateCollection()));
	collectDialog.exec();
	QObject::disconnect((QObject*)(&collectDialog), SIGNAL(updateMainWindow()), (QObject*)(WindowsManager::getInstance().mainWindow),SLOT(updateCollection()));		
}

void Aside::selectNextAction()
{
	SelectNextActionDialog selectDialog;
	selectDialog.exec();
}

void Aside::addReview()
{
	ReviewAddDialog reviewDialog;
	reviewDialog.exec();
}

void Aside::showReview(const QDate& date)
{
	QString reviewContent;
	if (DBManager::getInstance().getReview(date, reviewContent)) {
		QMessageBox::information(this, "review", reviewContent);
	} else {
		QMessageBox::information(this, "no review this day", reviewContent);
	}
}

void Aside::showListMenu(const QPoint& point)
{
	QMenu contextMenu(tr("Context menu"), ui.nextActionList_);
	contextMenu.addAction(tomatoAction_);
	contextMenu.exec(ui.nextActionList_->mapToGlobal(point));
}

void Aside::startTomatoTime()
{
	tomatoDialog_ = new TomatoTimeDialog;
	tomatoDialog_->setWindowFlags(Qt::FramelessWindowHint);
	tomatoDialog_->move(0, 0);
	tomatoDialog_->show();
}