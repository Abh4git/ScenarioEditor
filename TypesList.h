

 #ifndef TYPESLIST_H
 #define TYPESLIST_H

 #include <QListWidget>

 class TypesList : public QListWidget
 {
     Q_OBJECT

 public:
     TypesList(int typeSize, QWidget *parent = 0);
     void addType(QIcon icon, QPoint location);
	 QSize sizeHint() const;
 protected:
     void dragEnterEvent(QDragEnterEvent *event);
     void dragMoveEvent(QDragMoveEvent *event);
     void dropEvent(QDropEvent *event);
     void startDrag(Qt::DropActions supportedActions);

     int m_TypeSize;
 };

 #endif