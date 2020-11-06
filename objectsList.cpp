
#include <QtGui>

#include "ObjectsList.h"

ObjectsList::ObjectsList(int pieceSize, QWidget *parent)
    : QListWidget(parent), m_PieceSize(pieceSize)
{
    setDragEnabled(true);
    //setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(5);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
	
}

QSize ObjectsList::sizeHint() const
{
    QSize size(100,100);
    return size;
}

void ObjectsList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void ObjectsList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
}

void ObjectsList::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        addObject(pixmap, location);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
}

void ObjectsList::addObject(QPixmap pixmap, QPoint location)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
	pieceItem->setText("Item Added");
	this->addItem(pieceItem);
}

void ObjectsList::addObject(BOMObject* bomObjectType, QPoint location)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(QPixmap::fromImage( bomObjectType->GetModelIdentification()->GetToolboxImage())));
	QString fileName= bomObjectType->GetModelIdentification()->GetToolBoxImageFileName() + ".ico";
    this->m_currentObjectIdentifer=bomObjectType->GetModelIdentification()->GetName();
	//pieceItem->setData(Qt::UserRole, QVariant(pixmap));
	//QIcon icon = QIcon("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\ScenarioEditor\\Resources\\PT.ico");
	QString resourcesPath=QDir::currentPath() + "\\Resources\\";
	//QIcon icon = QIcon("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\ScenarioEditor\\Resources\\" + fileName);
	QIcon icon = QIcon(resourcesPath + fileName);
	pieceItem->setData(Qt::DecorationRole,icon);
	pieceItem->setData(Qt::UserRole,QVariant(m_currentObjectIdentifer));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
	
	pieceItem->setText(m_currentObjectIdentifer);
	this->addItem(pieceItem);
}

void ObjectsList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();
	QString str=item->data(Qt::UserRole).toString();
    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
	//setText here for identifier to be transferred
	//BOMType.GetModelIdenitification().GetName
	mimeData->setText(str);
    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

	
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
	{
	}
        //delete takeItem(row(item));
}
