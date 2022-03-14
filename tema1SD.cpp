#include <iostream>
#include <chrono>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

/////////////RadixSort/////////

//determinare maxim vector
int maxim(vector<int> &v,int n)
{
    int m=v[0];
    for(int i=0; i<n; i++)
        if(m<v[i]) m=v[i];
    return m;
}
//count sort
void countSort(vector<int> &v,int n,int exp)
{
    int rezultat[n];
    int i, frcif[10]= {0};
    for(i=0; i<n; i++)
        frcif[(v[i]/exp)%10]++;

    for(i=1; i<10; i++)
        frcif[i]+=frcif[i-1];
    for(i=n-1; i>=0; i--)
    {
        rezultat[frcif[(v[i]/exp)%10]-1]=v[i];
        frcif[(v[i]/exp)%10]--;
    }
    for(i=0; i<n; i++)
        v[i]=rezultat[i];
}
//radixSort
void RadixSort(vector<int> &v,int n)
{
    int m=maxim(v,n);
    for(int exp=1; m/exp>0; exp=exp*10)
        countSort(v,n,exp);
}
void afisare(vector<int> &v,int n)
{
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout<<endl;
}
bool testare(vector<int> & v, int n)
{
    for(int i = 1; i <n; i++)
        if(v[i] < v[i-1])
            return false;
    return true;
}

/////////////Final Radixsort/////////



////////////Inceput MergeSort//////////
void merge(vector<int> &v, int st, int mij, int dr)
{
    int temp[dr - st + 1];
    int i = st, j = mij+1, k = 0;
    while(i <= mij && j <= dr)
    {
        if(v[i] <= v[j])
        {
            temp[k] = v[i];
            k ++;
            i ++;
        }
        else
        {
            temp[k] = v[j];
            k ++;
            j ++;
        }
    }
    while(i <= mij)
    {
        temp[k] = v[i];
        k ++;
        i ++;
    }
    while(j <= dr)
    {
        temp[k] = v[j];
        k ++;
        j ++;
    }
    for(i = st; i <= dr; i += 1)
    {
        v[i] = temp[i - st];
    }
}
void MergeSort(vector<int> &v, int st, int dr)
{

    if(st< dr)
    {
        int mij = (st + dr) / 2;
        MergeSort(v, st, mij);
        MergeSort(v, mij+1, dr);
        merge(v, st, mij, dr);
    }
}
////////Final Merge sort///////////

///////Inceput Shell Sort//////////
void ShellSort(vector <int> &v, int n)
{
    int aux,interval,j,i;
    // Rearrange elements at each n/2, n/4, n/8, ... intervals
    for (interval=n/2; interval>0; interval=interval/2)
    {
        for (i=interval; i<n; i++)
        {
            aux = v[i];
            for (j=i; j>=interval && v[j-interval]>aux; j=j-interval)
            {
                v[j]=v[j-interval];
            }
            v[j]=aux;
        }
    }
}
//////////////Final Shellsort//////////////

/////////////Inceput QuickSort///////////
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
// varianta cu alegerea pivotului ca ultimul element din vector
int partitie(vector <int> &v, int st, int dr)
{
    int pivot,i,j;

    pivot = v[dr];
    i = (st - 1);
    for (j = st; j < dr; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(&v[i], &v[j]);
        }
    }

    swap(&v[i + 1], &v[dr]);

    return (i + 1);//partitia
}

void QuickSort(vector <int>  &v, int st, int dr)
{
    int pi;
    if (st < dr)
    {
        pi = partitie(v, st, dr);
        QuickSort(v, st, pi - 1);
        QuickSort(v, pi + 1, dr);
    }
}
//Quicksort mediana a 3 nr

int partitieMediana(vector <int> &v, int st, int dr)
{
    int pivot,i,j,x,y,z,aux,ix,iy,iz;
    x=v[st];
    y=v[(st+dr)/2];
    z=v[dr];

    ix=st;
    iy=(dr+st)/2;
    iz=dr;
    if(x>z)
    {
        aux=x;
        x=z;
        z=aux;
        aux=ix;
        ix=iz;
        iz=aux;
        if (y>z)
        {
            aux=y;
            y=z;
            z=aux;
            aux=iy;
            iy=iz;
            iz=aux;
        }
        else //x>y
        {
            aux=x;
            x=y;
            y=aux;
            aux=ix;
            ix=iy;
            iy=aux;
        }
    }
    else if (x>y)
    {
        aux=y;
        y=x;
        x=aux;
        aux=iy;
        iy=ix;
        ix=aux;
    }
    else if (y>z)
    {
        aux=y;
        y=z;
        z=aux;
        aux=iy;
        iy=iz;
        iz=aux;
    }
    //aux=v[iy];
    //v[iy]=v[dr];
    //v[dr]=aux;
    swap(&v[iy], &v[dr]);
    pivot = v[dr];
    i = (st - 1);
    for (j = st; j < dr; j++)
    {
        if (v[j] <= pivot)
        {
            i++;
            swap(&v[i], &v[j]);
        }
    }

    swap(&v[i + 1], &v[dr]);

    return (i + 1);//partitia
}

void QuickSortMediana(vector <int>  &v, int st, int dr)
{
    int pi;
    if (dr-st>=2)
    {
        pi = partitieMediana(v, st, dr);
        QuickSortMediana(v, st, pi - 1);
        QuickSortMediana(v, pi + 1, dr);
    }
    else if (dr-st==1)
        if(v[st]>v[dr])swap(&v[st], &v[dr]);

}
////////////Final Quicksort///////////

///////////Inceput heap sort///////

void heap(vector <int> &v, int n, int i)
{
    int maxx = i;
    int st = 2 * i + 1;
    int dr = 2 * i + 2;
    if (st<n && v[st]>v[maxx])
        maxx = st;

    if (dr<n && v[dr]>v[maxx])
        maxx = dr;

    if (maxx != i)
    {
        swap(v[i], v[maxx]);
        heap(v, n, maxx);
    }
}

void HeapSort(vector <int> &v, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(v, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(v[0], v[i]);
        heap(v, i, 0);
    }
}

/////////Final Heap sort/////////////
int main()
{
    ifstream f("fisier.in");
    long int n,maxx,nr;
    long int N;
    f>>N;
    vector<int> vct;
    vector <int>vct2;
    for(int i=0; i<N; i++)
    {
        f>>n>>maxx;
        cout<<"Testul "<<i+1<<":"<<endl;
        cout<<n<<" "<<maxx<<endl;
        srand((unsigned)time(0));
        for(int j=0; j<n; j++)
        {
            nr = rand()% maxx;
            vct.push_back(nr);
        }
        ///RadixSort
        if(n >=1000000)
            cout<<"RadixSort: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            RadixSort(vct,n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"Timp Radixsort : "<<duration.count()/1000000.00000000000000<<"s"<<endl;
            else
                cout << "Radixsort nu a sortat bine"<<endl;
            vct2.clear();
        }
        ///MERGESORT
        if(n >= 1000000)
            cout<<"MergeSort:Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start= high_resolution_clock::now();

            MergeSort(vct,0,n-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            if(testare(vct, n) == true)
                cout<<"Timp MergeSort : "<<duration.count()/1000000.00000000000000<<"s"<<endl;

            else
                cout << "MergeSort nu a sortat bine"<<endl;
            vct2.clear();
        }
        ///Shell Sort


        if(n >= 1000000)
            cout<<"ShellSort: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            ShellSort(vct,n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"Timp ShellSort : "<<duration.count()/1000000.00000000000000<<"s"<<endl;
            else
                cout << "ShellSort nu a sortat bine"<<endl;
            vct2.clear();
        }

        ///QuickSort
        //varianta cu pivotul luat ca ultimul element din vector

        if(n >= 100000)
            cout<<"QuickSort: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            QuickSort(vct,0,n-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"-Timp QuickSort pivotul=vct[dr]: "<<duration.count()/1000000.00000000000000<<"s"<<endl;

            else
                cout << "-QuickSort nu a sortat bine"<<endl;
            vct2.clear();
        }
        //varianta cu pivotul luat ca mediana din 3 elemente

        if(n >= 1000000)
            cout<<"-QuickSortMediana: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            QuickSortMediana(vct,0,n-1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"-Timp QuickSortMediana"<<": "<<duration.count()/1000000.00000000000000<<"s"<<endl;
            else
                cout << "-Timp QuickSortMediana nu a sortat bine"<<endl;
            vct2.clear();
        }

        //HeapSort

        if(n >= 1000000)
            cout<<"HeapSort: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            HeapSort(vct,n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"Timp HeapSort : "<<duration.count()/1000000.00000000000000<<"s"<<endl;
            else
                cout << "HeapSort nu a sortat bine"<<endl;
            vct2.clear();

        }
        ///algortimul de sortare nativ al c++
         if(n >= 1000000)
            cout<<"STL: Numar prea mare"<<endl;
        else
        {
            for(int j=0; j<n; j++)
            {
                vct2.push_back(vct[j]);
            }
            auto start = high_resolution_clock::now();
            sort(vct2.begin(), vct2.end());
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            if(testare(vct, n) == true)
                cout<<"Timp algortim sortare nativ: "<<duration.count()/1000000.00000000000000<<"s"<<endl;
            else
                cout << "Algortimul sortare nativ nu a sortat bine"<<endl;
            vct2.clear();

        }
        vct.clear();
        cout<<endl<<endl;

    }
    return 0;
}
