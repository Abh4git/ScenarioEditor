#include "testlistwidgetwithimage.h"

TestListWidgetwithImage::TestListWidgetwithImage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupWidgets();

     setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
     setWindowTitle(tr("Puzzle"));
}

TestListWidgetwithImage::~TestListWidgetwithImage()
{

}

 void TestListWidgetwithImage::setupWidgets()
{
	
     QFrame *frame = new QFrame;
     QHBoxLayout *frameLayout = new QHBoxLayout(frame);
	 //Add ListView
	 contentsListView= new QListView();
	 contentsListView->setViewMode(QListView::IconMode);
	 

	 //Setting the icon size
	contentsListView->setIconSize(QSize(32, 32));

	 
	 iStandardModel = new QStandardItemModel(this);
	QList<QStandardItem*> *items = new QList<QStandardItem*> ();
    QString qs = "This is string";

	 QStandardItem *item;
	item = new QStandardItem();
	item->setTextAlignment(Qt::AlignBottom);
	item->setData( "12344", Qt::DisplayRole );
	QIcon icon = QIcon("C:\\Abhilash\\MyToolBox\\SystemsExplorer\\ScenarioEditor\\Resources\\PT.ico");
	//item->setIcon();
	//item->setData( QIcon(":/icons/busbar32.ico"), Qt::DecorationRole );
	item->setData( icon, Qt::DecorationRole );
	item->setSizeHint( QSize( 32,32 ) );
	item->setEditable( false ); 

	iStandardModel->appendRow(item);
   
	
   QStandardItem* item2 = new QStandardItem();
   //item2->setText("12345");
	item2->setData( "2468", Qt::DisplayRole );
	item2->setIcon(QIcon(":/icons/busbar32.ico"));
	item2->setData( QIcon(":/icons/busbar32.ico"), Qt::DecorationRole );
	item2->setSizeHint( QSize( 64,64 ) );
   //item2->setIcon(QIcon(":/icons/busbar32.ico"));
   //items->append(item2);
	
   iStandardModel->appendRow(item2);
 
 
//Setting the model
contentsListView->setModel(iStandardModel);

	frameLayout->addWidget(contentsListView);
	 this->setLayout(frameLayout);
     
	 /* commented
	 QIcon icon1=QIcon(":/icons/busbar32.ico");
     m_typesList = new TypesList(100, this);
	 m_typesList->addType(icon1,QPoint(10,10));
	 //m_typesList->addType(icon1,QPoint(400,100));
	 frameLayout->addWidget(m_typesList); */
	 
	 
 
}
