#ifndef CONNECTORGRAPHICITEM_H
#define CONNECTORGRAPHICITEM_H

#include <QGraphicsPolygonItem>
#include <../BOMGraphicalLibrary/connectorbase.h>
#include <QPainter>
namespace WSIMINST
{
	//! ConnectorGraphicitem class
	/*!
		Responsibility: Create Connectors in Graphics Scene based on source and destination points
	*/
class ConnectorGraphicitem : public QGraphicsPathItem
{
//Q_OBJECT
public:
    //DeviceGraphicItem();

    //
	//! Constructor
	/*!
		\param parent 
		Parent object
	*/
    explicit ConnectorGraphicitem(QGraphicsItem *parent = 0);
    //! Constructor
	/*!
		\param identifier string
		\param typeOfDevice
		\param parent -		Parent object
		\param sourcePt as QPointF
		\param destPt as QPointF
	*/
	explicit ConnectorGraphicitem(QString identifier,ConnectorBase* typeOfDevice=0,QGraphicsItem *parent = 0,QPointF sourcePt=QPointF(0,0), QPointF destPt=QPointF(0,0));
     //! Constructor
	/*!
		\param parent -		Parent object
		\param sourcePt as QPointF
		\param destPt as QPointF
	*/
	explicit ConnectorGraphicitem(QGraphicsItem *parent = 0,QPointF sourcePt=QPointF(0,0), QPointF destPt=QPointF(0,0));
	 //! polygon
	/*!
		Return the graphic - Derived from QGraphicsItem
	*/
    QPolygonF polygon() const
        { return connectGraphic; }
	//! setPosition
	/*!
		\param startX x pos
		\param startY y pos
		Set the position by x and y pos
	*/
    void setPosition(int startX, int startY)
    {
        _startX=startX;
        _startY=startY;

    }
	//! SetTypeOfConnect
	/*!
		\param typeofConnect type of Connector
		Set the type of connector for the graphic utem
	*/
    bool SetTypeOfConnect(ConnectorBase* typeOfConnect)
    {
        _typeOfConnect=typeOfConnect;
        return true;
    }
	//! getConnectionPath
	/*!
		Returns the path of the connector
	*/
    QPainterPath getConnectionPath()
    {
        return m_connectPath;
    }
	//! getBeginPoint
	/*!
		Returns the source point of the connector
	*/
    QPointF getBeginPoint()
    {
        return m_sourcePt;
    }
	//! getEndPoint
	/*!
		Returns the dest point of the connector
	*/
    QPointF getEndPoint()
    {
        return m_destPt;
    }
	//! getIdentifier
	/*!
		Returns the Identifier of the connector
	*/
	QString getIdentifier()
	{
		return m_identifier;
	}

signals:

public slots:

private:
    QPolygonF connectGraphic;
    QPointF m_sourcePt, m_destPt;
    int _startX, _startY;
    QPolygonF polygonF;
    ConnectorBase* _typeOfConnect;
    QPainterPath m_connectPath;

    //instance identifer
	QString m_identifier;

};
}

#endif // CONNECTORGRAPHICITEM_H
