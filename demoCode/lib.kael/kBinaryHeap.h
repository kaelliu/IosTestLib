//
//  kBinaryHeap.h
//
//  Created by kael on 12/28/12.
//
//

#ifndef __kBinaryHeap__
#define __kBinaryHeap__

class kAstarNode;
class kAstarAlgorithm;
class kBinaryHeap
{
public:
    kBinaryHeap(kAstarAlgorithm* a);
    ~kBinaryHeap(void);
    void reinit();
    void initiate(int len);
    int left(int idx);
    int right(int idx);
    int parent(int idx);
    int value(int idx);
    
    void maxHeapify(int idx);
    void buildMaxHeap(void);
    void maxInsert(int idx, int id);
    int	 maximum(void);
    int	 maxExtract(void);
    void increaseKey(int idx, int id);
    
    void minHeapify(int idx);
    void buildMinHeap(void);
    void minInsert(int idx, int id);
    int	 minimum(void);
    int	 minExtract(void);
    int	 minRemove(int idx);
    void decreaseKey(int idx, int id);
    
    void heapSort(bool max=true);
    
    int  getF(int id);
    void setF(int id, int F);
    
    kAstarAlgorithm* algo;
    int* array;
    int length;
    int totalLen;
};

#endif /* defined(__kBinaryHeap__) */
