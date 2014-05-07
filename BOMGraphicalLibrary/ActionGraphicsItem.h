#ifndef ACTGRAPHITEM_H
#define ACTGRAPHITEM_H
#include <qgraphicsitem.h>
#include <qicon.h>


#include <QGraphicsPixmapItem>
#include <../BOMLibrary/interface.h>
#include <QPainter>
#include <QPixmap>
class ActionGraphicsItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    ActionGraphicsItem(const QPixmap &pix) : QGraphicsPixmapItem(pix)
    {

    }
	
};

/*class PixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    PixmapItem(const QPixmap &pix) : QGraphicsPixmapItem(pix)
    {
    }
};*/


/*

class MsgGraphicsItem: public QObject, public QGraphicsPixmapItem
{
	
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
	explicit MsgGraphicsItem(QGraphicsItem *parent = 0);
    explicit MsgGraphicsItem(QString itemName,QGraphicsItem *parent = 0,int startX=0, int startY=0);
    QPointF GetPosition()
    {
        return QPointF(_startX,_startY);
    }


	~MsgGraphicsItem(void);
private:
	int _startX;
	int _startY;
};
*/

#endif
