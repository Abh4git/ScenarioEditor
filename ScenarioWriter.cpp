#include <ScenarioWriter.h>

ScenarioWriter::ScenarioWriter(QString fileName)
{
	this->m_currentFileName=fileName;
	m_TopologyItemsList==QList<SceneItem*>();
	m_ActionsList=QList<SceneAction*>();
	m_CommunicationActionsList=QList<ComAction*>();
}

void ScenarioWriter::AddTopologyItem(SceneItem* item)
{
	m_TopologyItemsList.append(item);
}

void ScenarioWriter::AddActions(SceneAction* item)
{
	m_ActionsList.append(item);
}

void ScenarioWriter::AddComActions(ComAction* item)
{
	m_CommunicationActionsList.append(item);
}

bool ScenarioWriter::WriteAndClose()
{
	/*
	<?xml version="1.0"?>
<Scenario>
<SceneTopology>
<SceneItem id="1" type="1" name="OPER-SPLUS" userdefname="objname" pos="10,10"/> 
<SceneItem id="2" type="1" name="ENGG-SPLUS" userdefname="objname" pos="200,10"/> 
<SceneItem id="3" type="1" name="COM_BUS" userdefname="objname" pos="-50,100"/> 
</SceneTopology>
<SceneActions>
<SceneAction id="1" order="1" type="1" source="OPER-SPLUS.1" dest="ENGG-SPLUS.1" repeat="3" waittime="1000"/>
<SceneAction id="2" order="2" type="2" source="ENGG-SPLUS.1" dest="OPER-SPLUS.1" repeat="3" waittime="1000"/>
</SceneActions>
<ComActions> 	
<ComAction id="1" type="1" assocsceneactionid="2" sourceaddress="" destaddress="" repeat="3" timetonext="1000"/>
<ComAction id="2" type="1" assocsceneactionid="2" sourceaddress="" destaddress="" repeat="3" timetonext="1000"/>
</ComActions>
</Scenario> */


	QFile file(m_currentFileName);
	file.open(QFile::WriteOnly);
	//file.open(QFile::ReadWrite);
	//output.open(stdout, QIODevice::WriteOnly);
//! [write output]
//! [start stream]
	QXmlStreamWriter writer(&file);
    
    writer.setAutoFormatting(true);

	writer.writeStartDocument();
	writer.writeStartElement("Scenario");
	writer.writeStartElement("SceneTopology");
	int iCount=1;
	foreach(SceneItem* item,m_TopologyItemsList)
	{
		writer.writeStartElement("SceneItem");
		writer.writeAttribute("id",item->getIdentifier());
		writer.writeAttribute("type",QString::number(1));
		writer.writeAttribute("name",item->getUserDefName());
		writer.writeAttribute("pos",QString::number(item->getPosition().x()) + "," + QString::number(item->getPosition().y()));
		writer.writeEndElement();
		iCount++;
	}
	writer.writeEndElement();
	writer.writeStartElement("SceneActions");
	iCount=1;
	foreach(SceneAction* item,m_ActionsList)
	{
		writer.writeStartElement("SceneAction");
		writer.writeAttribute("id",QString::number(iCount));
		writer.writeAttribute("order",QString::number(iCount));
		writer.writeAttribute("type",QString::number(1));
		writer.writeAttribute("source",item->getSourceName());
		writer.writeAttribute("dest",item->getDestName());
		writer.writeAttribute("repeat","3");
		writer.writeAttribute("waittime","1000");
		writer.writeEndElement();
		iCount++;
	}
	writer.writeEndElement();
	iCount=1;
	writer.writeStartElement("ComActions");
	foreach(ComAction* item,m_CommunicationActionsList)
	{
		writer.writeStartElement("ComAction");
		writer.writeAttribute("id",QString::number(iCount));
		writer.writeAttribute("type",QString::number(1));
		writer.writeAttribute("assocsceneactionid","2");
		writer.writeAttribute("sourceaddress","");
		writer.writeAttribute("destaddress","");
		writer.writeAttribute("repeat","3");
		writer.writeAttribute("timetonext","1000");
		writer.writeEndElement();
		iCount++;
	}
	
	writer.writeEndElement();
	writer.writeEndElement();
	writer.writeEndDocument();
	//output.flush();
	file.close();
	return true;
}
