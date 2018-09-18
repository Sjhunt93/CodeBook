//
//  DataModel.cpp
//  CodeBook
//
//  Created by Samuel Hunt on 01/08/2018.
//
//

#include "DataModel.h"


TutorialsCollection::TutorialsCollection ()
{

    File tutorialSettings = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile );//getChildFile("Contents").getChildFile("Resources");
    



    
//    File xmlFile("/Users/sj4-hunt/Documents/iap.xml");// = tutorialSettings.getChildFile("tutorials.xml");
    File xmlFile = tutorialSettings.getParentDirectory().getChildFile("code book files").getChildFile("iap.xml");
    std::cout << "XML Location : " << xmlFile.getFullPathName() << "\n";
    if (!xmlFile.existsAsFile()) {
        return;
    }

    XmlDocument settingsDoc (xmlFile);
    XmlElement * root = settingsDoc.getDocumentElement();
    if (root == nullptr) {
        return;
    }
    jassert(root != nullptr);
    
    for (int tut = 0; tut < root->getNumChildElements(); tut++) {
        XmlElement * tutorialElement = root->getChildElement(tut);
        
        String name = tutorialElement->getStringAttribute("name");
        
        Tutorial tutorial;
        tutorial.name = name;
        for (int s = 0; s < tutorialElement->getNumChildElements(); s++) {
            XmlElement * itemXml = tutorialElement->getChildElement(s);
            Section section;
            section.name = itemXml->getStringAttribute("name");
            section.typeToUse = (eType) itemXml->getStringAttribute("type").getIntValue();
            jassert(section.typeToUse >= eCppOnly && section.typeToUse <= eFragment);
            
            section._id = s;
            section.tutorialId = tut;
            
            for (int i = 0; i < itemXml->getNumChildElements(); i++) {
                XmlElement * element = itemXml->getChildElement(i);
                String type = element->getTagName();
                if (type == "h") {
                    section.hFile = element->getStringAttribute("src");
                    section.h = true;
                }
                else if (type == "cpp") {
                    section.cppFile = element->getStringAttribute("src");
                    section.c = true;
                
                }
                else if (type == "code") {
                    section.singleLine = element->getStringAttribute("src");
                    section.s = true;
                }

            }
            tutorial.sections.add(section);
            
        }
        tutorials.add(tutorial);
    }
    //        std::cout << t.dataTree.getNumChildren() << "\n";
    
#if 0
    for (int i = 0; i < tutorials.size(); i++) {
        for (int s = 0; s < tutorials[i].sections.size(); s++) {
            for (int t = 0; t < tutorials[i].sections[s].texts.size(); t++) {
                printf("%i %i %s \n", i, s, tutorials[i].sections[s].texts[t].text.toRawUTF8());
            }
        }
    }
#endif
    
}
TutorialsCollection::~TutorialsCollection ()
{
    
}

const int TutorialsCollection::getTotalTutorials ()
{
    return tutorials.size();
}

TutorialsCollection::Tutorial TutorialsCollection::getTutorial (const int index)
{
    return tutorials[index];
}

void TutorialsCollection::setXML (int tutorial, int section, File hPath, File cPath, File sPath, bool hUp, bool cUp, bool sUp )
{
    File tutorialSettings = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile );
    File xmlFile = tutorialSettings.getParentDirectory().getChildFile("code book files").getChildFile("iap.xml");
    jassert(xmlFile.existsAsFile());
    XmlDocument settingsDoc (xmlFile);
    XmlElement * root = settingsDoc.getDocumentElement();
    
    
    
    XmlElement * tutorialElement = root->getChildElement(tutorial);
    XmlElement * activityXml = tutorialElement->getChildElement(section);
    
    if (hUp) {
        XmlElement * element = activityXml->getChildElement(0);
        element->setAttribute("src", hPath.getFileName());
        tutorials.getRawDataPointer()[tutorial].sections.getRawDataPointer()[section].hFile = hPath.getFileName();
    }
    if (cUp) {
        XmlElement * element = activityXml->getChildElement(1);
        element->setAttribute("src", cPath.getFileName());
        tutorials.getRawDataPointer()[tutorial].sections.getRawDataPointer()[section].cppFile = cPath.getFileName();
    }
    if (sUp) {
        XmlElement * element = activityXml->getChildElement(2);
        element->setAttribute("src", sPath.getFileName());
        tutorials.getRawDataPointer()[tutorial].sections.getRawDataPointer()[section].singleLine = sPath.getFileName();
    }
    
    root->writeToFile(xmlFile, "");

    
    
    
}
void TutorialsCollection::getTotals (int &total, int & completed)
{
    total = 0;
    completed = 0;
    for (int i = 0; i < tutorials.size(); i++) {
        for (int s = 0; s < tutorials[i].sections.size(); s++) {
            
            int sum =   tutorials[i].sections[s].cppFile.isNotEmpty() +
                        tutorials[i].sections[s].hFile.isNotEmpty() +
                        tutorials[i].sections[s].singleLine.isNotEmpty();
            
            if (sum){
                completed++;
            }
            total++;
            
        }
    }
}