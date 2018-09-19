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
    
    void getTotals (int &total, int & completed);
    
    File getRootFolderLocation ();
private:
    Array<Tutorial> tutorials;
    File rootFolderLocation;
    File xmlFile;
    
    
};
#endif /* defined(__CodeBook__DataModel__) */
