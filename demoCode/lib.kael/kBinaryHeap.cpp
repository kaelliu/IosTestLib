//
//  kBinaryHeap.cpp
//
//  Created by kael on 12/28/12.
//

#include "kBinaryHeap.h"
#include "kAstar.h"
#include <memory>
kBinaryHeap::kBinaryHeap(kAstarAlgorithm* a): algo(a), array(0), length(0)
{
	initiate(10*10);// need to be changed
}

kBinaryHeap::~kBinaryHeap(void)
{
	delete[] array;
}

void kBinaryHeap::reinit()
{
    memset(array, 0, sizeof(int)*totalLen);
    length = 0;
}

void kBinaryHeap::initiate(int len)
{
	if( len<1 ) return;
	totalLen = len;
	array = new int[len];
	length = 0;
	memset(array, 0, sizeof(int)*len);
}

int kBinaryHeap::left(int index)
{
//	index = index;
	return index*2;
}

int kBinaryHeap::right(int index)
{
    //	if( index<0 || (index*2+1)>=length ) return 0;
	return (index*2+1);
}

int kBinaryHeap::parent(int index)
{
    //	if( index<1 || index >=length ) return 0;
	return index/2;
}


int kBinaryHeap::value(int index)
{
    //	if( index<0 || index >=length ) return 0;
	return array[index-1];
}

int  kBinaryHeap::getF(int id)
{
	kAstarNode* n = algo->getNode(id);
	if( n ) return n->F;
	return 0;
}

void kBinaryHeap::setF(int id, int F)
{
	kAstarNode* n = algo->getNode(id);
	if( n ) n->F = F;
}

void kBinaryHeap::maxHeapify(int idx)
{
	int l = left(idx);
	int r = right(idx);
	int largest = 0;
	if( l<=length && getF(array[l-1])>getF(array[idx-1]) )
	{
		largest = l;
	}
	else
	{
		largest = idx;
	}
	if( r<=length && getF(array[r-1])>getF(array[largest-1]) )
	{
		largest = r;
	}
	if( largest!=idx )
	{
		int tmp = array[idx-1];
		array[idx-1] = array[largest-1];
		array[largest-1] = tmp;
		maxHeapify(largest);
	}
}

void kBinaryHeap::buildMaxHeap(void)
{
	for(int i=length/2; i>0; i--)
	{
		maxHeapify(i);
	}
}

void kBinaryHeap::maxInsert(int idx, int id)
{
	length++;
	array[length] = id;
	increaseKey(idx, id);
}

int	 kBinaryHeap::maximum(void)
{
	return array[0];
}

int	 kBinaryHeap::maxExtract(void)
{
	if( length<1 ) return 0;
	int max = array[0];
	array[0] = array[length-1];
	length--;
	maxHeapify(1);
	return max;
}

void kBinaryHeap::increaseKey(int idx, int id)
{
	if( getF(id)<getF(array[idx-1]) ) return;
	array[idx-1] = id;
	while( idx>1 && getF(array[parent(idx)-1])<getF(array[idx-1]) )
	{
		int tmp = array[idx-1];
		array[idx-1] = array[parent(idx)-1];
		array[parent(idx)-1] = tmp;
		idx = parent(idx);
	}
}

void kBinaryHeap::minHeapify(int idx)
{
	int l = left(idx);
	int r = right(idx);
	int smallest = 0;
	if( l<=length && getF(array[l-1])<getF(array[idx-1]) )
	{
		smallest = l;
	}
	else
	{
		smallest = idx;
	}
	if( r<=length && getF(array[r-1])<getF(array[smallest-1]) )
	{
		smallest = r;
	}
	if( smallest!=idx )
	{
		int tmp = array[idx-1];
		array[idx-1] = array[smallest-1];
		array[smallest-1] = tmp;
		minHeapify(smallest);
	}
}

void kBinaryHeap::buildMinHeap(void)
{
	for(int i=length/2; i>0; i--)
	{
		minHeapify(i);
	}
}

void kBinaryHeap::minInsert(int idx, int id)
{
	array[length] = id;
	length++;
	decreaseKey(idx, id);
}

int	 kBinaryHeap::minimum(void)
{
	return length?array[0]:-1;
}

int	 kBinaryHeap::minExtract(void)
{
	if( length<1 ) return 0;
	int min = array[0];
	array[0] = array[length-1];
	length--;
	minHeapify(1);
	return min;
}

int	 kBinaryHeap::minRemove(int idx)
{
	if( length<1 ) return 0;
	int min = array[idx-1];
	array[idx-1] = array[length-1];
	length--;
	minHeapify(1);
	return min;
}

void kBinaryHeap::decreaseKey(int idx, int id)
{
	if( getF(id)>getF(array[idx-1]) ) return;
	array[idx-1] = id;
	while( idx>1 && getF(array[parent(idx)-1])>getF(array[idx-1]) )
	{
		int tmp = array[idx-1];
		array[idx-1] = array[parent(idx)-1];
		array[parent(idx)-1] = tmp;
		idx = parent(idx);
	}
}

void kBinaryHeap::heapSort(bool max)
{
	if( max )
	{
		buildMaxHeap();
		for(int i=length; i>=2; i--)
		{
			int tmp = array[1-1];
			array[1-1] = array[i-1];
			array[i-1] = tmp;
			length--;
			maxHeapify(1);
		}
	}
	else
	{
		buildMinHeap();
		for(int i=length; i>=2; i--)
		{
			int tmp = array[1-1];
			array[1-1] = array[i-1];
			array[i-1] = tmp;
			length--;
			minHeapify(1);
		}
	}
}
