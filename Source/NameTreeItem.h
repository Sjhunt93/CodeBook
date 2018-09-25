//
//  NameTreeItem.h
//  CodeBook
//
//  Created by Samuel Hunt on 25/09/2018.
//
//

#ifndef __CodeBook__NameTreeItem__
#define __CodeBook__NameTreeItem__

#include "../JuceLibraryCode/JuceHeader.h"
#include "DataModel.h"

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
        virtual void itemRenamed (NameTreeItem * item, String newName) = 0;
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
        
        if (e.mods.isRightButtonDown() && custom) {
            PopupMenu p;
            p.addItem(1, "Rename");
            int choice = p.show();
            if (choice == 1) {
                AlertWindow al("Rename entry.", "Enter name for entry:", AlertWindow::QuestionIcon);
                al.addTextEditor("name", "");
                al.getTextEditor("name")->setMultiLine(false);
                
                al.addButton("Ok", 1);
                al.addButton("Cancel", 2);
                
                int result = al.runModalLoop();
//                printf("result %i\n", result);
                if (result == 1) {
                    String name = al.getTextEditor("name")->getText();
                    listener->itemRenamed(this, name);
                }
                
                
            }
        }
    }
    
    String name;
    int tutoiralId, sectionId;
    Listener * listener = nullptr;
    bool custom;

private:
    eType type;
};
#endif /* defined(__CodeBook__NameTreeItem__) */
