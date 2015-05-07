#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <climits>
using namespace std;

class record{
public:
	int ID;
	string name;
	int score;
	string city;
};
struct radix_entry{
	record rec;
	int rem;
};

//SORT FUNCTIONS
void insertionSort();
void mergeSort(int, int);
void quickSort(int left, int right);
void radixSort();
void cocktailSort();
void qureshiSort();
void gnomeSort();
void rvaSort();

//FILE FUNCTIONs
void readFromFile();
void writeToFile(string fileName);
void writeToFile2(string fileName);
void sSwap( record& a, record& b );

//Global VARIABLES
vector<record> unsortedList;

int main(){

	bool exitChoice=1;

	do{
		cout<<"Reading List to Sort..."<<endl;
		unsortedList.reserve(100000);//change
//		sortedList.reserve(100000);
		readFromFile();

		cout<<"----------------------------------------------"<<endl;
		cout<<"Choose algorithm to use in sorting:"<<endl;
		cout<<"1- Insertion sort:"<<endl;
		cout<<"2- Merge sort:"<<endl;
		cout<<"3- Quick sort:"<<endl;
		cout<<"4- Radix sort:"<<endl;
		cout<<"5- Cocktail sort:"<<endl;
		cout<<"6- Qureshi sort:"<<endl;
		cout<<"7- Gnome sort:"<<endl;
		cout<<"8- RVA sort:"<<endl;
		cout<<"Enter 0 to Exit"<<endl;
		cout<<"----------------------------------------------"<<endl;

		int algorithmChoice;
		cin>>algorithmChoice;// Check if integer

		if(algorithmChoice==1){
			insertionSort();				
		}else if(algorithmChoice==2){
				mergeSort(0, unsortedList.size()-1);
				writeToFile("mergeSort");				
		}else if(algorithmChoice==3){				
			quickSort(0,unsortedList.size()-1);
			writeToFile("quickSort");
				
		}else if(algorithmChoice==4){
				radixSort();
		}else if(algorithmChoice==5){
				cocktailSort();
		}else if(algorithmChoice==6){
				qureshiSort();
		}else if(algorithmChoice==7){
				gnomeSort();
		}else if(algorithmChoice==8){
				rvaSort();
		}else if(algorithmChoice==0){
				exitChoice=0;
		}
		

	}while(exitChoice);
	

	system("PAUSE");
	return 0;
}

//FILE FUNCTIONS
void readFromFile(){
	string line;	
	ifstream file ("data1kck.csv");

	while ( file.good()) {	
		getline(file, line);
		stringstream  lineStream(line);
		string cell;
		record temp;
		int countElement=0;

		while(getline(lineStream,cell,',')){
			if(countElement==0){
				temp.ID=atoi(cell.c_str());
				countElement++;
			}else if(countElement==1){
				temp.name=cell;
				countElement++;
			}else if(countElement==2){
				temp.score=atoi(cell.c_str());
				countElement++;
			}else if(countElement==3){
				temp.city=cell;
				countElement++;
			}				
		}
		unsortedList.push_back(temp);
		//cout<<"id: " << temp.ID<<" name: "<<temp.name <<" score: "<<temp.score<<" city: "<<temp.city<<endl;
	}
}
void writeToFile(string fileName){

	ofstream file(fileName+".txt");
	cout<<"Writing results to file..."<<endl;
	for(int i=unsortedList.size()-1; i>=0; i--)
	{
		file<<unsortedList[i].ID<<"\t\t"<<unsortedList[i].name<<"\t\t"<<unsortedList[i].score<<"\t\t"<<unsortedList[i].city<<"\n";
	}

	file.close();
}


// SORT ALGORITHM FUNCTIONS
void insertionSort(){

	cout<<"Insertion sort..."<<endl;

	//clock_t start = clock() 

	for(int i = 1; i< unsortedList.size(); i++)
	{
		record x = unsortedList[i];
		int j = i;

		while(j>0 && unsortedList[j-1].score > x.score)
		{	
			unsortedList[j] = unsortedList[j-1];
			j = j-1; 
		}
		unsortedList[j] = x;
	}

	writeToFile("insertionSort");
}
void merge(int start, int middle, int end){
    record* left = new record[middle-start+1];

    for (int l_cnt=0; l_cnt<middle-start; l_cnt++){
        left[l_cnt] = unsortedList[start+l_cnt];
    }

	record newrecord;
	newrecord.score = numeric_limits<int>::max();
	
    left[middle-start] = newrecord;
    
	record* right = new record[end-middle+2];
    for (int r_cnt=0; r_cnt<end-middle+1; r_cnt++){
        right[r_cnt] = unsortedList[middle+r_cnt];
    }

    right[end-middle+1] = newrecord;
    
	int i = 0;
    int j = 0;
    for (int k=start; k<=end; k++){
		if (left[i].score < right[j].score){
            unsortedList[k] = left[i];
            i++;
        }
        else{
            unsortedList[k] = right[j];
            j++;
        }
    }

	delete [] left;
	delete [] right;
}
void mergeSort(int start, int end){
    if (start < end){
        int middle = int((end + start) / 2);
        mergeSort(start, middle);
        mergeSort(middle+1, end);
        merge(start, middle+1, end);
    }
}
void quickSort(int left, int right){
	  int i = left, j = right;

      record tmp;
	  int pivot =unsortedList[(left + right) / 2].score;
 
      /* partition */
      while (i <= j) {
            while (unsortedList[i].score < pivot)
                  i++;
            while (unsortedList[j].score > pivot)
                  j--;
            if (i <= j) {
                  tmp = unsortedList[i];
                  unsortedList[i] = unsortedList[j];
                  unsortedList[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      /* recursion */
      if (left < j)
            quickSort(left, j);
      if (i < right)
            quickSort(i, right);
	
}
void radixSort(){
	unsigned int div=1;
	unsigned int sh=32;

	vector<radix_entry> sortedList(unsortedList.size());	
	
	for(int i = 0; i< sortedList.size(); i++)	{
		sortedList[i].rec = unsortedList[i];
	}
	while(--sh){
		for(int i = 0; i< sortedList.size(); i++){
			sortedList[i].rem=sortedList[i].rec.score & div;
			for(int k = i; k>=1 ; --k){
				if(sortedList[k].rem < sortedList[k-1].rem){
					radix_entry temp = sortedList[k];
					sortedList[k] = sortedList[k - 1];
					sortedList[k-1] = temp;
				}
			}
		}
		div <<= 1; 
		
		cout <<"div "<<div<<endl;
		
	}

	for(int i = 0; i< sortedList.size(); i++)	{
		unsortedList[i] = sortedList[i].rec;
	}

	writeToFile("radixSort");
}
void gnomeSort(){

	int i = 0;
	record	temp;
	
	while( i < unsortedList.size() ){
		   
		if ( i == 0 || unsortedList[i - 1].score <= unsortedList[i].score )
			  i++;
		   
		   else{
				temp = unsortedList[i];
				unsortedList[i] = unsortedList[i - 1];
				i--;
				unsortedList[i] = temp;
		   }
	}
	writeToFile("gnomeSort");
}
void cocktailSort(){
	int len=unsortedList.size();
	bool notSorted = true;

	while( notSorted) {
	    notSorted = false;
	    for( int a = 0; a < len - 1; a++ )  {
			if( unsortedList[a].score > unsortedList[a + 1].score ){
				sSwap( unsortedList[a], unsortedList[a + 1] );
				notSorted = true;
			}
	    }
 
	    if( !notSorted ) break;
	    notSorted = false;
 
	    for( int a = len - 1; a > 0; a-- )  {
			if( unsortedList[a - 1].score > unsortedList[a].score ){
				sSwap( unsortedList[a], unsortedList[a - 1] );
				notSorted = true;
			}
	    }
	}

	writeToFile("cocktailSort");
}
void sSwap( record& a, record& b ){
	record t = a;
   	a = b; b = t;
}
void rvaSort(){
	int len=unsortedList.size();
	int c=(int) ceil(float(len)/2);	
	int k=0;
	int count=0;

	while(k<c) {
		count++;

		if((count%2)!=0){
			for( int a = 0; a < len - 1; a++ )  {
				if( unsortedList[a].score > unsortedList[a + 1].score ){
					sSwap( unsortedList[a], unsortedList[a + 1] );
				
				}
			}
		}
		
		else{
			for( int a = len - 1; a > 0; a-- )  {
				if( unsortedList[a - 1].score > unsortedList[a].score ){
					sSwap( unsortedList[a], unsortedList[a - 1] );				
				}
			}
		}  

		k++;
	   
	}
		
	writeToFile("rvaSort");
}
void qureshiSort(){
	int maxpoint = unsortedList[0].score;
	int minpoint = unsortedList[0].score;
	
	for(int i=1; i<unsortedList.size(); i++)
	{
		if(unsortedList[i].score > maxpoint)
			maxpoint = unsortedList[i].score;

		if(unsortedList[i].score < minpoint)
			minpoint = unsortedList[i].score;
	}


   //////////////////////////////////////////////////////////

	vector<vector<record>> ra;
	vector<int> da;

	for(int i=0; i<=maxpoint; i++){
		da.push_back(-1);
		vector<record> newvector;
		ra.push_back(newvector);
	}

    ///////////////////////////////////////////////////////////

	for(int i=0; i<unsortedList.size(); i++){
		int index = maxpoint - unsortedList[i].score;		
		da[index] = index;

		unsortedList[i].score=index;
		ra[index].push_back(unsortedList[i]);
	}


	///////////////////////////////////////////////////////////

	vector<record> answer;

	for(int i=0; i<=maxpoint; i++){
		if(da[i] != -1){
			int innerI=0;
			for(int j=1; j<=ra[i].size();j++){
				answer.push_back(ra[i][innerI]);
				answer.back().score=maxpoint-answer.back().score;
				innerI++;
			}		
		}
	}

	///////////////////////////////////////////////////////////
	unsortedList=move(answer);

	writeToFile2("qureshiSort");
}
void writeToFile2(string fileName){

	ofstream file(fileName+".txt");
	cout<<"Writing results to file..."<<endl;
	for(int i=0; i < unsortedList.size(); i++)
	{
		file<<unsortedList[i].ID<<"\t\t"<<unsortedList[i].name<<"\t\t"<<unsortedList[i].score<<"\t\t"<<unsortedList[i].city<<"\n";
	}

	file.close();
}
