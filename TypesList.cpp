
 #include <QtGui>

 #include "Typeslist.h"

 TypesList::TypesList(int typeSize, QWidget *parent)
     : QListWidget(parent), m_TypeSize(typeSize)
 {
     setDragEnabled(true);
     setViewMode(QListView::IconMode);
     setIconSize(QSize(32, 32));
     setSpacing(10);
     setAcceptDrops(true);
     setDropIndicatorShown(true);
	 
	 
 }
 
 QSize TypesList::sizeHint() const
{
    QSize size(100,100);
    return size;
}

 void TypesList::dragEnterEvent(QDragEnterEvent *event)
 {
     if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
         event->accept();
     else
         event->ignore();
 }

 void TypesList::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else
         event->ignore();
 }

 void TypesList::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
         QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
         QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
         QPixmap pixmap;
         QPoint location;
         dataStream >> pixmap >> location;

         addType(pixmap, location);

         event->setDropAction(Qt::MoveAction);
         event->accept();
     } else
         event->ignore();
 }

 void TypesList::addType(QIcon icon, QPoint location)
 {
     QListWidgetItem *pieceItem = new QListWidgetItem(this);
     pieceItem->setIcon(icon);
     pieceItem->setData(Qt::UserRole, QVariant("123"));
     pieceItem->setData(Qt::UserRole+1, location);
     pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                         | Qt::ItemIsDragEnabled);
	 pieceItem->setText("123");
	 pieceItem->setData(Qt::DecorationRole,icon);
	 QLabel *boatIcon = new QLabel(this);
     boatIcon->setPixmap(QPixmap(":/icons/sample.png"));
     boatIcon->move(10, 10);
	 this->setIconSize(QSize(32, 32));
     boatIcon->show();
     boatIcon->setAttribute(Qt::WA_DeleteOnClose);
	 //boatIcon;
	 //pieceItem->setSizeHint(QSize(0,265));
	 this->addItem(pieceItem);
	 this->setItemWidget(pieceItem,boatIcon);

	 
 }

 void TypesList::startDrag(Qt::DropActions /*supportedActions*/)
 {
     QListWidgetItem *item = currentItem();

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
     QPoint location = item->data(Qt::UserRole+1).toPoint();

     dataStream << pixmap << location;

     QMimeData *mimeData = new QMimeData;
     mimeData->setData("image/x-puzzle-piece", itemData);

     QDrag *drag = new QDrag(this);
     drag->setMimeData(mimeData);
     drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
     drag->setPixmap(pixmap);

     if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
         delete takeItem(row(item));
 }