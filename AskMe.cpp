// AskMe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
using namespace std;
vector<string> Split(string& S1, string Delim="#//#")
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    
        vString.push_back(S1); // it adds last word of the string.
   

    return vString;

}
vector<string> Read_Data_From_File(const string& FileName)
{
    fstream MyFile;
    vector<string> V_string;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            V_string.push_back(Line);
        }
        MyFile.close();
    }
    return V_string;
}
void Write_Line_In_File(const string FileName,const string Line,bool append=true )
{
    fstream MyFile;
    if (append)
        MyFile.open(FileName, ios::out | ios::app);
    else
        MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        
        MyFile.close();
    }
   
}
void Update_Data_In_File(const string& FileName, const vector<string>& v_String)
{
    fstream MyFile;
    
        MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for(int i=0;i<v_String.size();i++)
        MyFile << v_String[i] << '\n';

        MyFile.close();
    }
}

void Print_Menu_Options()
{
    cout << "-----------------------------------------\n";
    cout << "Menu :\n\n";
    cout << "\t\t[1] Print Questions To Me \n";
    cout << "\t\t[2] Print Questions From Me \n";
    cout << "\t\t[3] Answer Question  \n";
    cout << "\t\t[4] Delete Question  \n";
    cout << "\t\t[5] Ask Question  \n";
    cout << "\t\t[6] List System Users  \n";
    cout << "\t\t[7] Feed  \n";
    cout << "\t\t[8] Log Out  \n";
    cout << "-----------------------------------------\n";
    cout << "\t\tEnter Your Choice :  ";
}
class Question
{
private:
    int Question_ID;
    int Parent_Question_ID;//-1 if it is a parent other if It is a Thread
    int From_ID;
    int To_ID;
    int IS_AQ; // 0 or 1
    string Question_Detailes;
    string Answer;
    bool Mark_For_Delete = false;
public :
    Question() :Question_ID(0), Parent_Question_ID(-1), From_ID(0), To_ID(0), IS_AQ(0)
        , Question_Detailes(""), Answer("")
    {

    }

    Question(string& Line)
    {
        vector<string>V_string = Split(Line);
        Parent_Question_ID = stoi(V_string[0]);
        Question_ID = stoi(V_string[1]);
        From_ID = stoi(V_string[2]);
        To_ID = stoi(V_string[3]);
        IS_AQ = stoi(V_string[4]);
        Question_Detailes = V_string[5];
        Answer = V_string[6];
    }
    bool Get_Mark_For_Delete()const
    {
        return Mark_For_Delete;
    }
    void Set_Mark_For_Delete(bool Mark)
    {
         Mark_For_Delete=Mark;
    }

     string ToString()const
    {
        return (to_string(Parent_Question_ID) + "#//#" +
            to_string(Question_ID) + "#//#" +
            to_string(From_ID) + "#//#" + 
            to_string(To_ID) + "#//#" +
            to_string(IS_AQ) + "#//#" +
            Question_Detailes + "#//#" +
            Answer);
    }
    // Setter And Getters
    void Set_Question_ID(int ID)
    {
        Question_ID = ID;
    }
    void Set_Parent_Question_ID(int& ID)
    {
        Parent_Question_ID = ID;
    }
    void Set_From_ID(int ID)
    {
        From_ID = ID;
    }
    void Set_To_ID(int& ID)
    {
        To_ID = ID;
    }
    void Set_Is_AQ(int& answer)
    {
        IS_AQ = answer;
    }
    void Set_Question_Detailes( const string &Question)
    {
        Question_Detailes = Question;
    }
    void Set_Answer(const string& Answer)
    {
        this->Answer= Answer;
    }
    int Get_Question_ID ()const
    {
      return  Question_ID ;
    }
   int Get_Parent_Question_ID()const
    {
        return Parent_Question_ID ;
    }
    int Get_From_ID()const
    {
      return  From_ID;
    }
    int Get_To_ID()const
    {
       return To_ID ;
    }
    int Get_Is_AQ()const
    {
       return IS_AQ ;
    }
    const string& Get_Question_Detailes()const
    {
       return  Question_Detailes ;
    }
   const string&  Get_Answer()
    {
       return  this->Answer ;
    }
   // print Questions Methods

   void Print_Question_From_Me()const
   {
       cout << "Question ID (" << Question_ID << ") ";
       if (!IS_AQ)
           cout << "!AQ ";
       cout << "To User ID (" << To_ID << ")             ";
       cout << " Question :  " << Question_Detailes;
       if (Answer == "")
           cout << "       Not Answered Yet\n";
       else
           cout << "      Answer: " << Answer<<'\n';

   }
   void Print_Question_To_Me()const
   {
       string Prefix = "";
       if (Parent_Question_ID != -1)
           Prefix = "Thread : ";
       cout <<Prefix <<"Question ID (" << Question_ID << ") ";
       if (!IS_AQ)      
       cout << "From User ID (" << From_ID << ")             ";
       cout << " Question :  " << Question_Detailes<<'\n';
       if (Answer != "")
           cout << "      Answer: " << Answer<<'\n';
              
   }
   void Print_Feed_Question()const
   {
       string Prefix = "";
       if (Parent_Question_ID != -1)
           Prefix = "Thread : ";
       cout << Prefix << "Question ID (" << Question_ID << ") ";
       
       if (!IS_AQ)
           cout << "From User ID (" << From_ID << ") ";
       cout << "To User ID (" << To_ID << ")             ";

       cout << " Question :  " << Question_Detailes<<'\n';
       if (Answer != "")
           cout << "      Answer: " << Answer << '\n';
   }
  
 
};
class User
{
private:
    string UserName;
    string Password;
    string Name;
    string Email;
    int Allow_Anon;// 0 or 1;
    int ID;
public:
    User():UserName(""), Password(""),Name(""),Email(""),Allow_Anon(0),ID(0)
    {
        

    }
    User(string& Line)
    {
        vector<string>V = Split(Line);
        ID = stoi(V[0]);
        UserName = V[1];
        Password = V[2];
        Name = V[3];
        Email = V[4];
        Allow_Anon = stoi(V[5]);
    }
     string To_String()const
    {
        return (to_string(ID)+ "#//#" +UserName + "#//#" + Password + "#//#"
            + Name + "#//#" + 
            Email + "#//#" + to_string(Allow_Anon));
    }
    void Set_UserName(const string& Str)
    {
        this->UserName = Str;
    }
    void Set_Pass(const string& Str)
    {
        this->Password = Str;
    }
    void Set_Name(const string& Str)
    {
        this->Name = Str;
    }
    void Set_Email(const string& Str)
    {
        this->Email = Str;
    }
    void Set_ID(const int& Num)
    {
        this->ID = Num;
    }
    void Set_Allow_Anon(const int& Num)
    {
        this->Allow_Anon = Num;
    }
    const string& Get_UserName()const
    {
        return this->UserName;
    }
    const string& Get_Email()const
    {
        return this->Email;
    }
    const string& Get_Password()const
    {
        return this->Password;
    }
    const string& Get_Name()const
    {
        return this->Name;
    }
     int Get_ID()const
    {
        return this->ID;
    }
     int Get_Allow_Anon()const
    {
        return this->Allow_Anon;
    }
     void Print_User_In_Brief()const
     {
         cout << "ID : " << ID << "            Name : " << Name << '\n';
     }
     void Print_User_In_Detail()const
     {
         cout << "\n-----------------------------------------------\n\n";
         cout << "ID         : " << ID<<'\n';
         cout << "Name       : " << Name << '\n';
         cout << "User Name  : " << UserName << '\n';
         cout << "Email      : " << Email << '\n';
         cout << "Allow Anon : " << ((Allow_Anon) ? "Yes" :"No" )<< '\n';
         cout << "\n-----------------------------------------------\n";
     }



};


class Users_Manger
{
    static int User_ID;
    
    static  void Update_Users_In_File(map<int, User>& Mp_Users)
    {
        vector<string>V_string;
        for (const auto& New_User : Mp_Users)
        {

            V_string.push_back(New_User.second.To_String());
        }
        Update_Data_In_File("Users2.txt", V_string);
    }
    static int Generate_New_ID(map<int, User>& Mp_Users)
    {
        int i = 1;
        while (Mp_Users.count(i))
        {
            i++;
        }
        return i;
    }

  
   
public:
   // static map<int, User>&Mp_Users;
    static map<int, User> Load_Users_From_File()
    {
        vector<string>V_string = Read_Data_From_File("Users2.txt");
        map<int, User> Mp_Users;
        for (string& Line : V_string)
        {
            User NewUser(Line);
            Mp_Users[NewUser.Get_ID()] = NewUser;
        }
        return Mp_Users;
    }
    static void Save_New_User(map<int, User>& Mp_Users,User& NewUser)
    {
        NewUser.Set_ID(Generate_New_ID(Mp_Users));
        Mp_Users[NewUser.Get_ID()] = NewUser;
        Write_Line_In_File("Users2.txt", NewUser.To_String());
    }
    static void Print_All_Users_In_Breif(map<int, User>& Mp_Users)
    {
        for (const auto& New_User : Mp_Users)
        {
            New_User.second.Print_User_In_Brief();
        }
    }
     static void Print_All_Users_In_Detail(map<int, User>& Mp_Users)
    {
        for (const auto& New_User : Mp_Users)
        {
            
            New_User.second.Print_User_In_Detail();
        }
    }
  
  


};
int Users_Manger::User_ID = 1;
//map<int, User>Users_Manger::Mp_Users = Users_Manger::Load_Users_From_File();//this Lines Cause Some Problems

class Question_Manager
{

    //static multimap<int, Question>&Thread_Questions;
    //static  map<int, Question>&Mp_Questions;
private:
    static int Question_ID;
    
     
    static int Generate_Question_ID(map<int, Question>& Mp_Questions)
    {
        int i = 300;
        while (Mp_Questions.count(i))
        {
            i++;
        }
        return i;
    }
    
    static void Save_New_Question_In_File(map<int, Question>& Mp_Questions, multimap<int, Question>& Thread_Questions,Question& NewQuestion)
    {
        
        Mp_Questions[NewQuestion.Get_Question_ID()] = NewQuestion;
        if (NewQuestion.Get_Parent_Question_ID() != -1)
            Thread_Questions.insert({ NewQuestion.Get_Parent_Question_ID(),NewQuestion });
        Write_Line_In_File("Questions.txt", NewQuestion.ToString());
    }
    
    static void Update_All_Questions_In_File(map<int, Question>& Mp_Questions)
    {
        vector<string>V_string;
        for (const auto& New_Question :Mp_Questions)
        {
            
            V_string.push_back(New_Question.second.ToString());
        }
        Update_Data_In_File("Questions.txt", V_string);

    }
    
public:
    static multimap<int, Question> Load_Thread_Questions_From_File_In_Multimap()
    {
        multimap<int, Question>Mp_Questions;
        vector<string>V_string = Read_Data_From_File("Questions.txt");
        for (string& Line : V_string)
        {
            Question NewQuestion(Line);
            if (NewQuestion.Get_Parent_Question_ID() != -1)
                Mp_Questions.insert({ NewQuestion.Get_Parent_Question_ID() , NewQuestion });
        }
        return Mp_Questions;
    }
     static void Update_Question(map<int, Question>& Mp_Questions, multimap<int, Question>& Thread_Questions,Question& Q)
    {
         Mp_Questions[Q.Get_Question_ID()] = Q;
         Update_All_Questions_In_File(Mp_Questions);
         Thread_Questions = Load_Thread_Questions_From_File_In_Multimap();
}
     static map<int, Question> Load_All_Question()
     {
         map<int, Question>Mp_Questions;
         vector<string>V_string = Read_Data_From_File("Questions.txt");
         for (string& Line : V_string)
         {
             Question NewQuestion(Line);

             Mp_Questions.insert({ NewQuestion.Get_Question_ID() , NewQuestion });
         }
         return Mp_Questions;
     }
    static void Answer_Question(map<int, Question>& Mp_Questions, multimap<int, Question>& Thread_Questions, Question& Q)
    {
        Update_Question(Mp_Questions, Thread_Questions, Q);
    }
   static void Delete_Question(map<int, Question>& Mp_Questions, multimap<int, Question>& Thread_Questions, Question& Q)
    {
       Mp_Questions.erase(Q.Get_Question_ID());
       vector<int>V_keys;
       for ( const auto& Re_Question : Mp_Questions)
       {
           if (Re_Question.second.Get_Parent_Question_ID() == Q.Get_Question_ID())
               V_keys.push_back(Re_Question.first);
       }
       for (short i = 0; i < V_keys.size(); i++)
       {
           Mp_Questions.erase(V_keys[i]);
       }
       Thread_Questions.erase(Q.Get_Question_ID());
       Update_All_Questions_In_File(Mp_Questions);
       
    }
   static void Add_New_Question(map<int, Question>& Mp_Questions, multimap<int, Question>& Thread_Questions, Question& Q)
   {
       Q.Set_Question_ID(Generate_Question_ID(Mp_Questions));
       Save_New_Question_In_File(Mp_Questions, Thread_Questions, Q);

   }




};

int Question_Manager::Question_ID = 300;
//map<int, Question> Question_Manager::Mp_Questions = Question_Manager::Load_All_Question();
//multimap<int, Question>Question_Manager::Thread_Questions = Question_Manager::Load_Thread_Questions_From_File_In_Multimap();
class Ask_Me_Ui
{
    map<int, Question>Mp_Questions;
    multimap<int, Question>Thread_Questions;
    map<int, User>Mp_Users;
    User CurrentUser;
     
    void Answer_Question()
    {
        int ID = 0;
        cout << "Enter Question ID :";
        cin >> ID;
        if (Mp_Questions.count(ID))
        {
            Question Q = Mp_Questions[ID];
            if (Q.Get_To_ID() == CurrentUser.Get_ID())
            {
                Q.Print_Question_To_Me();
                if (Q.Get_Answer() == "")
                    cout << "Enter The Answer :";
                else
                cout << "Warning : Already AnsWered The Answer Will Be Updated : ";

                string Answer;
                cin >> Answer;
                Q.Set_Answer(Answer);
                Question_Manager::Answer_Question(Mp_Questions, Thread_Questions, Q);
                cout << "Done SuccessfUlly";
                


            }
            else
            {
                cout << "You Can Not Answer Others Questions \nTRy Again \n";
                Answer_Question();
            }


        }
        else
        {
            cout << "\n You Gived Me Wrong ID\n Try Again \n";
            Answer_Question();
        }
    }
    void Show_Sign_up_Screen()
    {
        string str;
        User NewUser;
        cout << "Enter User name : ";
        cin >> str;
        NewUser.Set_UserName(str);
        cout << "Enter Password : ";
        cin >> str;
        NewUser.Set_Pass(str);
        cout << "Enter Name : ";
        cin >> str;
        NewUser.Set_Name(str);
        cout << "Enter Email : ";
        cin >> str;
        NewUser.Set_Email(str);
        cout << "Allow anonymous (0/1)  : ";
        int n;
        cin >> n;
        NewUser.Set_Allow_Anon(n);
        Users_Manger::Save_New_User(Mp_Users, NewUser);
        cout << "Saved Succesfully\n Click Enter to Back To Login Screen :";
        system("pause");
    }
    void Back_To_Menu_Options()
    {
        cout << "\n Click Enter to Back To Login Screen :";
        system("pause");
        Show_menu_screen();
    }
    void Print_Questions_From_ME()
    {
        for (const auto& Q : Mp_Questions)
        {
            if ((Q.second.Get_From_ID() == CurrentUser.Get_ID()) )
            {
                Q.second.Print_Question_From_Me();
                

            }
        }

    }
    void Print_Questions_To_ME()
    {
        for (const auto& Q : Mp_Questions)
        {
            if ((Q.second.Get_To_ID() == CurrentUser.Get_ID()) && Q.second.Get_Parent_Question_ID() == -1)
            {
                Q.second.Print_Question_To_Me();
                if (Thread_Questions.count(Q.first))
                {
                    auto Range = Thread_Questions.equal_range(Q.first);
                    for (auto it = Range.first; it != Range.second; ++it)
                    {
                        it->second.Print_Question_To_Me();
                    }
                }

            }
        }

    }
    void Delete_Question()
    {
        int ID = 0;
        cout << "Enter Question ID :";
        cin >> ID;
        if (Mp_Questions.count(ID))
        {
            Question Q = Mp_Questions[ID];
            if (Q.Get_From_ID() == CurrentUser.Get_ID())
            {
                Q.Print_Question_From_Me();
                cout << "Do You Want To Delete This Question (Y/N) : ";
                char Answer;
                cin >> Answer;
                if (toupper(Answer) == 'Y')
                {
                    Question_Manager::Delete_Question(Mp_Questions, Thread_Questions, Q);
                }
                else
                {
                    cout << "\n\nThe Operation Was Cancled";
                }


            }
            else
            {
                cout << "You Can Not Delete Others Questions \nTRy Again \n";
                Delete_Question();
            }


        }
        else
        {
            cout << "\n You Gived Me Wrong ID\n Try Again \n";
            Delete_Question();
        }
    }
    void Print_Feed_Questions()
    {
        for (const auto& Q : Mp_Questions)
        {
            if ( Q.second.Get_Parent_Question_ID() == -1)
            {
                Q.second.Print_Feed_Question();
                if (Thread_Questions.count(Q.first))
                {
                    auto Range = Thread_Questions.equal_range(Q.first);
                    for (auto it = Range.first; it != Range.second; ++it)
                    {
                        it->second.Print_Feed_Question();
                    }
                }

            }
        }

    }
    void Ask_Question()
    {
        int ID;
        cout << "Enter User ID :";
        cin >> ID;
        
        if (Mp_Users.count(ID))
        {
            Question New_Question;
            New_Question.Set_From_ID(CurrentUser.Get_ID());
            New_Question.Set_To_ID(ID);
            User Req_user = Mp_Users[ID];
            if (Req_user.Get_Allow_Anon())
            {
                
                int Answer;
                cout << "Do You Wnant The Question To Be Anon  (1/0) :";
                cin >>Answer ;
                New_Question.Set_Is_AQ(Answer);
            }
            else
            {
                int Z = 0;
                cout << "Note Anonymous Question Are Not Allowed \n\n";
                New_Question.Set_Is_AQ(Z);
            }
            int Answer;
            string Q;
            cout << "For Thread Questions : Enter  Question ID or -1 For New Question : ";
            cin >> Answer;
            if (Answer == -1)
            {
                New_Question.Set_Parent_Question_ID(Answer);
            }
            else
            {

                while (!Mp_Questions.count(Answer))
                {
                    cout << "\nwrong Question ID \n Try Again \n";
                    cin >> Answer;

                }
                New_Question.Set_Parent_Question_ID(Answer);

            }
            cout << "Enter Question : ";
            cin >> Q;
            New_Question.Set_Question_Detailes(Q);
            Question_Manager::Add_New_Question(Mp_Questions, Thread_Questions, New_Question);
            cout << " \n\nDone Succesfully";
        }
        else
        {
            cout << "\nYou Gived Us Wrong User ID \n Try again ";
            Ask_Question();
        }

    }

    void Show_menu_screen()
    {
        Print_Menu_Options();
        int choice;
        cin >> choice;
        system("cls");
        
        switch (choice)
        {
        case 1:
        {
            Print_Questions_To_ME();
            Back_To_Menu_Options();
            break;
        }
        case 2:
        {
            Print_Questions_From_ME();
            Back_To_Menu_Options();
            break;
        }
        case 3:
        {
            Answer_Question();
            Back_To_Menu_Options();
            break;
        }
        case 4:
        {
            Delete_Question();
            Back_To_Menu_Options();
            break;
        }
        case 5:
        {
            Ask_Question();
            Back_To_Menu_Options();
            break;
        }
        case 6:
        {
            Users_Manger::Print_All_Users_In_Breif(Mp_Users);
            Back_To_Menu_Options();
            break;
        }
        case 7:
        {
            Print_Feed_Questions();
            Back_To_Menu_Options();
            break;
        }


        }
        

    }

   void  Show_LoginScreen()
   {
       system("cls");
       string Password ;
       int id;

      
       cout << "ID :";
       cin >> id;
           cout<<"Password :";
           cin >> Password;
           if (Mp_Users[id].Get_Password() == Password)
           {
               CurrentUser = Mp_Users[id];
               system("cls");
               Show_menu_screen();}
           else
           {
               system("cls");
               Show_LoginScreen();
           }



  }

    void Show_Start_Screen()
    {
        cout << "Menu :\n\n";
        cout << "\t\t[1] Login \n";
        cout << "\t\t[2] Sign Up \n";
        cout << "____________________________________________________\n";
        cout << "Enter Your Choice : ";
        int Choice;
        cin >> Choice;
        switch (Choice)
        {
        case 1:
        {
            system("cls");
            Show_LoginScreen();
            break;
        }
        case 2:
        {
            system("cls");
            Show_Sign_up_Screen();
        }
        }

    }
    
public:
    Ask_Me_Ui()
    {
        Mp_Questions=Question_Manager::Load_All_Question();
        Mp_Users = Users_Manger::Load_Users_From_File();
        Thread_Questions=Question_Manager::Load_Thread_Questions_From_File_In_Multimap();
        
    }

    void Run()
    {
        while (true)
        {
            
            Show_Start_Screen();
            system("cls");
               
        }



}


};

int main()
{

    Ask_Me_Ui Ask;
    Ask.Run();
       
}
