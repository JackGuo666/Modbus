#include "QtWidgetsClass.h"
#include "config_data.h"
#include "devicestudio\treeitem_def.h"

#pragma execution_character_set("utf-8")

QtWidgetsClass::QtWidgetsClass(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.tableWidget->clear();
	ui.tableWidget->setColumnCount(9);


	QStringList headers;
	headers << "ID" << "名称"<<"IP地址" << "从站地址" << "响应超时（ms）" << "允许的超时次数" << "重连间隔" << "复位变量" << "通道";
	ui.tableWidget->setHorizontalHeaderLabels(headers);

	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
	ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

}


void QtWidgetsClass::on_pushButton_clicked()
{
	int Timeout = ui.lineEdit->text().toInt();
	int TCPClint_settingsrowcount = ui.tableWidget->rowCount();
	ui.tableWidget->insertRow(TCPClint_settingsrowcount);
	QPushButton* channel = new QPushButton(". . .");
	connect(channel, SIGNAL(clicked()), SLOT(clicked_channel()));
	ui.tableWidget->setCellWidget(TCPClint_settingsrowcount, 8, channel);

	QTableWidgetItem* Item0 = new QTableWidgetItem(QString::number(TCPClint_settingsrowcount));
	QTableWidgetItem* Item1 = new QTableWidgetItem(QString("设备")+QString::number(TCPClint_settingsrowcount));
	QTableWidgetItem* Item2 = new QTableWidgetItem();
	QTableWidgetItem* Item3 = new QTableWidgetItem();
	QTableWidgetItem* Item4 = new QTableWidgetItem(QString::number(Timeout));
	QTableWidgetItem* Item5 = new QTableWidgetItem();
	QTableWidgetItem* Item6 = new QTableWidgetItem();
	QTableWidgetItem* Item7 = new QTableWidgetItem();

	ui.tableWidget->setItem(TCPClint_settingsrowcount, 0, Item0);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 1, Item1);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 2, Item2);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 3, Item3);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 4, Item4);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 5, Item5);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 6, Item6);
	ui.tableWidget->setItem(TCPClint_settingsrowcount, 7, Item7);


	//判断设备号是否重复
	   // connect(ui.tableWidget, SIGNAL(QTableWidget::cellChanged(int,int)), this, SLOT(slotItemChanged(QTableWidgetItem*)));
	QString a = ui.tableWidget->item(TCPClint_settingsrowcount, 1)->text();
	QString b = ui.tableWidget->item(TCPClint_settingsrowcount, 4)->text();
	for (int i = 0; i < TCPClint_settingsrowcount; i++)
	{
		if (a == ui.tableWidget->item(i, 0)->text())
		{
			QString a1 = b;
			int row = a1.toInt();
			//row += 1;
			ui.tableWidget->setItem(TCPClint_settingsrowcount, 0, new QTableWidgetItem(QString("设备") + QString::number(row)));

		}
		if (b == ui.tableWidget->item(i, 1)->text())
		{
			QString a2 = b;
			int row1 = a2.toInt();
			// row1 += 1;
			ui.tableWidget->setItem(TCPClint_settingsrowcount, 1, new QTableWidgetItem(QString::number(row1 + 1)));

		}
	}

	CDeviceData* pData = new CDeviceData();
	pData->m_unID = ui.tableWidget->item(TCPClint_settingsrowcount, ID)->text().toUInt();
	pData->m_strDeviceName = ui.tableWidget->item(TCPClint_settingsrowcount, NAME)->text();
	pData->m_strIP = ui.tableWidget->item(TCPClint_settingsrowcount, IPADDR)->text();
	pData->m_ucSlaveAddr = ui.tableWidget->item(TCPClint_settingsrowcount, SLAVEADDR)->text().toUInt();
	pData->m_unResponseTime = ui.tableWidget->item(TCPClint_settingsrowcount, REPONSETIME)->text().toUInt();
	pData->m_unTimeoutCount = ui.tableWidget->item(TCPClint_settingsrowcount, TIMEOUTCOUNT)->text().toUInt();
	pData->m_unReconnectInterval = ui.tableWidget->item(TCPClint_settingsrowcount, RECONNECTINTERVAL)->text().toUInt();
	pData->m_strResetVariable = ui.tableWidget->item(TCPClint_settingsrowcount, RESETVAR)->text().toUInt();

	auto& devVec = m_pData->getDevData();
	devVec.append(pData);

	auto value = reinterpret_cast<std::uintptr_t>(pData);
	ui.tableWidget->item(TCPClint_settingsrowcount, RESETVAR)->setData(Qt::UserRole, value);

	//CS.CchannelID(ui.tableWidget->item(ui.tableWidget->currentRow(), 1)->text());
}


void QtWidgetsClass::on_pushButton_2_clicked()
{

	int currentrow = ui.tableWidget->currentRow();
	if (currentrow < 0)
	{
		return;
	}

	auto value = ui.tableWidget->item(currentrow, RESETVAR)->text().toInt();
	CChannelData* pData = (CChannelData*)(value);

	ui.tableWidget->removeRow(currentrow);



}

void QtWidgetsClass::on_pushButton_3_clicked()
{
	m_pData->m_strNetPort = ui.comboBox->currentText();
	m_pData->m_uResponseTime = ui.lineEdit->text().toUShort();
	if (ui.radioButton->isChecked())
	{
		m_pData->m_bTcp = CModbusClientData::TCP_COMM;
	}
	else
	{
		m_pData->m_bTcp = CModbusClientData::UDP_COMM;
	}

	auto &devData = m_pData->getDevData();
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		//CDeviceData* pData = new CDeviceData();
		//通道的值在复位变量的userrole上
		auto pData = (CDeviceData *)ui.tableWidget->item(i, RESETVAR)->data(Qt::UserRole).toInt();

		pData->m_unID = ui.tableWidget->item(i, 0)->text().toUInt();
		pData->m_strDeviceName = ui.tableWidget->item(i, 1)->text();
		pData->m_strIP = ui.tableWidget->item(i, 2)->text();
		pData->m_ucSlaveAddr = ui.tableWidget->item(i, 3)->text().toUInt(); 
		pData->m_unResponseTime = ui.tableWidget->item(i, 4)->text().toUInt();
		pData->m_unTimeoutCount = ui.tableWidget->item(i, 5)->text().toUInt();
		pData->m_unReconnectInterval = ui.tableWidget->item(i, 6)->text().toUInt();
		pData->m_strResetVariable = ui.tableWidget->item(i, 7)->text().toUInt();


	}

	accept();
}

void QtWidgetsClass::on_pushButton_4_clicked()
{

	reject();
}

void QtWidgetsClass::clicked_channel(void)
{
	QString channelnumber = ui.tableWidget->item(ui.tableWidget->currentRow(), 0)->text();

	auto value = ui.tableWidget->item(ui.tableWidget->currentRow(), RESETVAR)->data(Qt::UserRole).toInt();
	CDeviceData* pData = (CDeviceData*)value;

	Channelsettings cs;
	cs.CchannelID(channelnumber);
	cs.setDeviceData(pData);
	//cs.show();
	cs.exec();

}


QtWidgetsClass::~QtWidgetsClass()
{
}

void QtWidgetsClass::SetModbusClientPoiner(void* p)
{
	m_pData = (CModbusClientData*)p;

	if (m_pData->m_strNetPort.isEmpty())
	{
		//为空，第一次初始化
		int nIndex = ui.comboBox->currentIndex();
		if (nIndex >= 0)
		{
			m_pData->m_strNetPort = ui.comboBox->currentText();
		}
	}
	else
	{
		if (m_pData->m_strNetPort != ui.comboBox->currentText())
		{
			ui.comboBox->setCurrentText(m_pData->m_strNetPort);
		}
	}

	ui.lineEdit->setText(QString("%1").arg(m_pData->m_uResponseTime));
	if (m_pData->m_bTcp == CModbusClientData::TCP_COMM)
	{
		ui.radioButton->setChecked(true);
	}
	else
	{
		ui.radioButton_2->setChecked(true);
	}

	//初始化界面
	auto& devVec = m_pData->getDevData();
	for (int i = 0; i < devVec.count(); i++)
	{
		int nRow = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(nRow);
		QPushButton* channel = new QPushButton(". . .");
		connect(channel, SIGNAL(clicked()), SLOT(clicked_channel()));
		ui.tableWidget->setCellWidget(nRow, 8, channel);

		QTableWidgetItem* Item0 = new QTableWidgetItem(QString::number(devVec[i]->m_unID));
		QTableWidgetItem* Item1 = new QTableWidgetItem(devVec[i]->m_strDeviceName);
		QTableWidgetItem* Item2 = new QTableWidgetItem(devVec[i]->m_strIP);
		QTableWidgetItem* Item3 = new QTableWidgetItem(QString::number(devVec[i]->m_ucSlaveAddr));
		QTableWidgetItem* Item4 = new QTableWidgetItem(QString::number(devVec[i]->m_unResponseTime));
		QTableWidgetItem* Item5 = new QTableWidgetItem(QString::number(devVec[i]->m_unTimeoutCount));
		QTableWidgetItem* Item6 = new QTableWidgetItem(QString::number(devVec[i]->m_unReconnectInterval));
		QTableWidgetItem* Item7 = new QTableWidgetItem(devVec[i]->m_strResetVariable);
		auto value = reinterpret_cast<std::uintptr_t>(devVec[i]);
		Item7->setData(Qt::UserRole, value);

		ui.tableWidget->setItem(i, 0, Item0);
		ui.tableWidget->setItem(i, 1, Item1);
		ui.tableWidget->setItem(i, 2, Item2);
		ui.tableWidget->setItem(i, 3, Item3);
		ui.tableWidget->setItem(i, 4, Item4);
		ui.tableWidget->setItem(i, 5, Item5);
		ui.tableWidget->setItem(i, 6, Item6);
		ui.tableWidget->setItem(i, 7, Item7);
	}



}
