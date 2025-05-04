#include <iostream>
#include <vector>
#include <Queue>
#include <Stack>
#include<fstream>
#include <algorithm>
#include<ctime>
#include <chrono>
#include <conio.h>
using namespace std::chrono;
using namespace std;
struct Organization_Data
{
    string index;
    string organizationID;
    string name;
    string website;
    string country;
    string discription;
    string founded;
    string industry;
    int employs;
};
struct lessThan
{
    inline bool operator()(Organization_Data &struct1, Organization_Data &struct2)
    {
    	
        return (struct1.employs < struct2.employs);
    }
};
class Organization_Class
{
	vector<Organization_Data> organization_vector;
	public:
	void storeDataInCSVfile(string line,int nanosec,int millisec,int second, int minute)
	{
		ofstream myFile;
		myFile.open("time taken by sorted_organizations.csv", ios::app);
		myFile << line << "," << nanosec <<"ns" << "," << millisec << "ms" << "," << second << "s" << "," << minute << "min" << endl;
		myFile.close();
	}
	void bucketSort(vector<Organization_Data> &array)
	{
		vector<Organization_Data> output;
		Organization_Data temp = array[0];
		int minValue = temp.employs;
		int maxValue = temp.employs;
		if(array.size() <= 1)
			return;
		
		for(int i = 0; i <array.size(); i++)
		{
			Organization_Data t = array[i];
			if(t.employs < minValue)
				minValue = t.employs;
			if(t.employs > maxValue)
				maxValue = t.employs;
		}
		int numberBuckets = maxValue - minValue + 1;
		vector<vector<Organization_Data>> buckets(numberBuckets);
		for(int i = 0; i < numberBuckets; i++)
		{
			buckets[i] = vector<Organization_Data>();
		}
		for(int i = 0; i < array.size(); i++)
		{
			Organization_Data t = array[i];
			int selectedBucket = (t.employs / numberBuckets);
			buckets[selectedBucket].push_back(array[i]);
		}
		for(int i = 0; i< numberBuckets; i++)
		{
			sort(buckets[i].begin(), buckets[i].end(),lessThan());
			for(int j = 0; j < buckets[i].size(); j++)
			{
				output.push_back(buckets[i][j]);
			}
		}
		for(int i = 0; i < array.size(); i++)
		{
			array[i]  = output[i];
		}
	}
	void countSort_Radix(vector<Organization_Data>& array, int exp)
	{
		int size = array.size();
		int max = getMax(array,size);
		vector<Organization_Data> output(size);
		vector<int>count(max+1,0);
		for(int i = 0; i < array.size(); i++)
		{
			Organization_Data temp = array[i];
			count[(temp.employs/exp) % 10]++;
		}
		for(int i = 1; i < 10; i++)
		{
			count[i] += count[i -1];
		}
		for(int i = array.size()-1; i >= 0; i--)
		{
			Organization_Data temp = array[i];
			output[count[(temp.employs/exp) % 10] - 1] = array[i];
			count[temp.employs/exp % 10]--;
		}
		for(int i = 0; i < array.size(); i++)
		{
			array[i] = output[i];
		}
	}
	void radixsort(vector<Organization_Data> &array)
    {
        int max = getMax(array,array.size());
        for (int exp = 1; max / exp > 0; exp *= 10)
            countSort_Radix(array, exp);
    }
	int getMax(vector<Organization_Data> array, int size) 
	{
		Organization_Data tempo = organization_vector[0];
	    int max = tempo.employs;
	   for(int i = 1; i < size; i++) 
	   {
	   		Organization_Data temp = array[i];
			if(temp.employs > max)
	    		max = temp.employs;
	   }
   		return max;
	}
	void countSort(vector<Organization_Data> & organization_vector)
	{
		int size = organization_vector.size();
		int max = getMax(organization_vector, size);
		vector<int> count(max + 1);
		vector<Organization_Data> output(size);
		
//		initialize count array to all zero
		for(int i = 0; i<=max; i++)
			count[i] = 0;
			
//		increase number count in count array.	
		for(int i = 0; i < size; i++)
		{
			Organization_Data temp = organization_vector[i];
			count[temp.employs]++;
		}
		
//		find cumulative frequency
		for(int i = 1; i<=max; i++)
			count[i] += count[i-1];
			
		for(int i = size - 1; i >= 0; i--) 
		{
			Organization_Data temp = organization_vector[i];
			int cont  = count[temp.employs - 1];
			output[count[temp.employs - 1]] = organization_vector[i];
			count[temp.employs] -= 1;
		}
		for(int i = 0; i < size; i++)
		{
			organization_vector[i] = output[i];
		}
	}
	int parentIndex(int i)
    {
        return (i - 1) / 2;
    }
    
    int leftChildIndex(int i)
    {
        return (2 * i) + 1;
    }
    
    int rightChildIndex(int i)
    {
        return (2 * i) + 2;
    }

    void heapify(vector<Organization_Data>& heapArr, int size, int index)
    {
        int maxIndex;
        while (true)
        {
            int lIdx = leftChildIndex(index);
            int rIdx = rightChildIndex(index);
            if (rIdx >= size)
            {
                if (lIdx >= size)
                    return;
                else
                    maxIndex = lIdx;
            }
            else
            {
            	Organization_Data temp1 = heapArr[lIdx];
            	Organization_Data temp2 = heapArr[rIdx];
                if (temp1.employs >= temp2.employs)
                    maxIndex = lIdx;
                else
                    maxIndex = rIdx;
            }
            Organization_Data temp1 = heapArr[index];
            Organization_Data temp2 = heapArr[maxIndex];
            if (temp1.employs < temp2.employs)
            {
                swap(heapArr[index], heapArr[maxIndex]);
                index = maxIndex;
            }
            else
                return;
            }
    }
    vector<Organization_Data> heapSort()
    {
    	int size = organization_vector.size();
        for (int x = (size / 2) - 1; x >= 0; x--)
        {
            heapify(organization_vector, size, x);
        }
        for (int x = size - 1; x > 0; x--)
        {
            swap(organization_vector[0], organization_vector[x]);
            heapify(organization_vector, x, 0);
        }
        return organization_vector;
    }
	int partition(vector<Organization_Data>& array, int low, int high) 
	{
//		select the rightmost element as pivot
		Organization_Data pivotTemp = array[high];
		int pivot = pivotTemp.employs;
		int i = (low - 1);
		for (int j = low; j < high; j++) 
		{
			Organization_Data temp = array[j];
			if (temp.employs <= pivot) 
			{
				i++;
				swap(array[i],array[j]);
			}
		}
		swap(array[i+1], array[high]);
		return (i+1);
    }

    void quickSort(vector<Organization_Data>& array, int low, int high) 
	{
		vector<int>stack(high - low+1);
		int top = -1;
		stack[++top] = low;
		stack[++top] = high;
		while(top >= 0)
		{
			high = stack[top--];
			low = stack[top--];
			int p = partition(array,low,high);
			if(p-1 > low)
			{
				stack[++top] = low;
				stack[++top] = p-1;
			}
			if(p+1 < high)
			{
				stack[++top] = p + 1;
				stack[++top] = high;
			}
	   }
	}
	void merge(vector<Organization_Data>& arr, int start, int mid, int end)
	{
		int i = start;
		int j = mid + 1;
		queue<Organization_Data> tempArr;
		while (i <= mid && j <= end)
		{
			Organization_Data temp1 = arr[i];
			Organization_Data temp2 = arr[j];
			if (temp1.employs < temp2.employs)
			{
				tempArr.push(arr[i]);
				i++;
			}
			else
			{
				tempArr.push(arr[j]);
				j++;
			}
		}
		while (i <= mid)
		{
			tempArr.push(arr[i]);
			i++;
		}
		while (j <= end)
		{
			tempArr.push(arr[j]);
			j++;
		}
		for (int x = start; x <= end; x++)
		{
			arr[x] = tempArr.front();
			tempArr.pop();
		}
	}

	void mergeSort(vector<Organization_Data>& arr, int start, int end)
	{
		if (start < end)
		{
			int mid = (start + end) / 2;
			mergeSort(arr, start, mid);
			mergeSort(arr, mid + 1, end);
			merge(arr, start, mid, end);
		}	
	}
	vector<Organization_Data> insertionSort()
    {
        for (int i = 1; i < organization_vector.size(); i++)
        {
        	Organization_Data temp = organization_vector[i];
            int key = temp.employs;
            int j;
            Organization_Data temp2 = organization_vector[i - 1];
            if (key < temp2.employs)
            {
                for (j = i - 1; j >= 0; j--)
                {
                    organization_vector[j + 1] = organization_vector[j];
                    Organization_Data temp3 = organization_vector[j];
                    if (key > temp3.employs)
                        break;
                }
                organization_vector[j + 1] = temp;
            }
        }
        return organization_vector;
    }
	int findMinimum(int start, int end)
	{
		Organization_Data temp = organization_vector[start];
		int min = temp.employs;
		int minIndex = start;
		for(int x = start; x < end; x++)
		{
			Organization_Data temp2 = organization_vector[x];
			if(min > temp2.employs)
			{
				min = temp2.employs;
				minIndex = x;
			}
		}
		return minIndex;
	}
	vector<Organization_Data> selectionSort()
	{
		int n = organization_vector.size();
		for(int x = 0; x < n - 1; x++)
		{
			int minIndex = findMinimum(x, n);
			swap(organization_vector[x], organization_vector[minIndex]);
		}
		return organization_vector;
	}

	vector<Organization_Data> bubbleSort()
	{
		int n = organization_vector.size();
		bool isSwapped = false;
		for (int x = 0; x < n - 1; x++)
		{
			for (int y = 0; y < n - x - 1; y++)
			{
				Organization_Data temp = organization_vector[y];
				int employs = temp.employs;
				Organization_Data temp2 = organization_vector[y+1];
				int next_employs = temp2.employs;
				if (employs > next_employs)
				{
					swap(organization_vector[y], organization_vector[y + 1]);
					isSwapped = true;
				}
			}
			if (!isSwapped)
			{
				break;
			}

		}
		return organization_vector;
	}

	vector<Organization_Data> returnVector()
	{
		return organization_vector;
	}
	void insert_in_vector(Organization_Data data)
	{
		organization_vector.push_back(data);
	}	
	void createStruct(string idx,string org_id,string n,string web,string cntry,string discrip,string found,string indstry,string emplys)
	{
		Organization_Data data;
	    data.index = idx;
	    data.organizationID = org_id;
	    data.name = n;
	    data.website = web;
	    data.country = cntry;
	    data.discription = discrip;
	    data.founded = found;
	    data.industry = indstry;
	    data.employs = stoi(emplys);
	    insert_in_vector(data);
	}
	string parseData(string record,int field)
	{
		int comma = 1;
		string item = "";
		for(int x=0; x<record.length(); x++)
		{
		    if(record[x] == ','){
		        comma++;
		    }
		    else if(comma == field){
		        item = item + record[x];
		    }
		}
		return item;
	}
	void make_an_object(string line)
	{
	    string index = parseData(line,1);
	    string organizationID = parseData(line,2);
	    string name = parseData(line,3);
	    string website = parseData(line,4);
	    string country = parseData(line,5);
	    string discription = parseData(line,6);
	    string founded = parseData(line,7);
	    string industry = parseData(line,8);
	    string employs = parseData(line,9);
	    createStruct(index,organizationID,name,website,country,discription,founded,industry,employs);
	}
	void traverse_1000_csv()
	{
	    int count = 1;
	    string line;
	    ifstream myFile;
	    myFile.open("./assets/organizations-1000.csv");
	    while (myFile.good())
	    {
	        if(count == 1)
	        {
	            getline(myFile,line); 
	            count++;
	        }
	        else if(count <=1001 && count>=2)
	        {
	            getline(myFile,line);
	            make_an_object(line);
	            count++;
	        }
	        else 
	        {
	            getline(myFile,line);
	        }
	    }
	}
	
	void traverse_10000_csv()
	{
	    int count = 1;
	    string line;
	    ifstream myFile;
	    myFile.open("./assets/organizations-10000.csv");
	    while (myFile.good())
	    {
	        if(count == 1)
	        {
	            getline(myFile,line); 
	            count++;
	        }
	        else if(count <=10001 && count>=2)
	        {
	            getline(myFile,line); 
	            make_an_object(line);
	            count++;
	        }
	        else 
	        {
	            getline(myFile,line);
	        }
	    }
	}
	void traverse_100000_csv()
	{
	    int count = 1;
	    string line;
	    ifstream myFile;
	    myFile.open("./assets/organizations-100000.csv");
	    while (myFile.good())
	    {
	        if(count == 1)
	        {
	            getline(myFile,line); 
	            count++;
	        }
	        else if(count <=100001 && count>=2)
	        {
	            getline(myFile,line); 
	            make_an_object(line);
	            count++;
	        }
	        else 
	        {
	            getline(myFile,line);
	        }
	    }
	}
	void traverse_500000_csv()
	{
	    int count = 1;
	    string line;
	    ifstream myFile;
	    myFile.open("./assets/organizations-500000.csv");
	    while (myFile.good())
	    {
	        if(count == 1)
	        {
	            getline(myFile,line); 
	            count++;
	        }
	        else if(count <=500001 && count>=2)
	        {
	            getline(myFile,line); 
	            make_an_object(line);
	            count++;
	        }
	        else 
	        {
	            getline(myFile,line);
	        }
	    }
	}
	void traverse_100_csv()
	{
	    int count = 1;
	    string line;
	    ifstream myFile;
	    myFile.open("./assets/organizations-100.csv");
	    while (myFile.good())
	    {
	        if(count == 1)
	        {
	            getline(myFile,line); 
	            count++;
	        }
	        else if(count <=101 && count>=2)
	        {
	            getline(myFile,line); 
	            make_an_object(line);
	            count++;
	        }
	        else 
	        {
	            getline(myFile,line);
	        }
	    }
	}
};
string mainMenu();
string subMenu();
int main()
{
	while(true)
	{
		string mainOp = mainMenu();
		if(mainOp == "1")
		{
			Organization_Class oc;
			oc.traverse_100_csv();
//			load 100 records
			while(true)
			{
				string subOp = subMenu();
				if(subOp == "1")
				{
//					Bubble sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.bubbleSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bubble Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "2")
				{
//					selection sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.selectionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Selection Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "3")
				{
//					insertion sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.insertionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Insertion Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "4")
				{
//					merge sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.mergeSort(temp, 0, temp.size()-1);
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Merge Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "5")
				{
// 					Quick sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> nums = oc.returnVector();
					oc.quickSort(nums, 0, nums.size() - 1);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Quick Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < nums.size(); x++)
			        {
			            Organization_Data t = nums[x];
						cout << t.employs << " ";
			        }
			        cout << endl;
				}
				else if(subOp == "6")
				{
// 					Heap sort
					auto start = high_resolution_clock::now();
			        vector<Organization_Data> temp = oc.heapSort();
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Heap Sorting of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "7")
				{
// 					counting sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.countSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Counting Sort of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "8")
				{
//					Radix sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.radixsort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Radix Sort of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "9")
				{
//					Bucket sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.bucketSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bucket Sort of 100 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "10")
				{
					break;
				}
				else
				{
					cout << "Wrong Option\n";
				}
			}
		}
		else if(mainOp == "2")
		{
//			load 1000 records
			Organization_Class oc;
			oc.traverse_1000_csv();
			while(true)
			{
				string subOp = subMenu();
				if(subOp == "1")
				{
//					Bubble sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.bubbleSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bubble Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "2")
				{
//					selection sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.selectionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Selection Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "3")
				{
//					insertion sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.insertionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Insertion Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "4")
				{
//					merge sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.mergeSort(temp, 0, temp.size()-1);
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Merge Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "5")
				{
// 					Quick sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> nums = oc.returnVector();
					oc.quickSort(nums, 0, nums.size() - 1);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Quick Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < nums.size(); x++)
			        {
			            Organization_Data t = nums[x];
						cout << t.employs << " ";
			        }
			        cout << endl;
				}
				else if(subOp == "6")
				{
// 					Heap sort
					auto start = high_resolution_clock::now();
			        vector<Organization_Data> temp = oc.heapSort();
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Heap Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "7")
				{
// 					counting sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.countSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Counting Sorting of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "8")
				{
//					Radix sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.radixsort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Radix Sort of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "9")
				{
//					Bucket sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.bucketSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bucket Sort of 1000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "10")
				{
					break;
				}
				else
				{
					cout << "Wrong Option\n";
				}
			}
		}
		else if(mainOp == "3")
		{
//			load 10000 records
			Organization_Class oc;
			oc.traverse_10000_csv();
			while(true)
			{
				string subOp = subMenu();
				if(subOp == "1")
				{
//					Bubble sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.bubbleSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bubble Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "2")
				{
//					selection sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.selectionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Selection Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "3")
				{
//					insertion sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.insertionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Insertion Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "4")
				{
//					merge sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.mergeSort(temp, 0, temp.size()-1);
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Merge Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "5")
				{
// 					Quick sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> nums = oc.returnVector();
					oc.quickSort(nums, 0, nums.size() - 1);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Quick Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < nums.size(); x++)
			        {
			            Organization_Data t = nums[x];
						cout << t.employs << " ";
			        }
			        cout << endl;
				}
				else if(subOp == "6")
				{
// 					Heap sort
					auto start = high_resolution_clock::now();
			        vector<Organization_Data> temp = oc.heapSort();
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Heap Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "7")
				{
// 					counting sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.countSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Count Sorting of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "8")
				{
//					Radix sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.radixsort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Radix Sort of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "9")
				{
//					Bucket sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.bucketSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bucket Sort of 10000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "10")
				{
					break;
				}
				else
				{
					cout << "Wrong Option\n";
				}
			}
		}
		else if(mainOp == "4")
		{
//			load 100000 records
			Organization_Class oc;
			oc.traverse_100000_csv();
			while(true)
			{
				string subOp = subMenu();
				if(subOp == "1")
				{
//					Bubble sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.bubbleSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bubble Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "2")
				{
//					selection sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.selectionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Selection Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "3")
				{
//					insertion sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.insertionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Insertion Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "4")
				{
//					merge sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.mergeSort(temp, 0, temp.size()-1);
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Merge Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "5")
				{
// 					Quick sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> nums = oc.returnVector();
					oc.quickSort(nums, 0, nums.size() - 1);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Quick Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < nums.size(); x++)
			        {
			            Organization_Data t = nums[x];
						cout << t.employs << " ";
			        }
			        cout << endl;
				}
				else if(subOp == "6")
				{
// 					Heap sort
					auto start = high_resolution_clock::now();
			        vector<Organization_Data> temp = oc.heapSort();
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Heap Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "7")
				{
// 					counting sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.countSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Count Sorting of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "8")
				{
//					Radix sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.radixsort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Radix Sort of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "9")
				{
//					Bucket sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.bucketSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bucket Sort of 100000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "10")
				{
					break;
				}
				else
				{
					cout << "Wrong Option\n";
				}
			}
		}
		else if(mainOp == "5")
		{
//			load 500000 records
			Organization_Class oc;
			oc.traverse_500000_csv();
			while(true)
			{
				string subOp = subMenu();
				if(subOp == "1")
				{
//					Bubble sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.bubbleSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bubble Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "2")
				{
//					selection sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.selectionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Selection Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "3")
				{
//					insertion sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> organization_vector = oc.insertionSort();
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Insertion Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < organization_vector.size(); x++)
					{
						Organization_Data temp = organization_vector[x];
						cout << temp.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "4")
				{
//					merge sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.mergeSort(temp, 0, temp.size()-1);
					
				    auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Merge Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "5")
				{
// 					Quick sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> nums = oc.returnVector();
					oc.quickSort(nums, 0, nums.size() - 1);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Quick Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < nums.size(); x++)
			        {
			            Organization_Data t = nums[x];
						cout << t.employs << " ";
			        }
			        cout << endl;
					
				}
				else if(subOp == "6")
				{
// 					Heap sort
					auto start = high_resolution_clock::now();
			        vector<Organization_Data> temp = oc.heapSort();
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Heap Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						cout << t.employs << " ";
					}
					cout << endl;
				}
				else if(subOp == "7")
				{
// 					counting sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.countSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Count Sorting of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
			        for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "8")
				{
//					Radix sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.radixsort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Radix Sort of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "9")
				{
//					Bucket sort
					auto start = high_resolution_clock::now();
					vector<Organization_Data> temp = oc.returnVector();
					oc.bucketSort(temp);
					auto end = high_resolution_clock::now();
				    auto millisec = duration_cast<milliseconds>(end - start);
				    auto nanosec = duration_cast<nanoseconds>(end-start);
				    auto second = duration_cast<seconds>(end-start);
				    auto minute = duration_cast<minutes>(end-start);
					oc.storeDataInCSVfile("Bucket Sort of 500000 records",nanosec.count(), millisec.count(),second.count(),minute.count());
					for (int x = 0; x < temp.size(); x++)
					{
						Organization_Data t = temp[x];
						if(t.employs != 0)
						{
						cout << t.employs << " ";
						}
					}
					cout << endl;
				}
				else if(subOp == "10")
				{
					break;
				}
				else
				{
					cout << "Wrong Option\n";
				}
			}
		}
		else if(mainOp == "6")
		{
			break;
		}
		else
		{
			cout << "Wrong Option\n";
		}
	}
}

string mainMenu()
{
    cout << "1.Load 100 Records\n";
    cout << "2.Load 1000 Records\n";
    cout << "3.Load 10000 Records\n";
    cout << "4.Load 100000 Records\n";
    cout << "5.Load 500000 Records\n";
    cout << "6.Exit\n";
    cout << "Your Option:";
    string op;
    cin >> op;
    return op;
}
string subMenu()
{
	cout << "1.Bubble Sort\n";
	cout << "2.Selection Sort\n";
	cout << "3.Insertion Sort\n";
	cout << "4.Merge Sort\n";
	cout << "5.Quick Sort\n";
	cout << "6.Heap Sort\n";
	cout << "7.Counting Sort\n";
	cout << "8.Radix Sort\n";
	cout << "9.Bucket Sort\n";
	cout << "10.Exit\n";
	cout << "Your Option:";
    string op;
    cin >> op;
    return op;
}

