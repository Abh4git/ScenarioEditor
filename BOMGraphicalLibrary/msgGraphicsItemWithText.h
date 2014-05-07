#ifndef MESSAGEGRAPHTEXT_H
#define MESSAGEGRAPHTEXT_H
#include <QGraphicsItemGroup>
#include <qpoint.h>
//! msgGraphicsItemWithText
	/*!
		Responsibility: To create a Communication Message as Item in scene
		with a Text in addition
	*/
class msgGraphicsItemWithText : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
	//! Constructor
	/*!
		\param position as QPoint
		\param UserDefName as string
	*/
	msgGraphicsItemWithText(QPoint position,QString UserDefName);
	~msgGraphicsItemWithText(void);
};
#endif
