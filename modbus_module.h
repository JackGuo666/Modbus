#pragma once

#include "modbus_global.h"
#include "devicestudio/plugin_module.h"

#include <qmap.h>

class IMainWindow;
class QJsonObject;

class MODBUS_EXPORT CModubsModule : public IPluginModule
{
	Q_OBJECT
public:
	CModubsModule();

	//add by gw in 20200831
	virtual bool SaveToProjectFile(QDomDocument* pXml);

	virtual bool LoadFromProjectFile(QDomDocument* pXml);

	virtual IMainModule* GetMainModule() const
	{
		return m_pMainModule;
	}
	//add end

	virtual void SetLoadDeviceName(const QString& strDeviceName);

	virtual bool SaveToJsonFile(QJsonObject* pJson);
public:
	virtual void Init(IMainModule* pMainModule);
	virtual void UnInit();

private:
	//往树结构中插入数据
	void CreateTreeItem();

private slots:
	void Slot_ClickLeftTreeItem(const QModelIndex& mIndex);
	void Slot_CloseOneTabWidget(int iIndex);
private:
	//模块加载工具
	IMainModule* m_pMainModule;
	//主界面加载控件对象
	IMainWindow* m_pMainWindow;

	//树结构 编号  对应的tab页
	QMap<int, QWidget*> m_MIndexTab;
	//树结构 tab页  编号
	QMap<QWidget*, int> m_MTabIndex;
};
