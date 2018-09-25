//
//  DataModel.h
//  CodeBook
//
//  Created by Samuel Hunt on 01/08/2018.
//
//

#ifndef __CodeBook__DataModel__
#define __CodeBook__DataModel__

#include "../JuceLibraryCode/JuceHeader.h"


class TutorialsCollection {
public:
    

    enum eType {
        eCppOnly = 0,
        eBoth,
        eFragment,
        eCustom,
    };
    
    struct Section {
        Section ()
        {
            h = c = s = false;
        }
        String hFile, cppFile, singleLine;
        bool h, c, s;
        
        int _id;
        eType typeToUse;
        String name;
        int tutorialId;
        bool locked; //This is used for adding more entries, as some of them cant be removed as they are required for the course..
    };
    
    struct Tutorial {
        String name;
        int _id;
        Array<Section> sections;
    };
    
    TutorialsCollection ();
    ~TutorialsCollection ();
    
    
    void loadTutorials (File xml);
    
    
    const int getTotalTutorials ();
    Tutorial getTutorial (const int index);
    
    void setXML (int tutorial, int section, File hPath, File cPath, File sPath, bool hUp, bool cUp, bool sUp );
    void setName (int tutorial, int section, String name);
    
    void getTotals (int &total, int & completed);
    
    File getRootFolderLocation ();
    
    void addEntry (const int tutorial, const int afterSection);
    
private:
    Array<Tutorial> tutorials;
    File rootFolderLocation;
    File xmlFile;
    
    
};
#endif /* defined(__CodeBook__DataModel__) */
