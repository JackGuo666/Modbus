#ifndef dddd_config_data
#define dddd_config_data


#include <qstring.h>
#include <qvector.h>

class  CBaseData
{
public:
	CBaseData();
	virtual ~CBaseData();
public:
	virtual void Save() = 0;

	virtual void SetModifyFlag(bool bFlag) = 0;

	virtual bool GetModifyFlag() = 0;
public:


protected:
	bool m_bModifyFlag;
};

class CChannelData : public CBaseData
{
public:
	CChannelData();
	~CChannelData();

	virtual void Save()
	{

	}

	virtual void SetModifyFlag(bool bFlag)
	{

	}

	virtual bool GetModifyFlag()
	{
		return true;
	}



public:
	quint32 m_unID;
	QString m_strDeviceName;
	quint8 m_ucMsgType;
	quint32 m_unPollingTime;
	quint32 m_unReadOffsetAddr;
	quint32 m_unReadLength;
	quint32 m_unWriteOffsetAddr;
	quint32 m_unWriteLength;
	QString m_strNote;
};

class CDeviceData : public CBaseData
{
public:
	CDeviceData();
	~CDeviceData();
	
	virtual void Save()
	{

	}

	virtual void SetModifyFlag(bool bFlag)
	{
		return;
	}

	virtual bool GetModifyFlag()
	{
		return true;
	}

	QVector<CChannelData*>& getChannelVec();


public:
	quint32 m_unID;
	QString m_strDeviceName;
	QString m_strIP;
	quint32 m_ucSlaveAddr;
	quint32 m_unResponseTime;
	quint32 m_unTimeoutCount;
	quint32 m_unReconnectInterval; //链路没连接上，没隔几秒连接一次
	QString m_strResetVariable;

	QVector<CChannelData*> m_vecChannel;
private:

};




class CModbusClientData : public CBaseData
{
public:
	enum Comm{TCP_COMM, UDP_COMM};
public:
	CModbusClientData();
	~CModbusClientData();

	virtual void Save()
	{

	}

	virtual void SetModifyFlag(bool bFlag)
	{

	}

	virtual bool GetModifyFlag()
	{
		return true;
	}

	void SetClientName(const QString& strName);


	QVector<CDeviceData*>& getDevData()
	{
		return m_vecDevice;
	}

public:
	QString m_strNetPort; //网口1、网口2、网口3
	quint16 m_uResponseTime; //发送查询帧，m_nReposTime没有回复帧
	bool m_bTcp;	//0-TCP     1-UDP 	  

private:
	QString m_strName;	//modbus客户端名称，唯一

	QVector<CDeviceData *> m_vecDevice;
};


#endif
