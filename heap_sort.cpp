#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
template <typename T>
class Heap
{
    private:
        std::vector<T> elements;

        int parent(const int& idx)
        {
            return (idx-1) / 2;
        }
        int leftChild(const int& idx)
        {
            return 2*idx + 1;
        }
        int rightChild(const int& idx)
        {
            return 2*idx + 2;
        }

    public:
        Heap()
        {
            elements.reserve(10);
        }
        Heap(const std::vector<T>& vect)
        {
            elements = vect;
            for(int i = (elements.size()-1) / 2; i >= 0; --i)
            {
                sink(i, elements.size() - 1);
            }

        }
        const std::vector<T>& getElements()
        {
            return elements;
        }

        void swap(const int& idx1, const int& idx2) {
            std::swap(elements[idx1], elements[idx2]);
        }

        void insertElement(const T& newValue)
        {

            elements.push_back(newValue);
            int currentIdx = elements.size();
            int swapIdx = parent(elements.size());

            while(currentIdx > 0 && elements[swapIdx] < newValue)
            {
                swap(currentIdx, swapIdx);
                currentIdx = swapIdx;
                swapIdx = parent(currentIdx);

            }
        }
        T removeMax()
        {
            if(elements.size() > 0)
            {
                T max = elements[0];
                elements[0] = elements.back();
                sink(0, elements.size()-2);
                return max;
            }
            else throw std::out_of_range("Heap is empty");
        }
        void sink(const int& idx1, const int& idx2)
        {
            int i = idx1;
            int left_idx = leftChild(i);
            bool isOver = false;

            while(left_idx <= idx2 && !isOver)
            {
                if(left_idx < idx2 && elements[left_idx + 1] > elements[left_idx])
                {
                    left_idx++;
                }
                if(elements[i] < elements[left_idx])
                {
                    swap(i, left_idx);
                    i = left_idx;
                    left_idx = leftChild(left_idx);
                }
                else
                {
                    isOver = true;
                }
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const Heap<T>& heap)
        {
            for(int i = 0; i < heap.elements.size(); i++)
            {
                os << heap.elements[i] << " ";                
            }
            os << "current lenght:  " << heap.elements.size();
            return os;
        }
};
template <typename T>
void heapSort(std::vector<T>& vect)
{
    Heap<T> heap(vect);

    int cnt = vect.size() - 1;
    while(cnt >= 0)
    {
        heap.swap(0,cnt);
        --cnt;
        heap.sink(0,cnt);
    }
    vect = heap.getElements();

}


int main()
{
    Heap<int> t;
    t.insertElement(15);
    t.insertElement(10);
    t.insertElement(50);
    t.insertElement(30);
    t.insertElement(20);
    std::cout << t << std::endl;
    std::cout << t.removeMax() << std::endl;
    std::cout << t.removeMax() << std::endl;
    std::cout << t.removeMax() << std::endl;
    t.insertElement(50);
    std::cout << t << std::endl;

    std::vector<int> vec(20);
    std::srand(std::time(nullptr));
    std::cout << "before sort" << std::endl;
    for (int& num : vec) {
        num = std::rand() % 100 + 1;
        std::cout << num << " ";
    }
    std::cout << std::endl << "after sort" << std::endl;
    heapSort(vec);
    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " " ;
    }

}