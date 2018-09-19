/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent() : headerComponent(headerDoc, &tokeniser), sourceComponent(sourceDoc, &tokeniser)
{
    
    addAndMakeVisible(treeView);
    
    refreshTreeViews();
    
    setSize (1200, 700);
    
    addAndMakeVisible(headerComponent);
    addAndMakeVisible(sourceComponent);
    

    nothingIsSelected = true;
    
}


MainContentComponent::~MainContentComponent()
{
    treeView.setRootItem(nullptr);
}

void MainContentComponent::paint (Graphics& g)
{
//    g.fillAll (Colour::fromRGB(34, 34, 34));
    g.fillAll(Colours::black);
    

    g.setColour(Colours::white);
    
    
    const int treeViewWidth = 300;
    int dif = (getWidth() - treeViewWidth) / 2.0;
    
    int a, b;
    dataModel.getTotals(a, b);
    
    
    
    String exercises = "Exercises Complete: " + String(b) + "/" + String(a) + "\n";
//    g.drawText(exercises, 5, getHeight() - 45, dif, 30, Justification::left);

    
    g.setFont(24);
    g.drawText("IAP.cpp", treeViewWidth + 10, 5, dif, 35, Justification::centred);
    
    if (headerComponent.isVisible()) {
        g.drawText("IAP.h", treeViewWidth + dif + 10, 5, dif, 35, Justification::centred);
    }

}

void MainContentComponent::paintOverChildren (Graphics& g)
{
    if (! sourceDoc.getNumCharacters()) {
//        g.drawText("File Empty", sourceComponent.getX(), sourceComponent.getY(), sourceComponent.getWidth(), sourceComponent.getHeight(), Justification::centred);
    }
    if (! headerDoc.getNumCharacters() && headerComponent.isVisible()) {
//        g.drawText("File Empty", headerComponent.getX(), headerComponent.getY(), headerComponent.getWidth(), headerComponent.getHeight(), Justification::centred);
    }
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    const int treeViewWidth = 300;
    treeView.setBounds(0, 0, treeViewWidth, getHeight() - 50);
    
    if (headerComponent.isVisible()) {
        int dif = (getWidth() - treeViewWidth) / 2.0;
        
        sourceComponent.setBounds(treeViewWidth + 5, 45, dif - 10, getHeight() - 50);
        headerComponent.setBounds(sourceComponent.getRight() + 10, sourceComponent.getY(), sourceComponent.getWidth(), sourceComponent.getHeight());
        
    }
    else {
        sourceComponent.setBounds(treeViewWidth+5, 45, getWidth() - treeViewWidth+10, getHeight() - 50);
    }
    
    
//    pullBtn.setBounds(treeView.getRight() + 10, 5, 200, 35);
//    pushBtn.setBounds(getWidth() - 210, 5, 200, 35);
    
}


void MainContentComponent::loadSection ()
{
    if (currentSection.typeToUse == TutorialsCollection::eCppOnly) {
        headerComponent.setVisible(false);
        
        if (currentSection.cppFile.isNotEmpty()) {
            File f1 =  dataModel.getRootFolderLocation().getChildFile(currentSection.cppFile);
            if (f1.exists()) {
                FileInputStream s1(f1);
                sourceDoc.loadFromStream(s1);
            }
        }
          
        else {
            sourceDoc.deleteSection(0, sourceDoc.getNumCharacters());
        }
        
    
    }
    else if (currentSection.typeToUse == TutorialsCollection::eBoth) {
        
        headerComponent.setVisible(true);
        if (currentSection.cppFile.isNotEmpty()) {
            File f1 = dataModel.getRootFolderLocation().getChildFile(currentSection.cppFile);
            if (f1.exists()) {
                FileInputStream s1(f1);
                sourceDoc.loadFromStream(s1);
            }

            
        }
        else {
            sourceDoc.deleteSection(0, sourceDoc.getNumCharacters());
        }
        if (currentSection.hFile.isNotEmpty()) {
            File f1 = dataModel.getRootFolderLocation().getChildFile(currentSection.hFile);
            if (f1.exists()) {
                FileInputStream s1(f1);
                headerDoc.loadFromStream(s1);
            }

        }
        else {
            headerDoc.deleteSection(0, headerDoc.getNumCharacters());
        }
    }
    
    repaint();
    resized();

    
    
}
void MainContentComponent::itemSelected (NameTreeItem * item)
{
    /*
     Need to save to file...
     */
 
    if (!nothingIsSelected) {
#if 0
        File root = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile ).getParentDirectory();
        if (!root.getChildFile("code book files").exists()) {
            root.getChildFile("code book files").createDirectory();
        }
        File codeFles = root.getChildFile("code book files");
#else
        File codeFles = dataModel.getRootFolderLocation();
#endif
        
        String fName = String(currentSection.tutorialId) + "_" + String(currentSection._id);
        
        if (sourceDoc.getNumCharacters()) {
            File f = codeFles.getChildFile(fName + "_cpp.txt");
            if (f.existsAsFile()) {
                f.deleteFile();
            }
            FileOutputStream fStream(f);
            sourceDoc.writeToStream(fStream);
            
            dataModel.getTutorial(currentSection.tutorialId).sections[currentSection._id];
            dataModel.setXML(currentSection.tutorialId, currentSection._id, File(""), f, File(""), false, true, false);
            
        }
        if (headerDoc.getNumCharacters()) {
            File f = codeFles.getChildFile(fName + "_h.txt");
            if (f.existsAsFile()) {
                f.deleteFile();
            }
            FileOutputStream fStream(f);
            headerDoc.writeToStream(fStream);
            
            dataModel.getTutorial(currentSection.tutorialId).sections[currentSection._id];
            dataModel.setXML(currentSection.tutorialId, currentSection._id, f, File(""), File(""), true, false, false);
        }
        
    }
 
    if (nothingIsSelected) {
        nothingIsSelected = false;
    }
    currentSection = dataModel.getTutorial(item->tutoiralId).sections[item->sectionId];
    loadSection();

}

StringArray MainContentComponent::getMenuBarNames()
{
    return {"file"};
}
PopupMenu MainContentComponent::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
    PopupMenu pm;
    pm.addItem(eLoad, "Load");
    pm.addItem(eSave, "Save");
    return pm;
    
    
}
void MainContentComponent::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
    if (menuItemID == eLoad) {
        FileChooser chooser ("Load Session",
                             File::nonexistent,
                             "*.xml");
        if (chooser.browseForFileToOpen())
        {
            File file (chooser.getResult());
            
            if (file.existsAsFile()) {
                dataModel.loadTutorials(file);
                refreshTreeViews();
            }

            
        }

        
    }
}

void MainContentComponent::refreshTreeViews ()
{
    treeView.setRootItem(nullptr); //clear an old one if needed.
    NameTreeItem *root = new NameTreeItem();
    treeView.setRootItem(root);
    treeView.setRootItemVisible(false);
    
    for (int i = 0; i < dataModel.getTotalTutorials(); i++) {
        NameTreeItem * nm = new NameTreeItem();
        nm->name = String (i+1) + ": " + dataModel.getTutorial(i).name;
        nm->setType(NameTreeItem::eTutorial);
        nm->sectionId = 0;
        nm->tutoiralId = i;
        nm->listener = this;
        for (int j = 0; j < dataModel.getTutorial(i).sections.size(); j++) {
            NameTreeItem * n = new NameTreeItem;
            n->name = String(i+1) + "." + String(j+1) + ": " + dataModel.getTutorial(i).sections[j].name;
            n->setType(NameTreeItem::eSection);
            n->tutoiralId = i;
            n->sectionId = j;
            n->listener = this;
            nm->addSubItem(n);
            
        }
        root->addSubItem(nm);
    }
    
    sourceDoc.replaceAllContent("");
    headerDoc.replaceAllContent("");
    
}