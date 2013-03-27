//
//  kAstar.h
//
//  Created by kael on 12/28/12.
//
//
#include "kBinaryHeap.h"
#ifndef __kAstar__
#define __kAstar__
struct kAstarNode
{
    kAstarNode(void)
    :parent(0), child(0), G(0), H(0), F(0), b(0), column_index(0)
    , row_index(0), _id(0), s(0)
	{
        
	}
	kAstarNode(int blocked, int c, int r, int id)
    :parent(0), child(0), G(0), H(0), F(0), b(blocked), column_index(c), row_index(r)
    , _id(id), s(0)
	{
        
	}
    
    void init()
    {
        s=0;
    }
    
    kAstarNode* parent;
    kAstarNode* child;
    int G;
	int H;
	int F;
    
	unsigned short b; // 0:non blocked; 1:blocked
	int column_index;
	int row_index;
	int _id;
	unsigned char s; // 0:free; 1:openlist 2:closelist
};

#define COST 10
#define TYPE_SQUARE 0
#define TYPE_45DEGREE 1
class kAstarAlgorithm
{
public:
    kAstarAlgorithm():openArray(this)
    , closeArray(this)
    , currNode(0)
    , startNode(0)
    , endNode(0)
    , searchTime(0)
    , isStop(false)
    {
        rowCount = 20;
        columnCount = 20;
        map = new kAstarNode*[rowCount*columnCount];
    }
    
    kAstarAlgorithm(unsigned short r,unsigned short c,unsigned short t=TYPE_SQUARE):openArray(this)
    , closeArray(this)
    , currNode(0)
    , startNode(0)
    , endNode(0)
    , searchTime(0),rowCount(r),columnCount(c)
    , isStop(false)
    {
        type = t;
//        if(type == TYPE_SQUARE)
//            ;//map = new kAstarNode*[rowCount*columnCount];
//        else if(type == TYPE_45DEGREE)
//        {
//            rowCount = rowCount * 2;
//            columnCount = columnCount / 2 + 1;
//        }
        map = new kAstarNode*[rowCount*columnCount];
    }
    
    ~kAstarAlgorithm(void)
	{
		for(int i=0; i<rowCount*columnCount; i++)
			delete map[i];
		delete[] map;
	}
    kAstarNode* AStarSearchRun(kAstarNode* start, kAstarNode* end);
    void AStarSearchInit(kAstarNode* start, kAstarNode* end);
	void AStarSearchStep(void);
    
    void TestCreateMap(int rand);
    void createMap(const char* walkArr);
    void createMapEx(const char* walkArr);
    void TravelOutputResult(void);
    kAstarNode* getEndNode(void);
    kAstarNode* getCurrNode(void);
    kAstarNode* getNode(int c, int r);
	kAstarNode* getNode(int id);
    bool IsStop(void) { return isStop; }
    void setCellSize(int r,int c){rowCount = r;columnCount = c;}
    // path finding type
    unsigned short type;
    unsigned short getColumn()const{return columnCount;}
    unsigned short getRow()const{return rowCount;}
private:
    kAstarNode* currNode;
	kAstarNode* startNode;
	kAstarNode* endNode;
    
    kAstarNode** map;
    unsigned short rowCount;
    unsigned short columnCount;
    int searchTime;
    bool isStop;
    kBinaryHeap openArray;
    kBinaryHeap closeArray;
    
    int getF(int w, int h);
	int getF(int id);
    
	kAstarNode* allocNode(int b, int column, int row, int id);
	void calculateNode(kAstarNode* node);
	// choose the lowest F node.
	kAstarNode* getLowestOpenNode(void);
    
	kAstarNode* getOpenNode(kAstarNode* node);
	kAstarNode* addOpenNode(kAstarNode* node);
	kAstarNode* delOpenNode(kAstarNode* node);
	kAstarNode* getCloseNode(kAstarNode* node);
	kAstarNode* addCloseNode(kAstarNode* node);
	kAstarNode* delCloseNode(kAstarNode* node);
    
	void outputInfo(const char* extra);
};

#endif /* defined(__kAstar__) */
