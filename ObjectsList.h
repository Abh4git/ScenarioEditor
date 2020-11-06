
#ifndef PIECESLIST_H
#define PIECESLIST_H


#include <QListWidget>
#include "../BOMLibrary/bomobject.h"
#include <qstring.h>
using namespace BOMLIB;
	//! ObjectsList class
	/*!
		Responsibility: Inheriting from QListWidget, this provides
		a way of showing the BOM Types as List with Icon and text
	*/
class ObjectsList : public QListWidget
{
    Q_OBJECT

public:
	//! Constructor
	/*!
		\param pieceSize size of the icon to show
		\param parent QWidget
	*/
    ObjectsList(int pieceSize, QWidget *parent = 0);
	//! addObject
	/*!
		\param pixmap QPixmap
		\param location QPoint
		Add Object to list
	*/
    void addObject(QPixmap pixmap, QPoint location);
	//! addObject
	/*!
		\param bomObject BOMObject
		\param location QPoint
		Add BOM Object to list
	*/
	void addObject(BOMObject* bomObject, QPoint location);
	//! sizeHint
	/*!
		Returns sizeHint - Important to Resize as per specified 
	*/
	QSize sizeHint() const;
protected:
	//! Overriding events so that Drag can be supported
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);
	
    int m_PieceSize;
	QString m_currentObjectIdentifer;
};

#endif
