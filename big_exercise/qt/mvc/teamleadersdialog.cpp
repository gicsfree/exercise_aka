#include <QtGui>

#include "teamleadersdialog.h"

TeamLeadersDialog::TeamLeadersDialog(const QStringList &leaders, QWidget *parent)
  :QDialog(parent)
{
    model = new QStringListModel(this);
    model->setStringList(leaders);

    listView = new QListView;
    listView->setModel(model);
    listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    insertButton = new QPushButton(tr("&Insert"));
    deleteButton = new QPushButton(tr("&Delete"));

    okButton = new QPushButton(tr("OK"));
    okButton->setDefault(true);

    cancelButton = new QPushButton(tr("Cancel"));

    connect(insertButton, SIGNAL(clicked()), this, SLOT(insert()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(del()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addStretch(); // 控件之间增加间隔
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listView);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Team Leaders"));
}

QStringList TeamLeadersDialog::leaders() const
{
    return model->stringList();
}

void TeamLeadersDialog::insert()
{
    int row = listView->currentIndex().row();
    model->insertRows(row, 1);

    QModelIndex index = model->index(row);
//    model->setData(index, "James Brown");
#if 1
    listView->setCurrentIndex(index);
    listView->edit(index);
#endif
}

void TeamLeadersDialog::del()
{
    model->removeRows(listView->currentIndex().row(), 1);
}
