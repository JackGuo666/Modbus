#include "Modbusindex.h"
#include "devicestudio\main_module.h"
#include "devicestudio\imainwindow.h"
#include "devicestudio\treewidget.h"
#include "devicestudio\treeitem_def.h"
#include "config_data.h"

#include <qstandarditemmodel.h>

#pragma execution_character_set("utf-8")

using namespace std;

Modbusindex::Modbusindex(QWidget *parent, IMainModule *pMainModule)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    Q_ASSERT(pMainModule);
    if (pMainModule)
    {
        m_pMainModule = pMainModule;
    }

    //ui.tableWidget->clear();
    ui.tableWidget->setColumnCount(2);
    QStringList headers;
    headers << "Client编号" << "跳转";
    ui.tableWidget->setHorizontalHeaderLabels(headers);

    ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

    connect(ui.tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(Slot_station_name_modify(int, int)));
}


void Modbusindex::on_pushButton_clicked()
{
    int rowcount = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(rowcount);

    QPushButton* Goto = new QPushButton(". . .");
    connect(Goto, SIGNAL(clicked()), this, SLOT(clicked_goto()));



    CModbusClientData* pData = new CModbusClientData();
    m_vecClient.append(pData);


    ui.tableWidget->setCellWidget(rowcount, 1, Goto);

    QTableWidgetItem* Item0 = new QTableWidgetItem(QString::number(rowcount));
    ui.tableWidget->setItem(rowcount, 0, Item0);

    auto i = reinterpret_cast<std::uintptr_t>(pData);

    //整数转换成指针
    //void* p = (void*)i;
    ui.tableWidget->item(rowcount, 0)->setData(Qt::UserRole, i);
}

void Modbusindex::on_pushButton_2_clicked()
{
    int currentrow = ui.tableWidget->currentRow();
    if (currentrow < 0)
    {
        return;
    }

    //
    std::uintptr_t i = ui.tableWidget->item(currentrow, 0)->data(Qt::UserRole).toUInt();
    void* p = (void*)i;



    for (QVector<CModbusClientData *>::iterator iter = m_vecClient.begin(); iter != m_vecClient.end();)
    {
        if ((*iter) == p)
        {
            delete (*iter);
            m_vecClient.erase(iter);//删除该行
        }
        else
        {
            iter++;
        }


    }

    ui.tableWidget->removeRow(currentrow);

}

void Modbusindex::clicked_goto(void)
{
    QPushButton* senderObj = qobject_cast<QPushButton*>(sender());
    if (senderObj == nullptr)
    {
        return;
    }
    QModelIndex idx = ui.tableWidget->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
    int row = idx.row();
    // 其他响应信息......
       //
    std::uintptr_t i = ui.tableWidget->item(row, 0)->data(Qt::UserRole).toUInt();
    void* p = (void*)i;

    QtWidgetsClass Csettings;
    Csettings.SetModbusClientPoiner(p);
    Csettings.exec();
}

#include <qdebug.h>
void forEach(QStandardItemModel* model, int nItemRole, QStandardItem **item, QModelIndex parent = QModelIndex()) {
    for (int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);
        int nRole = model->data(index, Qt::UserRole).toInt();
        if (nRole == nItemRole)
        {
            QStandardItem* curItem = model->itemFromIndex(index);
            qDebug() << curItem->text();
            *item = curItem;
            return;
        }
        //qDebug() << name;
        // here is your applicable code
        if (model->hasChildren(index)) {
            forEach(model, nItemRole, item, index);
            int a = 5;
            a = 6;
        }
    }
}

void Modbusindex::Slot_station_name_modify(int nRow, int nCol)
{
    
    return;
    auto pItem = ui.tableWidget->item(nRow, nCol);
    if (pItem)
    {
        QString strName = pItem->text();
        auto pMainWindow = m_pMainModule->GetMainWindow();
        QStandardItemModel *model = (QStandardItemModel*)pMainWindow->GetLeftTree()->model();
        QStandardItem* item = nullptr;
        forEach(model, TREE_MODBUS_CLIENT_ITEM, &item);
        Q_ASSERT(item);
        if (item)
        {
            QStandardItem* pSlave = new QStandardItem(tr("strName"));
            pSlave->setData(TREE_MODBUS_SLAVE_ITEM, Qt::UserRole);
            pSlave->setIcon(QIcon("./ini/icons/analog.png"));
            item->appendRow(pSlave);
        }
    }
}
