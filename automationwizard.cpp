#include "automationwizard.h"
#include <qmessagebox.h>
AutomationWizard::AutomationWizard(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	QAction* actnewScene= new QAction(QIcon( "icons/newscene.ico"),"New Scenario",this);
	actnewScene->setEnabled(false);
	ui.mainToolBar->addAction(actnewScene);
	QAction* actopenScene= new QAction(QIcon( "Icons/openscene.ico"),"Open Scenario",this);
	connect(actopenScene,SIGNAL(triggered()),this->centralWidget(),SLOT(loadScenario()));
	//connect(actopenScene, SIGNAL(triggered()), this->m_currentSubWindow, SLOT(this->m_currentSubWindow->loadScenario()));
	

	m_openAction=actopenScene;
	ui.mainToolBar->addAction(actopenScene);
	QAction* actplay=new QAction(QIcon( ":/icons/playscene.ico"),"Play Scenario",this);
	actplay->setEnabled(true);
	m_playScenario=actplay;
	ui.mainToolBar->addAction(actplay);
	//connect(m_playScenario,SIGNAL(triggered()),this,SLOT(openScenarioPlayer()));
	connect(actplay,SIGNAL(triggered()), this,SLOT(openScenarioPlayer()));
	
}

void AutomationWizard::openScenarioPlayer()
{
	QMessageBox box;
	box.setText("start");
	QString path = QDir::currentPath() + "\\Ouput";
	//QCoreApplication::applicationDirPath ();
	path.append("/BOMPlayer.exe");
	QProcess process;
	process.execute(path);
}
AutomationWizard::~AutomationWizard()
{

}
