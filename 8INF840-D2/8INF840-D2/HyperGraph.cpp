#include "HyperGraph.h"
using namespace std;

template <typename T>
HyperGraph<T>::HyperGraph()
{
}

template <typename T>
HyperGraph<T>::~HyperGraph()
{
}

template class HyperGraph<string>;
template class HyperGraph<Page>;