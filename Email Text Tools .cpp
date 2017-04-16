/*
	Name:  Email Tools (filtring - Joining - spliting ... and more ! )
	Copyright:  Venus 2016
	Author:  MOHAMED EL OMARI
	Date: 20/08/16 02:39 , reviewed 16/04/17 22:44
	Description:  this Project is personal and free not for sell 
*/
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <windows.h>
#include <sstream>
#include <set>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <algorithm>

using namespace std ;

ifstream Input ;
ofstream Output;
void setcolor(unsigned short );
vector<string> load_to_RAM(bool );
vector <string> Get_Dir_list(bool );
void Email_Splitter();
int Email_Joiner();
int Email_Filter();
void Main_filter(vector <string> &,vector<int> &);
vector<string> duplicated_remover(vector<string> &);
bool  Quick_Statistique(vector<string> & ,bool  ,int & ,int & ,int & ,int & ,int & ,int & ,int &,int &,int &);
bool Start(vector <string> &Temp_File,vector <string> &,int );
vector<string> Custom_Choices();
void Creat_OutPut(vector<string> );
vector<int> Choices();
void Closing(int );
void Logo();
void help();

string Key_Words[] = 	{
				"@gmail.",
				"@free.",
				"@aol.",
				"@orange",
				"@wanadoo.",
				"@hotmail.",
				"@outlook.",
				"@live.",
				"@yahoo.",
				"@ymail.",
				"@rocketmail.",
				"@sfr.",
				"@waika9.com",
				"@fnac.net",
				"@mageos.com",
				"@guideo.",
				"@cario.",
				"@9business.",
				"@9online.",
				"@club-internet.",
				"@cegetel.",
				"@neuf.",
				"@laposte.",
				"@voila."
				};

const vector<string> Domains(Key_Words, Key_Words+(sizeof(Key_Words)/sizeof(Key_Words[0])));
static int  HOTMAIL,
			GMAIL,
			YAHOO,
			FREE,
			AOL,
			ORANGE,
			SFR,
			POST,
			VOILA;

int main()
{
	//p_name = argv[0];
	system("cls");
	setcolor(15);
	int choice = 0 ;
	Logo();
	cout<<"		#################################################	  "<<endl
		<<"		#	For Emails Filter    :     1		#	  "<<endl
		<<"		#	For Emails Splitter  :     2		#	  "<<endl
		<<"		#	For Emails Joiner    :     3		#	  "<<endl
		<<"		#################################################	  "<<endl;
	cout<<"Choice : ";cin>>choice;
	switch(choice)
	{
		case 1 :
				Email_Filter();
				cin.ignore();
				break ;
		case 2 :
				setcolor(15);
    			Email_Splitter();
    			cin.ignore();
    			break;
		case 3 :
				setcolor(15);
    			Email_Joiner();
    			cin.ignore();
    			break;    			
    	default: main();		
	}	
}
// Coloring the programme 
void setcolor(unsigned short color){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon,color); 
}
//duplicated remover using Set
vector<string> duplicated_remover(vector<string> &Temp_File){
	const clock_t begin_time = clock(); //time
	int old_size  = Temp_File.size(); //save old size for Info
	set<string> s( Temp_File.begin(), Temp_File.end() ); //Copy Tempfile to S (set) striing
	Temp_File.assign( s.begin(), s.end() );
	setcolor(10);cout<<"[+]";setcolor(15);cout<<" Deleting Duplicated emails !"<<endl;
	setcolor(10);cout<<"[!] ";setcolor(12);cout<<old_size-Temp_File.size();setcolor(15);cout<<" Duplicated emails was Deleted in ";setcolor(9);
	cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;		
	return Temp_File;
}
//copying 
vector<string> load_to_RAM(bool Show){
	string line;
	const clock_t begin_time = clock(); //time
	vector<string> Temp_File ;
	Input.open("Input.txt");
		if(Show)
			{
				// do something
			setcolor(10);cout<<"[+] ";setcolor(15);cout<<"Loading Input.txt To RAM ..."<<endl;
			}
		if(Input.is_open())
		{
			while (getline(Input,line))   
			{	
				string helper ;
				stringstream Flux;
				Flux<<line ;
		       	while(Flux>>helper && !line.empty()) 
					{
					if(helper.find("@") != string::npos )
					{
						if(helper.substr(helper.find("@")+1).find(".") != string::npos)
						{
							transform(helper.begin(), helper.end(), helper.begin(), ::tolower); //to lower case for exact compaire hahaha
							Temp_File.push_back(helper);
						}
					}	
				}

			}
			if(Show)
			{
				setcolor(10);cout<<"[!] ";setcolor(15);cout<<"Loading and Converting To lower case for precession . Done in ";setcolor(9);
				cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;	
			}
		}
		else 
		{
			setcolor(12);cout<<"[+] ";setcolor(12);cout<<"Faild To Open Input.txt ! "<<endl;			
			Closing(5000);
		}
	Input.close();
	return Temp_File;
}
bool  Quick_Statistique(vector<string> &Temp_File,bool Show,int &all_hotmail,int &gmail,int &all_yahoo,int &free,int &aol,int &orange_wanadoo,int &all_sfr,int &voila,int & laposte)
{
	const clock_t begin_time = clock(); //time
	all_hotmail=0,
	gmail=0,
	all_yahoo=0,
	free=0,
	aol=0,
	orange_wanadoo=0,
	all_sfr=0,
	voila=0,
	laposte=0;
	for(int i =0;i<Temp_File.size();i++){
		if(Temp_File.at(i).find(Domains.at(0)) != string::npos)
		{
			gmail++;
		}
		if(Temp_File.at(i).find(Domains.at(1)) != string::npos)
			{
			free++;
		}
		if(Temp_File.at(i).find(Domains.at(2)) != string::npos)
			{
			aol++;
		}
		for(int k=0;k<=1;k++){	
		if(Temp_File.at(i).find(Domains.at(k+3)) != string::npos)
			{
			orange_wanadoo++;
			}
		}
		for(int k=0;k<=2;k++){
			if(Temp_File.at(i).find(Domains.at(k+5)) != string::npos)
			{
			all_hotmail++;
			}
		}
		for(int k=0;k<=1;k++){
			if(Temp_File.at(i).find(Domains.at(k+8)) != string::npos)
			{
			all_yahoo++;
			}
		}
		for(int k=0;k<=10;k++){
			if(Temp_File.at(i).find(Domains.at(k+11)) != string::npos)
			{
			all_sfr++;
			}
		}
			if(Temp_File.at(i).find(Domains.at(22)) != string::npos)
			{
			laposte++;
			}
			if(Temp_File.at(i).find(Domains.at(23)) != string::npos)
			{
			voila++;
			}
	}
	Input.close();
	if(Show){
	setcolor(10);cout<<"[!]";setcolor(10);cout<<" Quick statistique on Input.txt in ";
	setcolor(9);cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;	
	setcolor(11);cout<<"	Total : "<<Temp_File.size()<<" Emails !"<<endl;
	cout<<"	0 -	Save All without Duplicated	: "<<Temp_File.size()<<endl
	    <<"	1 -	Gmail  				: "<<gmail<<endl
	    <<"	2 -	Free 				: "<<free<<endl 
	    <<"	3 -	Aol 				: "<<aol<<endl	
	    <<"	4 -	Orange				: "<<orange_wanadoo<<endl	
	    <<"	5 -	Hotmail				: "<<all_hotmail<<endl
	    <<"	6 -	Yahoo	 			: "<<all_yahoo<<endl 
	    <<"	7 -	SFR				: "<<all_sfr<<endl
	    <<"	8 -	La Poste			: "<<laposte<<endl
	    <<"	9 -	Voila				: "<<voila<<endl		
	    <<"	10 -	Others 				: "<<Temp_File.size()-(free+all_yahoo+gmail+all_hotmail+aol+orange_wanadoo+all_sfr+laposte+voila)<<endl	
	    <<"	11 -	For custome choice" <<endl
	    <<"	99 -	Help ! " <<endl;
	}
	if (HOTMAIL == 0 && GMAIL == 0 && YAHOO == 0 && FREE == 0 && AOL == 0 && ORANGE == 0 && SFR == 0 && laposte == 0 &&  voila == 0)
	{
		return true; 	
	}
}
vector<string> Custom_Choices(){
	vector<string> choices_list;
	string choice_domain_str;
	string helper ;
	stringstream Flux;
		do
		{
		setcolor(12);
		cout<<"[-] Enter KeyWords Seprated By Space ( @mail ... ) : ";
		getline(cin,choice_domain_str);
		}while(choice_domain_str.empty());
				Flux<<choice_domain_str ;
	       	while(Flux>>helper && !choice_domain_str.empty()) 
				{
				choices_list.push_back(helper);
				}
		return choices_list;
}
vector<int> Choices(){
	vector<string> choices_list_str;  
	vector<int> choices_list_int;
	string choice_domain_str;
	string helper ;
	stringstream Flux;
		cin.ignore();
		do
		{
		setcolor(12);
		cout<<"[+] Choose Frome The List Above ( Seperated By SPACE For Multi Choice ) : ";
		setcolor(10);
		getline(cin,choice_domain_str);
		}while(choice_domain_str.empty());
				Flux<<choice_domain_str ;
	       	while(Flux>>helper && !choice_domain_str.empty()) 
				{
				choices_list_str.push_back(helper);
				}
			for(int i=0;i<choices_list_str.size();i++)
				{
				int Temp;
				stringstream buffer(choices_list_str.at(i));
				buffer >> Temp;
				choices_list_int.push_back(Temp);  
				}		
		return choices_list_int;
}
bool Start(vector <string> &Temp_File,vector <string> &choosed_Domain,int Mode){			
		CreateDirectory("Filter Output", NULL);
		string Output_name;
		if(Mode == 1)
		{	
		setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring Others ... !"<<endl;
			Output.open("Filter Output/Others.txt");
			do
			{
			for(int i=0;i<choosed_Domain.size();i++)
				{
					for(int j = 0 ;j<Temp_File.size() ; j++ )
					{
						 if(Temp_File.at(j).substr(Temp_File.at(j).find("@")).find(choosed_Domain.at(i)) != string::npos) 		
						{
								Temp_File.erase(Temp_File.begin()+j);
						}
					 }   			
			    }
			}while(!(Quick_Statistique(Temp_File,false,HOTMAIL,GMAIL,YAHOO,FREE,AOL,ORANGE,SFR,VOILA,POST)));
		    for(int i=0;i<Temp_File.size();i++)
			{
				Output<<Temp_File.at(i)<<endl;
		    }
		setcolor(10);cout<<"[+]";setcolor(172);cout<<" Filtring Others Done !"<<endl;
		Output.close();
		}
		else if(Mode == 3)
		{
			setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring All Without Duplicated ..."<<endl;
			Output_name = "Filter Output/All_no_duplicated.txt";
			Output.open(Output_name.c_str());
			for(int j = 0 ;j<Temp_File.size() ; j++ )
			{
				//setcolor(10);cout<<"[+]";setcolor(15);cout<<" Copying "<<Temp_File.at(j)<<" To "<<Output_name;setcolor(10);cout<<" Done."<<endl;
				Output<<Temp_File.at(j)<<endl;
				//Temp_File.erase(Temp_File.begin()+j);		
			}
			Output.close();  
		}
		else
		{
			if(Mode == 2 )
			{
			setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring ..."<<endl;
				for(int i = 0  ;i<choosed_Domain.size();i++)
				{
					cout<<"   - "<<choosed_Domain.at(i)<<endl;
				}
				if(choosed_Domain.size() == 1)
				{
				Output_name = "Filter Output/"+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1)+".txt";
				Output.open(Output_name.c_str());	
				}
				else
				Output.open("Filter Output/Custom choices.txt");
			}
			else if(Mode == 0)
			{
			Output_name = "Filter Output/"+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1)+".txt";
			Output.open(Output_name.c_str());
			}
			for(int i=0;i<choosed_Domain.size();i++)
				{
					for(int j = 0 ;j<Temp_File.size() ; j++ )
					{
						 if(Temp_File.at(j).substr(Temp_File.at(j).find("@")).find(choosed_Domain.at(i)) != string::npos) 		
						{
								//setcolor(10);cout<<"[+]";setcolor(15);cout<<" Copying "<<Temp_File.at(j)<<" To "<<Output_name;setcolor(10);cout<<" Done."<<endl;
								Output<<Temp_File.at(j)<<endl;
								Temp_File.erase(Temp_File.begin()+j);
						}
					 }   			
			    }
			Output.close();
		}
		Temp_File = load_to_RAM (false);
		Output_name.clear();
		//return (Output.is_open())?true:false;
}
void Main_filter(vector <string> &Temp_File,vector<int> &Choices_list){
//for testing				for(int i=0;i<Choices_list.size();i++)cout<<"----"<<Choices_list.at(i)<<endl;
		for(int i=0;i<Choices_list.size();i++){
		vector<string> choosed_Domain ;
			switch(Choices_list.at(i))
			{	
				case 0 : 
						 Start(Temp_File,choosed_Domain,3);
						 break;
				case 1 : choosed_Domain.push_back(Domains.at(0));
				 		 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 2 : choosed_Domain.push_back(Domains.at(1));
				 		 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
				 		 break; 
				case 3 : choosed_Domain.push_back(Domains.at(2));
				 		 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 4 : 
						 for(int k=0;k<=1;k++)
						 {	
						 choosed_Domain.push_back(Domains.at(k+3)); 
						 }
				 		 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 5 : 
					 	 for(int k=0;k<=2;k++)
						 {
						 choosed_Domain.push_back(Domains.at(k+5)); 
						 }
						 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 6 : 
		    		 	 for(int k=0;k<=1;k++)
						 {
						 choosed_Domain.push_back(Domains.at(k+8)); 
						 }
						 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 7 :
		    		 	 for(int k=0;k<=10;k++)
						 {
						 choosed_Domain.push_back(Domains.at(k+11)); 
						 }
						 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 8 :
						 choosed_Domain.push_back(Domains.at(22));
						 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;
				case 9 :		 
						 choosed_Domain.push_back(Domains.at(23));
						 Start(Temp_File,choosed_Domain,0);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring "+choosed_Domain.at(0).substr(choosed_Domain.at(0).find("@")+1,choosed_Domain.at(0).find(".")-1);setcolor(10);cout<<" Done."<<endl;
						 break;						
				case 10 : 
						 choosed_Domain = Domains; 
						 Start(Temp_File,choosed_Domain,1);
						 break;
				case 11 :
						// vector<string> Custome_Choices = Custom_Choices();
						 choosed_Domain = Custom_Choices();
						 Start(Temp_File,choosed_Domain,2);
						 setcolor(10);cout<<"[+]";setcolor(15);cout<<" Filtring Your Custome Choices Done !"<<endl;
						 break;
				case 99 :	
							help();
							system("pause");
							main();
							break;
				default : 
						  setcolor(201);cout<<"[!]";setcolor(201);cout<<" Wrong Choice ! Idiot :p "<<endl;
						  Temp_File.clear();
						  Closing(4500);
			}
		}
}
void help()
{
	cout<<"[!] Help :"<<endl
		<<"	- Make Sure to Put Input.txt in the Same directory "<<endl
		<<"	  Input.txt with a capital I not i :p "<<endl
		<<"	- This app won't Edit your Input.txt ( Works with a copy of it ) "<<endl	
		<<"	- For Multi choices Enter choices seperated by space "<<endl
		<<"		ex : 2 5 1	"<<endl
		<<"	- To avoid problem try to clear direcory from other privious Result "<<endl
		<<"		Files like Gmail.txt ... yahoo.txt ..."<<endl
		<<"	- For large Input Files it may take a bit for Loading To RAM "<<endl
		<<"	  So be patient :p "<<endl
		<<"	- first part can filter Duplicatd lines not just emails ! "<<endl
		<<"	- For Support contact me on facebook 'Med.e6'"<<endl<<endl<<endl<<endl;
}
void Closing(int temp)
{
	setcolor(15);
  cout<<"       ¦¦¦+   ¦¦¦+ ¦¦¦¦¦¦+ ¦¦+  ¦¦+ ¦¦¦¦¦+ ¦¦¦+   ¦¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦+     "<<endl
	  <<"       ¦¦¦¦+ ¦¦¦¦¦¦¦+---¦¦+¦¦¦  ¦¦¦¦¦+--¦¦+¦¦¦¦+ ¦¦¦¦¦¦¦+----+¦¦+--¦¦+    "<<endl
	  <<"       ¦¦+¦¦¦¦+¦¦¦¦¦¦   ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦+¦¦¦¦+¦¦¦¦¦¦¦¦+  ¦¦¦  ¦¦¦    "<<endl
	  <<"       ¦¦¦+¦¦++¦¦¦¦¦¦   ¦¦¦¦¦+--¦¦¦¦¦+--¦¦¦¦¦¦+¦¦++¦¦¦¦¦+--+  ¦¦¦  ¦¦¦    "<<endl
	  <<"       ¦¦¦ +-+ ¦¦¦+¦¦¦¦¦¦++¦¦¦  ¦¦¦¦¦¦  ¦¦¦¦¦¦ +-+ ¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦++    "<<endl
	  <<"       +-+     +-+ +-----+ +-+  +-++-+  +-++-+     +-++------++-----+     "<<endl
      <<"                                                                          "<<endl
	  <<"       ¦¦¦¦¦¦¦+¦¦+          ¦¦¦¦¦¦+ ¦¦¦+   ¦¦¦+ ¦¦¦¦¦+ ¦¦¦¦¦¦+ ¦¦+        "<<endl
	  <<"       ¦¦+----+¦¦¦         ¦¦+---¦¦+¦¦¦¦+ ¦¦¦¦¦¦¦+--¦¦+¦¦+--¦¦+¦¦¦        "<<endl
	  <<"       ¦¦¦¦¦+  ¦¦¦         ¦¦¦   ¦¦¦¦¦+¦¦¦¦+¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦++¦¦¦        "<<endl
	  <<"       ¦¦+--+  ¦¦¦         ¦¦¦   ¦¦¦¦¦¦+¦¦++¦¦¦¦¦+--¦¦¦¦¦+--¦¦+¦¦¦        "<<endl
	  <<"       ¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+    +¦¦¦¦¦¦++¦¦¦ +-+ ¦¦¦¦¦¦  ¦¦¦¦¦¦  ¦¦¦¦¦¦        "<<endl
	  <<"       +------++------+     +-----+ +-+     +-++-+  +-++-+  +-++-+        "<<endl;
	cout<<" Closing ..."<<endl;	
	Sleep(temp);
	exit(EXIT_FAILURE);
}
void Logo(){
	setcolor(26);
		cout<<"----------------Version--06-09-2016---BY--MOHAMED--EL-OMARI--------------------"<<endl;
		cout<<"	Make Sure to Put Input.txt in the Same directory ( Next to this .exe ) "<<endl;
		cout<<"-------------------------------------------------------------------------------"<<endl<<endl;
	setcolor(15);
}
int Email_Filter()
{
	system("cls & color 1");
	string State;
	do
	{
		Logo();
		setcolor(14);
		cout<<"		################ Email Filter #################"<<endl;
		vector <string> INPUT_Text =load_to_RAM(true);
		INPUT_Text = duplicated_remover(INPUT_Text);
		Quick_Statistique(INPUT_Text,true,HOTMAIL,GMAIL,YAHOO,FREE,AOL,ORANGE,SFR,VOILA,POST);
		vector<int> Choices_list = Choices();
		const clock_t begin_time = clock(); //time
		Main_filter(INPUT_Text,Choices_list);
		setcolor(10);cout<<"[!] ";setcolor(15);cout<<"Filtring Done in ";setcolor(9);
		cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;	
			do
		{
			setcolor(12);cout<<"[ Start again ? (Y) or (N) | To Go Back To Main Menu Press"; setcolor(10);cout<<" M ";setcolor(12);cout<<"]:";getline(cin,State);
		}while(State.empty());
	}while(State == "Yes" || State == "Y" || State == "y");
	if(State == "M" || State == "m")
	{
	main();	
	}
	else
	Closing(2000);
}
//
void Email_Splitter()
{
	system("cls & color 1");
	string State;
	do
	{
		Logo();
		setcolor(14);
		cout<<"		################ Email Splitter #################"<<endl;
		vector<string> Temp_File;
	   	double counter=0,Num_line=0;
		string line,counter_str;
		Input.open("Input.txt");
		if(Input.is_open())
		{
			setcolor(10);cout<<"[+] ";setcolor(15);cout<<"Loading Input.txt To RAM ..."<<endl;
			while (std::getline(Input, line))   
			{
				if(!line.empty())
				{
					Temp_File.push_back(line);
					++Num_line;
				}
			}
			Input.close();
			Temp_File = duplicated_remover (Temp_File);
			cin.ignore();
/*
		do
			{
				setcolor(10);cout<<"[+] ";setcolor(15);cout<<"Enter Inbox Check Email : ";setcolor(12);
				getline(cin,email);
			}while(email.empty());
*/
		do
			{
				setcolor(10);cout<<"[+] ";setcolor(15);cout<<"Email's number to Cut from "<<Temp_File.size()<<" : ";setcolor(12);
				getline(cin,counter_str);
				
				stringstream buffer(counter_str);
				buffer >> counter;
			}while(counter_str.empty() );
		if(counter > Temp_File.size())
		{
			setcolor(10);cout<<"[+] ";setcolor(12);cout<<"Error Entred value more then number of emails !"<<endl;
		}
		else
		{ 		
			int J=0 , Num_File = ceil(Num_line/counter) ;
			setcolor(10);cout<<"[?] ";setcolor(15);cout<<"The Input file has "<<Temp_File.size()<<" will generate ";setcolor(9);cout<<Num_File;setcolor(15);cout<<" Outputs Text Files !"<<endl;
			setcolor(9);cout<<"[+] Press Enter to start or Close the Console to cancel !"<<endl;getch();
			const clock_t begin_time = clock(); //time
				for(int i=1 ;i<=Num_File;i++)
				{
					const clock_t begin_time = clock(); //time
					stringstream I; 
					I<<i;
					CreateDirectory("Splitter Output", NULL);
					string Output_Name ="Splitter Output/Output-"+I.str()+".txt";

					Output.open(Output_Name.c_str());
						
						//Output<<email<<endl;
						
						for(int j=0;j<counter;j++)
						{	
							if((J+j)<Temp_File.size())
							{
								Output<<Temp_File.at(J+j)<<endl;
								J++;
							}
							else break;
						}
						
						//Output<<email;
					setcolor(10);cout<<"[+] ";setcolor(15);cout<<Output_Name.substr(Output_Name.find("/")+1,Output_Name.find("."))<<" Done ! in ";setcolor(9);cout<<float( clock () - begin_time ) /  CLOCKS_PER_SEC<<" s"<<endl;
			    	Output.close();
				}
			setcolor(10);cout<<"[+] ";setcolor(15);cout<<"Spliting Done ! in ";setcolor(9);
			cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;		
		}
		}
		else
		{
			setcolor(12);cout<<"[+] ";setcolor(12);cout<<"Faild To Open Input.txt ! "<<endl;			
			Closing(2000);
		}	
		cin.ignore();
		do
			{
			setcolor(12);cout<<"[ Start again ? (Y) or (N) | To Go Back To Main Menu Press"; setcolor(10);cout<<" M ";setcolor(12);cout<<"]:";getline(cin,State);
			}while(State.empty());
	}while(State == "Yes" || State == "Y" || State == "y");
	if(State == "M" || State == "m")
	{
	main();	
	}
	else
	 Closing(2000);
}
vector <string> Get_Dir_list(bool Show){
	vector <string>	Dir_list;
	string line ;
	system("dir >> DIR");
	Input.open("DIR");
	while (getline(Input ,line))
	{
	string helper ;
	stringstream Flux;
    		if(line.find(".txt") != std::string::npos)
			{
				Flux<<line ;
	       		   while(Flux>>helper && !line.empty())
				   {
	             		if(helper.find(".txt") != std::string::npos)
						{
						 	Dir_list.push_back(helper);
	        			}
	       			}
			}
	}	
	if(Show)
	{
	setcolor(10);cout<<"[+] ";setcolor(15);cout<<Dir_list.size()<<" Text File founded"<<endl;
	}
	Input.close();
	remove("DIR");
 	return Dir_list;
}
vector<string> File_Joiner(int &n_emails,int &Files)
{
	vector<string> Temp_text;
	vector<string> Dir_list = Get_Dir_list(true) ;
	Files = Dir_list.size();
	setcolor(10);cout<<"[!]";setcolor(12);cout<<" Press Enter To Continue ! ";
	if (cin.get() == '\n')
	{
	int emails = 0;
	setcolor(10);cout<<"[+]";setcolor(15);cout<<" Loading ..."<<endl;
	const clock_t begin_time = clock(); //time
   	for(int i=0;i<Dir_list.size();i++)
	   {
		string line;
		setcolor(10);cout<<" ";setcolor(15);cout<<" 	Loading From "<<Dir_list.at(i);
		Input.open(Dir_list.at(i).c_str());		
					int em = 1;
				while(getline(Input ,line))
				{
					if(!line.empty())
					{	
					Temp_text.push_back(line);
					emails++;
					em++;
					}
				}
					cout<<" Found "<<em<<" in "<<Dir_list.at(i)<<endl;
		Input.close();
		n_emails = emails ;
	}
	setcolor(10);cout<<"[+]";setcolor(15);cout<<" Loading Done ! in ";		setcolor(9);
	cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;	
	return Temp_text;
	}
	else 
		Closing(100);
}
void Creat_OutPut(vector<string> Temp_text){
	CreateDirectory("Joiner Output", NULL);
    Output.open("Joiner Output/Total.txt");
    setcolor(10);cout<<"[+]";setcolor(15);cout<<" Joining ..."<<endl;
    const clock_t begin_time = clock(); //time
    for(int i=0;i<Temp_text.size();i++)
	{
		Output<<Temp_text.at(i)<<endl;
	}
    setcolor(10);cout<<"[+]";setcolor(15);cout<<" Joining Done ! in "; 		setcolor(9);
    cout<<(long double)( clock () - begin_time ) /  (CLOCKS_PER_SEC)<<" s"<<endl;	
	Output.close();
}
int Email_Joiner() 
{	
	cin.ignore();
	string State;
	do
	{
		system("cls & color 1");
		Logo();
		setcolor(14);
		cout<<"		################ Email Joiner #################"<<endl;
		setcolor(15);
	    setcolor(10);cout<<"[!]";setcolor(15);cout<<" All Text files in the same directory will be joined !"<<endl;		
		int Files,n_emails = 0;
		vector<string> Temp_text;
		Temp_text = File_Joiner(n_emails,Files);		
		Temp_text = duplicated_remover(Temp_text);
		Creat_OutPut(Temp_text);
		setcolor(14);
		cout<<"     ######################################################################"<<endl;
		setcolor(15);
		cout<<"		Joining : "<<Files<<" Text file Done ! "<<endl
			<<"		Total Email Found : "<<n_emails<<" and After Removing Duplicated ";setcolor(10);cout<<Temp_text.size()<<endl;
		setcolor(14);
		cout<<"     ######################################################################"<<endl;
		do
		{
			setcolor(12);cout<<"[ Start again ? (Y) or (N) | To Go Back To Main Menu Press"; setcolor(10);cout<<" M ";setcolor(12);cout<<"]:";getline(cin,State);
		}while(State.empty());
	}while(State == "Yes" || State == "Y" || State == "y");
	if(State == "M" || State == "m")
	{
	main();	
	}
	else
	Closing(2000);
}
