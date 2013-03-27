//
//  kAstar.cpp
//
//  Created by kael on 12/28/12.
//
//

#include "kAstar.h"
#include <stdio.h>
#include <stdlib.h>
int kAstarAlgorithm::getF(int c, int r)
{
    if( c>=0&&c<columnCount && r>=0&&r<rowCount)
	{
		return map[r*columnCount+c]->F;
	}
	return 0;
}

int kAstarAlgorithm::getF(int id)
{
	if( id<columnCount*rowCount )
	{
		return map[id]->F;
	}
	return 0;
}

kAstarNode* kAstarAlgorithm::getNode(int c, int r)
{
	if( c>=0&&c<columnCount && r>=0&&r<rowCount)
	{
		return map[r*columnCount+c];
	}
	return 0;// RETURN NULL POINTER
}

kAstarNode* kAstarAlgorithm::getNode(int id)
{
	if( id<columnCount*rowCount && 0<=id )
	{
		return map[id];
	}
	return 0;
}

kAstarNode* kAstarAlgorithm::allocNode(int blocked, int column, int row, int id)
{
	return new kAstarNode(blocked, column, row, id);
}

// choose the lowest F node.
kAstarNode* kAstarAlgorithm::getLowestOpenNode(void)
{
	kAstarNode* r = getNode(openArray.minimum());
	delOpenNode(r);
	addCloseNode(r);
	return r;
}

kAstarNode* kAstarAlgorithm::getOpenNode(kAstarNode* node)
{
	return node->s==1?node:0;
}

kAstarNode* kAstarAlgorithm::addOpenNode(kAstarNode* node)
{
	node->s = 1;
	openArray.minInsert(openArray.length+1, node->_id);
	return node;
}

kAstarNode* kAstarAlgorithm::delOpenNode(kAstarNode* node)
{
	if( !node ) return 0;
	node->s = 0;
	int id = openArray.minExtract();
	return getNode(id);
}

kAstarNode* kAstarAlgorithm::getCloseNode(kAstarNode* node)
{
	return node->s==2?node:0;
}

kAstarNode* kAstarAlgorithm::addCloseNode(kAstarNode* node)
{
	if( !node ) return 0;
	node->s = 2;
	closeArray.minInsert(closeArray.length+1, node->_id);
	return node;
}

kAstarNode* kAstarAlgorithm::delCloseNode(kAstarNode* node)
{
	node->s = 0;
	int id = closeArray.minExtract();
	return getNode(id);
}

kAstarNode* kAstarAlgorithm::getEndNode(void)
{
    return endNode;
}

kAstarNode* kAstarAlgorithm::getCurrNode(void)
{
	return currNode;
}

void kAstarAlgorithm::AStarSearchInit(kAstarNode* start, kAstarNode* end)
{
	searchTime = 0;
	if( !start || !end ) return;
	if( start==end ) return;
	startNode = start;
	endNode = end;
    
	//1.initiate the start node to open list.
	addOpenNode(startNode);
}

void kAstarAlgorithm::AStarSearchStep(void)
{
	if( !startNode || !endNode ) return;
	currNode = getLowestOpenNode();
	if( currNode && currNode!=endNode )
	{
		searchTime++;
		//2.traversal all around start node
		for(int i=-1; i<=1; i++) // 3*3 column search
		{
			for(int j=-1; j<=1; j++) // 3*3 row search
			{
				if(currNode->column_index+i>=0 && currNode->column_index+i<columnCount
                   && currNode->row_index+j>=0 && currNode->row_index+j<rowCount)
				{
					kAstarNode* n = getNode(currNode->column_index+i, currNode->row_index+j);
					if( n && !n->b && !getCloseNode(n) )
					{
						//3.calc the G,H,F
						calculateNode(n);
					}
				}
			}
		}
        
		char info[128];
		sprintf(info, "step:%d", searchTime);
		outputInfo(info);
	}
	else
		isStop = true;
}

kAstarNode* kAstarAlgorithm::AStarSearchRun(kAstarNode* start, kAstarNode* end)
{
	searchTime = 0;
	if( !start || !end ) return NULL;
	if( start==end ) return end;
	startNode = start;
	endNode = end;
    openArray.reinit();
    closeArray.reinit();
    for (int i=0; i<columnCount*rowCount; ++i) {
        map[i]->init();
    }
	//1.initiate the start node to open list.
	addOpenNode(startNode);
	currNode = getLowestOpenNode();
	while( currNode && currNode!=endNode )
	{
		searchTime++;
		//2.traversal all around start node
        if (type == TYPE_SQUARE) {
            for(int i=-1; i<=1; i++) // 3*3 column search
            {
                for(int j=-1; j<=1; j++) // 3*3 row search
                {
                    if(currNode->column_index+i>=0 && currNode->column_index+i<columnCount
                       && currNode->row_index+j>=0 && currNode->row_index+j<rowCount)
                    {
                        kAstarNode* n = getNode(currNode->column_index+i, currNode->row_index+j);
                        if( n && !n->b && !getCloseNode(n) )
                        {
                            //3.calc the G,H,F
                            calculateNode(n);
                        }
                    }
                }
            }
        }
		else if(type == TYPE_45DEGREE)
        {
            // four grid near by same row
            for(int i = -2;i<3;++i)
            {
                if(i == 0)continue;
                if(currNode->column_index+i>=0 && currNode->column_index+i<columnCount)
                {
                    kAstarNode* n = getNode(currNode->column_index+i, currNode->row_index);
                    if( n && !n->b && !getCloseNode(n) )
                    {
                        //3.calc the G,H,F
                        calculateNode(n);
                    }
                }
            }
            if(currNode->column_index % 2 == 0)// even column
            {
                // upper row
                if(currNode->row_index - 1 >= 0 && currNode->row_index-1<rowCount)
                {
                    for(int i = -1;i <= 1;++i)
                    {
                        if(currNode->column_index+i>=0 && currNode->column_index+i<columnCount)
                        {
                            kAstarNode* n = getNode(currNode->column_index+i, currNode->row_index-1);
                            if( n && !n->b && !getCloseNode(n) )
                            {
                                //3.calc the G,H,F
                                calculateNode(n);
                            }
                        }
                    }
                }
                // downer row
                if(currNode->column_index>=0 && currNode->column_index<columnCount
                   && currNode->row_index + 1 >= 0 && currNode->row_index + 1 < rowCount)
                {
                    kAstarNode* n = getNode(currNode->column_index, currNode->row_index+1);
                    if( n && !n->b && !getCloseNode(n) )
                    {
                        //3.calc the G,H,F
                        calculateNode(n);
                    }
                }
            }
            else// odd column
            {
                // upper row
                if(currNode->column_index >= 0 && currNode->column_index < columnCount
                   && currNode->row_index - 1 >= 0 && currNode->row_index - 1 < rowCount)
                {
                    kAstarNode* n = getNode(currNode->column_index, currNode->row_index-1);
                    if( n && !n->b && !getCloseNode(n) )
                    {
                        //3.calc the G,H,F
                        calculateNode(n);
                    }
                }
                // downer row
                if(currNode->row_index + 1 >= 0 && currNode->row_index + 1<rowCount)
                {
                    for(int i = -1;i <= 1;++i)
                    {
                        if(currNode->column_index+i>=0 && currNode->column_index+i<columnCount)
                        {
                            kAstarNode* n = getNode(currNode->column_index+i, currNode->row_index+1);
                            if( n && !n->b && !getCloseNode(n) )
                            {
                                //3.calc the G,H,F
                                calculateNode(n);
                            }
                        }
                    }
                }
            }
        }
		currNode = getLowestOpenNode();
//		outputInfo("stage 3");
	}
	return 0;
}

void kAstarAlgorithm::calculateNode(kAstarNode* node)
{
	if( !node ) return;
    
	int delta = 0;
//	if( abs(currNode->column_index-node->column_index)+abs(currNode->row_index-node->row_index)>1 )		//Diagonal distance
//		delta = 4;

	if( getOpenNode(node) )
	{
		int g = currNode->G + COST + delta;
		if( g<=node->G )
		{
			node->G = g;
			node->parent = currNode;
			node->H = abs(node->column_index - endNode->column_index)*COST + abs(node->row_index - endNode->row_index)*COST;
			node->F = node->G + node->H;
		}
	}
	else
	{
		node->G = currNode->G + COST + delta;
		node->parent = currNode;
		node->H = abs(node->column_index - endNode->column_index)*COST + abs(node->row_index - endNode->row_index)*COST;
		node->F = node->G + node->H;
		// add to open list
		addOpenNode(node);
	}
}

void kAstarAlgorithm::outputInfo(const char* extra)
{
	printf("%s:\n", extra);
	printf("start(id:%d,F:%d,G:%d,H:%d),end(id:%d,F:%d,G:%d,H:%d), curr(id:%d,F:%d,G:%d,H:%d)\n",
           startNode->_id,startNode->F,startNode->G,startNode->H,
           endNode->_id,endNode->F,endNode->G,endNode->H,
           !currNode?-1:currNode->_id,!currNode?-1:currNode->F,!currNode?-1:currNode->G,!currNode?-1:currNode->H);
    
	printf("open list:\n");
	for(int i=0; i<openArray.length; i++)
	{
		kAstarNode* an = getNode(openArray.array[i]);
		printf("node(id:%d,F:%d,G:%d,H:%d)\n",
               an->_id,an->F,an->G,an->H);
	}
	printf("close list:\n");
	for(int i=0; i<closeArray.length; i++)
	{
		kAstarNode* an = getNode(closeArray.array[i]);
		printf("node(id:%d,F:%d,G:%d,H:%d)\n",
               an->_id,an->F,an->G,an->H);
	}
}

void kAstarAlgorithm::TestCreateMap(int random)
{
//    columnCount = c;
//    rowCount = r;
	for(int i=0; i<columnCount; i++)
	{
		for(int j=0; j< rowCount; j++)
		{
			int blocked = 0;
			kAstarNode* node = allocNode(blocked, i, j, j*columnCount+i);
			map[j*columnCount+i] = node;
			if( node->b )
				printf("node:%d is blocked.\n", node->_id);
		}
	}
	
	map[3*columnCount+4]->b = 1;
	map[4*columnCount+4]->b = 1;
	map[5*columnCount+4]->b = 1;
}

void kAstarAlgorithm::createMap(const char* walkArr)
{
//    if(type == TYPE_SQUARE)
//    {
        for(int i=0; i< rowCount; i++)
        {
            for(int j=0; j< columnCount; j++)
            {
                int blocked = 0;
                kAstarNode* node = allocNode(blocked, j, i, i*columnCount+j);
                map[i*columnCount+j] = node;
                if( walkArr[i*columnCount+j] == '1' )// 1 is blocked in editor,change by yourself
                    map[i*columnCount+j]->b = 1;
                else
                    map[i*columnCount+j]->b = 0;
            }
        }
//    }
//    else if(type == TYPE_45DEGREE)
//    {
//        createMapEx(walkArr);
//    }
}

void kAstarAlgorithm::createMapEx(const char* walkArr)
{
    /* the thing is like this:
        0   2   4   6   8
          1   3   5   7
       but what we want is like this:
        0   1   2   3   4
          5   6   7   8
        so do the swap at evencolumn and oddcolumn
     */
    int blocked = 0;
    for(int i=0; i< rowCount; ++i)
	{
		for(int j=0; j< columnCount; j++)
		{
            kAstarNode* node;
			node = allocNode(blocked, j, i, i*columnCount+j);
			map[i*columnCount+j] = node;
            // extra one let it non block
            if(j == columnCount - 1 && (i % 2 == 0))
                map[i * columnCount + j]->b = 0;
            else
            {
                if(i % 2 == 0)
                {
                    // even row
                    if( walkArr[i / 2 * ((columnCount - 1) * 2 + 1) + j * 2] == '1' )// 1 is blocked in editor,change by yourself
                        map[i*columnCount+j]->b = 1;
                    else
                        map[i*columnCount+j]->b = 0;
                }
                else{
                    // odd row
                    if( walkArr[i / 2 * ((columnCount - 1) * 2 + 1) + j * 2 + 1] == '1' )// 1 is blocked in editor,change by yourself
                        map[i*columnCount+j]->b = 1;
                    else
                        map[i*columnCount+j]->b = 0;
                }
            }
		}
	}
}

void kAstarAlgorithm::TravelOutputResult(void)
{
	printf("travel time:%d output node:\n", searchTime);
	kAstarNode* p = endNode->parent;
	printf("back node(id:%d,F:%d,G:%d,H:%d,column:%d,row:%d)\n",
           endNode->_id,endNode->F,endNode->G,endNode->H,endNode->column_index,endNode->row_index);
	while( p )
	{
		printf("back node(id:%d,F:%d,G:%d,H:%d,column:%d,row:%d)\n",
               p->_id,p->F,p->G,p->H,p->column_index,p->row_index);
		p = p->parent;
	}
}