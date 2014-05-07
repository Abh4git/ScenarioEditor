#ifndef COMACT_H
#define COMACT_H
#include <qstring.h>
#include <qpoint.h>
//! ComAction Class
	/*!
		Responsibility: Represents Communication Actions
	*/
class ComAction
{
public:
	//! Constructor
	/*!
		\param id as string
		\param type as int
		\param assocSceneActId as int
		\param sourceAddress as string	
		\param destAddress as string	
		\param repeatTimes as int	
		\param timeToNext as int	
	*/
	ComAction(QString id,int type,int assocSceneActId,QString sourceAddress, QString destAddress, int repeatTimes, int timeToNext )
	{
		m_id=id;
		m_type=type;
		m_sourceAddress=sourceAddress;
		m_assocSceneActId=assocSceneActId;
		m_destAddress=destAddress;
		m_timesRepeat=repeatTimes;
		m_timeToNext=timeToNext;
	}
	//! Destructor
	~ComAction(void)
	{
	}
	//! getIdentifier
	/*!
		Return the identifier as string
	*/
	QString getIdentifier()
	{
		return m_id;
	}
	//! getObjectType
	/*!
		Return the object type as int
	*/
	int getObjectType()
	{
		return m_type;
	}
	//! getSourceAddress
	/*!
		Return the source address as string
	*/
	QString getSourceAddress()
	{
		return m_sourceAddress;
	}
	//! getDestAddress
	/*!
		Return the dest address as string
	*/
	QString getDestAddress()
	{
		return m_destAddress;
	}
	//! getNoofTimesToRepeat
	/*!
		Return the no of times to repeat as int
	*/
	int getNoofTimesToRepeat()
	{
		return m_timesRepeat;
	}
	//! waitTimeBeforeNext
	/*!
		Return the time before next action happens
	*/
	int waitTimeBeforeNext()
	{
		return m_timeToNext;
	}
private:
	QString m_id;
	int m_type;
	QString m_sourceAddress;
	QString m_destAddress;
	int m_assocSceneActId;
	int m_timesRepeat;
	int m_timeToNext;
	
};

#endif