#include "automationwizard.h"
#include <QApplication>
#include <automationelementswidget.h>
#include <qplugin.h>

//Q_IMPORT_PLUGIN(qjpeg)
//Q_IMPORT_PLUGIN(qgif)
//Q_IMPORT_PLUGIN(QICOPlugin)


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	


	
	
    //AutomationElementsWidget w1;
    AutomationWizard w;
    //w.setCentralWidget(&w1);
	w.show(); 
	/*TestListWidgetwithImage w;
	w.show();*/
	
	return a.exec();
}

