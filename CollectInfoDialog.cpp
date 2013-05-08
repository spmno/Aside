#include "CollectInfoDialog.h"
#include <QtSql\qsqlquerymodel.h>

CollectInfoDialog::CollectInfoDialog(QWidget* parent)
{
	ui.setupUi(this);
	QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM collection");
	 model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, "name");
    model->setHeaderData(2, Qt::Horizontal, "logtime");
	ui.tableView->horizontalHeader()->setStretchLastSection(true);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setModel(model);
}


CollectInfoDialog::~CollectInfoDialog(void)
{
}
