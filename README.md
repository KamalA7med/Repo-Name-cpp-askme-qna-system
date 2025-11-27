# 💬 cpp-askme-qna-system

A simple, console-based *Q&A social system* (similar to Ask.fm) implemented in *C++*. This project demonstrates basic object-oriented programming (OOP) principles, file I/O operations for data persistence, and fundamental data structures like std::map, std::multimap, and std::vector to manage users and questions.

## ✨ Features

* *User Management:* Sign up and Log in for users.
* *User Persistence:* Stores user data (ID, username, password, name, email, allow anonymous flag) in a file (Users2.txt).
* *Question Asking:* Users can ask questions to other users.
    * Supports *anonymous* questioning based on the recipient's settings.
    * Supports *question threads* (asking a follow-up question referencing a Parent_Question_ID).
* *Question Persistence:* Stores question data (Parent ID, Question ID, From ID, To ID, is anonymous flag, details, answer) in a file (Questions.txt).
* *Core Q&A Functionality:*
    * View *Questions To Me* (questions received).
    * View *Questions From Me* (questions asked).
    * *Answer* questions received.
    * *Delete* questions asked.
* *Feed:* View a consolidated feed of all questions and their answers.
* *System Users List:* View a list of all registered users.

## 🛠 Technology Used

* *Language:* C++
* *Libraries:* Standard C++ Library (iostream, string, vector, fstream, map, multimap).
* *Data Storage:* Local text files (Users2.txt, Questions.txt) for simple database simulation.

## 🏗 Project Structure

The project is structured with classes to encapsulate the logic for users and questions:

* User Class: Represents a system user.
* Question Class: Represents a single question/answer entry.
* Users_Manger Class: Handles loading, saving, and managing user data.
* Question_Manager Class: Handles loading, saving, answering, and deleting question data.
* Ask_Me_Ui Class: Contains the main application loop, menu, and user interface logic.

## 🚀 Getting Started

### Prerequisites

* A C++ compiler (e.g., g++).
* A C++ development environment (like Visual Studio, VS Code, or a simple text editor).

### Compilation and Execution

1.  *Clone the repository:*
    bash
    git clone [https://github.com/yourusername/cpp-askme-qna-system.git](https://github.com/yourusername/cpp-askme-qna-system.git)
    cd cpp-askme-qna-system
    
2.  *Compile the C++ code:*
    bash
    g++ AskMe.cpp -o AskMe
    
    (The compilation command may vary slightly based on your environment.)
3.  *Run the application:*
    bash
    ./AskMe
    
4.  The application will start with the *Login/Sign-up* screen.

### Initial Setup
The system requires two files to store data:
* Users2.txt
* Questions.txt

If these files do not exist in the same directory as the executable, you may need to *create empty files* with these names before running the application.

## 💡 Usage Example

1.  *Sign Up* for a new account.
2.  *Log In* with your credentials.
3.  Choose [6] List System Users to find the ID of another user.
4.  Choose [5] Ask Question and provide the target user's ID, question details, and set the anonymous flag if desired.
5.  Log in as the recipient and choose [1] Print Questions To Me.
6.  Choose [3] Answer Question to reply.
7.  View the answered question in the feed using [7] Feed.
