#include "CollectInfoDialog.h"
#include <QtSql\qsqlquerymodel.h>

CollectInfoDialog::CollectInfoDialog(QWidget* parent)
{
	ui.setupUi(this);
	QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM collection");
    model->setHeaderData(0, Qt::Horizontal, "name");
    model->setHeaderData(1, Qt::Horizontal, "logtime");
	ui.tableView->horizontalHeader()->setStretchLastSection(true);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setModel(model);
}


CollectInfoDialog::~CollectInfoDialog(void)
{
}
