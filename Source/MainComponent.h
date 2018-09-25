/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "NameTreeItem.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class MainContentComponent   : public Component, public NameTreeItem::Listener, public MenuBarModel
{
public:
    //==============================================================================
    
    enum eMenuBarOption {
        eLoad = 1,
        eSave,
        //
        eAddEntry,
        eRemoveEntry,
    };
    
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void paintOverChildren (Graphics& g);

    void resized();
    
    void itemSelected (NameTreeItem * item);
    void itemRenamed (NameTreeItem * item, String newName);

    void loadSection ();

    StringArray getMenuBarNames();
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
    void menuItemSelected (int menuItemID, int topLevelMenuIndex);
    
    
private:
    //==============================================================================
    
    void refreshTreeViews ();
    
    TutorialsCollection dataModel;
    TreeView    treeView;

    
    CPlusPlusCodeTokeniser tokeniser;
    
    
    CodeDocument headerDoc;
    CodeDocument sourceDoc;
    
    CodeEditorComponent     headerComponent;
    CodeEditorComponent     sourceComponent;
    
//    TextButton              pullBtn, pushBtn, add;
    TutorialsCollection::Section    currentSection;
    bool                            nothingIsSelected;
    NameTreeItem            *       currentlySelected;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
