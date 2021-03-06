// File: SpacerInstance.h
// Original Author: Michael Imelfort 2011
// --------------------------------------------------------------------
//
// OVERVIEW:
//
// Spacers! Lots of them!
// Each found spacer *could* be different. Each unique instance should be saved
// so that graph cleaning can be doned.
// --------------------------------------------------------------------
//  Copyright  2011 Michael Imelfort and Connor Skennerton
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
// --------------------------------------------------------------------
//
//                        A
//                       A B
//                      A B R
//                     A B R A
//                    A B R A C
//                   A B R A C A
//                  A B R A C A D
//                 A B R A C A D A
//                A B R A C A D A B 
//               A B R A C A D A B R  
//              A B R A C A D A B R A 
//

#ifndef SpacerInstance_h
    #define SpacerInstance_h

// system includes
#include <iostream>
#include <list>

// local includes
#include "crassDefines.h"
#include "CrisprNode.h"
#include "StringCheck.h"

class SpacerInstance;
// we hash together string tokens to make a unique key for each spacer
typedef unsigned int SpacerKey;

enum SI_EdgeDirection {
    REVERSE = 0,
    FORWARD = 1
};

typedef struct{ 
    SpacerInstance * edge; 
    SI_EdgeDirection d; 
} spacerEdgeStruct;

inline std::string saySpacerEdgeDirectionLikeAHuman(SI_EdgeDirection d)
{
	if(d == REVERSE) { return "REVERSE"; }
	return "FORWARD";
}


typedef std::vector<SpacerInstance * > SpacerInstanceVector;
typedef std::vector<SpacerInstance * >::iterator SpacerInstanceVector_Iterator;

typedef std::list<SpacerInstance * > SpacerInstanceList;
typedef std::list<SpacerInstance * >::iterator SpacerInstanceList_Iterator;

typedef std::pair<SpacerInstance *, SpacerInstance *> SpacerInstancePair;

typedef std::vector<spacerEdgeStruct *> SpacerEdgeVector;
typedef std::vector<spacerEdgeStruct *>::iterator SpacerEdgeVector_Iterator;

inline SpacerKey makeSpacerKey(StringToken backST, StringToken frontST)
{
    //-----
    // make a spacer key from two string tokens
    //
	if(backST < frontST)
	{
		return (backST * 10000000) + frontST;
	}
	return (frontST * 10000000) + backST;
}

class SpacerInstance {

    
public:
        SpacerInstance (void) {
            SI_SpacerSeqID = 0;
            SI_LeadingNode = NULL;
            SI_LastNode = NULL;
            SI_InstanceCount = 0;
            SI_ContigID = 0;
            SI_Attached = false;
            SI_isFlanker = false;
        }
        
        SpacerInstance (StringToken spacerID);
        SpacerInstance (StringToken spacerID, CrisprNode * leadingNode, CrisprNode * lastNode);
        ~SpacerInstance () {clearEdge();}
        
        //
        // get / set
        //
        inline void incrementCount(void) { SI_InstanceCount++; }
        inline unsigned int getCount(void) { return SI_InstanceCount; }
        inline StringToken getID(void) { return SI_SpacerSeqID; }
        inline CrisprNode * getLeader(void) { return SI_LeadingNode; }
        inline CrisprNode * getLast(void) { return SI_LastNode; }
        inline bool isAttached(void) 
        { 
            if ((SI_LeadingNode->isAttached() && SI_LastNode->isAttached() ^ SI_Attached))
            {
                std::cout<<"Spacer "<<SI_SpacerSeqID<<" has asynchronous attached state"<<std::endl;  
            }
            return SI_Attached;
        }
        inline void setAttached(bool attached) { SI_Attached = attached; }
        inline bool isFlanker(void){return SI_isFlanker;}
        inline void setFlanker(bool f){SI_isFlanker = f;}
        inline int isCap(void) {return (getSpacerRank() == 1);}
        //
        // contig functions
        //
        inline int getContigID(void) { return SI_ContigID; }
        inline void setContigID(int CID) { SI_ContigID = CID; }
        inline int getSpacerRank(void) { return (int)SI_SpacerEdges.size(); }

        //
        // graph functions
        //
        bool isViable(void);
        bool isFur(void);
        void detachFromSpacerGraph(void);
        bool detachSpecificSpacer(SpacerInstance * target);

        //
        // edge functions/iterators
        //
        inline void addEdge(spacerEdgeStruct * s) { SI_SpacerEdges.push_back(s); }
        void clearEdge(void);
        
    SpacerEdgeVector_Iterator begin(void) {return SI_SpacerEdges.begin();}
    
    SpacerEdgeVector_Iterator end(void) {return SI_SpacerEdges.end();}
    
    SpacerEdgeVector_Iterator find(SpacerInstance *);
    
    inline SpacerEdgeVector * getEdges(void) {return &SI_SpacerEdges;}
        
        //
        // File /IO
        //
        void printContents(void);
        
    private:
        StringToken SI_SpacerSeqID;               // the StringToken of this spacer
        CrisprNode * SI_LeadingNode;              // the first node of this spacer
        CrisprNode * SI_LastNode;                 // the last node
        unsigned int SI_InstanceCount;            // the number of times this exact instance has been seen
        bool SI_Attached;							  // is this spacer attached?
        int SI_ContigID;							  // contig ID
        SpacerEdgeVector SI_SpacerEdges;              // Pointers to the spacers that come off this spacer
        bool SI_isFlanker;                          // set if this spacer instance is considered a flanker or not
};


#endif //SpacerInstance_h
