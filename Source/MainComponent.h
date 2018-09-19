/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "DataModel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


static const Colour stateGreen () {return Colour(52,200,73);}

class NameTreeItem : public TreeViewItem {
public:
    
    enum eType {
        eTutorial,
        eSection,
    };
    class Listener {
    public:
        virtual ~Listener() {}
        virtual void itemSelected (NameTreeItem * item) = 0;
    };
    
    
    void paintItem (Graphics& g, int width, int height)
    {
        if (isSelected()) {
            g.fillAll (stateGreen().withAlpha (0.3f));
        }
        
        if (type == eTutorial) {
            Font f = g.getCurrentFont();
            f.setBold(true);
            g.setFont(f);
        }
        g.setColour(Colours::white);
        g.drawText(name, 0, 0, width, height, Justification::centredLeft);
    }
    
    
    void setType (eType type)
    {
        this->type = type;
    }
    
    bool mightContainSubItems()
    {
        if (type == eTutorial) {
            return true;
        }
        return false;
    }
    
    void itemClicked (const MouseEvent& e)
    {
        jassert(listener != nullptr);
        listener->itemSelected(this);

        if (e.mods.isRightButtonDown()) {
            printf("Right click\n");
        }
    }
    
    String name;
    int tutoiralId, sectionId;
    Listener * listener = nullptr;
private:
    eType type;
    bool custom;
};



class MainContentComponent   : public Component, public NameTreeItem::Listener, public MenuBarModel
{
public:
    //==============================================================================
    
    enum eMenuBarOption {
        eLoad = 1,
        eSave,
    };
    
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void paintOverChildren (Graphics& g);

    void resized();
    
    void itemSelected (NameTreeItem * item);

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
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
