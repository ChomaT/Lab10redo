//============================================================================
// Name        : main2.cpp
// Author      : Theo Choma
// Version     :
// Copyright   : 
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;


class Exception{
    public:
        int num;
        Exception();
        ~Exception();
};

Exception::Exception(){
    int num = 0;
}

Exception::~Exception(){
}


//Signal class definition
class Signal{
	public:
		//double *data;
        vector<double> data;
		int length;
		double max;
		double avg;
	public:
		Signal();		// default constructor.
		Signal(int);            // parametric constructor file number
        Signal(string);         //parametric constructor file name
		~Signal();		// destructor
		void operator+(double factor);
		void operator*(double factor);
		void Offset() throw(int);
		void Scale();
		void Center();
		void Normalize();
		void Statistics();
		void Sig_info();
		void Save_file(string);
};




//default constructor
Signal::Signal(){
	length = 0;
	max = 0;
	avg = 0;
}




//parametric integer constructor
Signal::Signal(int L){
	double i = 0;
	double sum = 0;
	length = 0;
	max = 0;
	avg = 0;
	string fname;
	char str[25] = {'\0'};

	ifstream fpointer;
        
	if ( L < 10 && L > 0)
	{
		sprintf(str,"Raw_data_0%d.txt",L);
		fname = str;
		cout<<"Opening File: "<<str<<endl;
		fpointer.open(fname.c_str(), ios::in);
	}
	else if (L < 20)
	{
		sprintf(str,"Raw_data_%d.txt",L);
		fname = str;
		cout<<"Opening File: "<<str<<endl;
		fpointer.open(fname.c_str(), ios::in);
	}
        else
        {
            throw 1;
        }

	if (fpointer.is_open())
	{
		fpointer >> length >> max;
		while(!fpointer.eof())
		{
			fpointer >> i;
			data.push_back(i);
			i++;
		}
		fpointer.close();
	}

	//Define avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = sum / (double) length;

	max = data[0];
	for(i = 0; i < length; i++)
	{
		if(data[i] > max)
		{
			max = data[i];
		}
	}
}




//Parametric string constructor
Signal::Signal(string instr){
	double i = 0;
	double sum = 0;
	length = 0;
	max = 0;
	avg = 0;
	string fname = instr + ".txt";

	ifstream fpointer;
	fpointer.open(fname.c_str(), ios::in);


	if (fpointer.is_open())
	{
		fpointer >> length >> max;
		while(!fpointer.eof())
		{

			fpointer >> i;
			data.push_back(i);
			i++;
		}
		fpointer.close();
	}

	//Define avg
	for (i = 0; i < length; i++)
	{
		sum = sum + data[i];
	}
	avg = sum / (double) length;

	max = data[0];
	for(i = 0; i < length; i++)
	{
		if(data[i] > max)
		{
			max = data[i];
		}
	}
}




//deconstructor
Signal::~Signal(){
	//delete[] data;	// no need to delete vector
}




//operator overload +
void Signal :: operator+(double factor)
{
        int sum = 0;

        if (length == 0)
            throw 2;
       
       	for(int i = 0; i < length; i++)
        {
            data[i] = data[i] + factor;
        }

        //Redefine avg
        for (int i = 0; i < length; i++)
        {
            sum = sum + data[i];
        }
        avg = sum / (double) length;

        //Redefine max
    	max = data[0];
    	for(int i = 0; i < length; i++)
    	{
    		if(data[i] > max)
    		{
    			max = data[i];
    		}
    	}
}




//operator overload *
void Signal :: operator*(double factor)
{
        int sum = 0;

        if (length == 0)
            throw 2;
        
       	for(int i = 0; i < this->length; i++)
        {
            this->data[i] = this->data[i] * factor;
        }

        //Redefine avg
        for (int i = 0; i < this->length; i++)
        {
            sum = sum + this->data[i];
        }
        this->avg = sum / (double) this->length;

        //Redefine max
    	this->max = this->data[0];
    	for(int i = 0; i < this->length; i++)
    	{
    		if(this->data[i] > this->max)
    		{
    			this->max = this->data[i];
    		}
    	}
}




//Centering function
void Signal::Center()
{
    if (length == 0)
        throw 2;
    
    int factor = -avg;
    (*this)+factor;
}




//Normalization function
void Signal::Normalize()
{
    if (length == 0)
        throw 2;

    double factor = (1/max);
    (*this)*factor;

}




//Offset function
void Signal::Offset() throw(int)
{
    if (length == 0)
        throw 2;	
    
    int i = 0, factor;
	double sum;

	cout << "Input an offset factor: ";
	cin >> factor;
	if(factor <= 1000 && factor >= -1000)
	{
		for(i = 0; i < length; i++)
		{
			data[i] = data[i] + factor;
		}

		//Redefine avg
		for (i = 0; i < length; i++)
		{
			sum = sum + data[i];
		}
		avg = sum / (double) length;

        //Redefine max
    	max = data[0];
    	for(int i = 0; i < length; i++)
    	{
    		if(data[i] > max)
    		{
    			max = data[i];
    		}
    	}

	}
        else
        {
			cout<<"Input error: please choose a value between -1000 and 1000."<<endl;
        }
}




//Signal Info printing function
void Signal::Sig_info()
{
	cout<<"Length: " << length << endl << "Max: " << max << endl << "Average: " << avg << endl;
}




//Saving file function
void Signal::Save_file(string outstr)
{
	fstream outstream;
	string fname = outstr + ".txt";
	outstream.open (fname.c_str(), ios::out);
	if(outstream.is_open())
	{
		outstream << length << " "<< max << endl;
		for(int i = 0; i < length; i++)
		{
			outstream << data[i] << endl;
		}
		outstream.close();
	}
	else
	{
		cout<<"File stream output error"<<endl;
	}
}



//+ operator non-member overwrite
Signal operator+(const Signal &sig1, const Signal &sig2)
{
	Signal sum;
	double sum2 = 0;
	double temp;

	if(sig1.length == sig2.length)
	{
		sum.length = sig1.length;

		//add signal data
		for(int i : sig1.data)
		{
			temp = sig1.data[i] + sig2.data[i];
			sum.data.push_back(temp);
			cout<<"sum data[i] = "<<sum.data[i]<<endl;
		}
        //Redefine max
    	sum.max = sum.data[0];
    	for(int i = 0; i < sum.length; i++)
    	{
    		if(sum.data[i] > sum.max)
    		{
    			sum.max = sum.data[i];
    		}
    	}

    	//Redefine avg
    	for (int i = 0; i < sum.length; i++)
        {
            sum2 = sum2 + sum.data[i];
        }
        sum.avg = sum2 / (double) sum.length;
	}
	else
	{
		cout << "Invalid signal addition" << endl;
	}

	return sum;
}



//Main function
int main(int argc, char *argv[]) {
	int fnum, choice = 0, err1 = 1, err2 = 0;
	double factor;
        Exception err3;
	string fname, outname;
	Signal *sig2;
	Signal sig3(1);

	//Command Line analysis
	if(argc == 1)
		{
			sig2 = new Signal();
		}
	else if(argv[1][1] == 'n')
		{
			fnum = atoi(argv[2]);
                        while(err1 == 1)
                        {
                            try{
                                sig2 = new Signal(fnum);
                            }
                            catch(int err1){
                                cout<<"Invalid file number, enter a new one: "<<endl;
                                cin>>fnum;
                                continue;
                            }
                            err1 = 0;
                        }
		}
	else if(argv[1][1] == 'f')
		{
			fname = argv[2];
			sig2 = new Signal(fname);
		}
	else
		{
			cout<<"ERROR: NO INPUT CASE"<<endl;
			//cout<<"test"<<endl;
			//sig2 = new Signal();

		}

	while(choice != 8)
	{
            try{

		cout << "\nMake an operation choice: "
				"\n1. Offset"
				"\n2. Scale"
				"\n3. Center"
				"\n4. Normalize"
				"\n5. Print Info"
				"\n6. Save Data"
				"\n7. Nonmember Addition"
				"\n8. Quit"
				<< endl;
		cin >> choice;

		if(choice == 1)
		{
			//sig2->Offset();
			cout<<"Input an offset value: ";
			cin>>factor;
                        try{
                            (*sig2)+factor;
                        }
                        catch(int err2)
                        {
                            cout<<"Empty Signal"<<endl;
                        }
		}
		else if(choice == 2)
		{
			//sig2->Scale();
			cout<<"Input a scaling factor: ";
			cin>>factor;
                        try{
                            (*sig2)*factor;
                        }
                        catch(int err2)
                        {
                            cout<<"Empty Signal"<<endl;
                        }
		}
		else if(choice == 3)
		{
                        try{
                            sig2->Center();
                        }
                        catch(int err2)
                        {
                            cout<<"Empty Signal"<<endl;
                        }
		}
		else if(choice == 4)
		{
                        try{
                            sig2->Normalize();
                        }
                        catch(int err2)
                        {
                            cout<<"Empty Signal"<<endl;
                        }
		}
		else if(choice == 5)
		{   
                        sig2->Sig_info();                          
		}
		else if(choice == 6)
		{
			cout << "Please input desired output name without extension: ";
			cin >> outname;
			sig2->Save_file(outname);
		}
		else if(choice == 7)
		{
                    try{
			if(sig2->length != sig3.length)
                            throw err3;
                        
                        *sig2 = (*sig2) + sig3;
                    }
                    catch(Exception err3)
                    {
                        cout<<"Incompatable signal lengths"<<endl;
                        throw err3;
                    }
		}
		else if(choice != 8)
		{
			cout<<"Improper choice"<<endl;
		}
            }
            catch(...){
                    cout<<"Undefined Exception"<<endl;
            }
	}

	delete sig2;
}