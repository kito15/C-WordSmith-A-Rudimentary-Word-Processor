#include <iostream>
#include<string.h>
#include <regex>
#include<fstream>
#include <sstream>
 
using namespace std;
int Parse_string_Int(string str) {  //converts string into substring to int for argv[i]
 string substr = str.substr(4);
 stringstream convert(substr);
 int num_string;
 convert >> num_string;
 return num_string;
}
string push(string o, int num, string brechar) {
 string result = o;
 for (int i = 0; i < num; i++)
   result += brechar;
 return result;
}
int main(int argc, char * argv[]) {
 ifstream file;
 int t = 20;
 int m = 50;
 int n = 5;
 int s = 1;
 int i = 1;
 int wordcount = 0;
 int flag = 0;
 int truncflag = 0;
 while (i < argc) { //error cases handled
   if (regex_match(argv[i], regex("-WC=[0-9]+"))) {
     m = Parse_string_Int(argv[i]);
     flag = 1;
   }
   if (regex_match(argv[i], regex("WC=[0-9]+"))) {
     cerr << "UNRECOGNIZED FLAG flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("-WC=?-[0-9]+"))) {
     cerr << "VALUE NOT INTEGER greater than 0 flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("-WC[0-9]+"))) {
     cerr << "MISSING = SIGN flag”";
     exit(1);
   }
   if (regex_match(argv[i], regex("-LL=[0-9]+"))) {
     t = Parse_string_Int(argv[i]);
     flag = 1;
   }
   if (regex_match(argv[i], regex("-LL=?-[0-9]+"))) {
     cerr << "VALUE NOT INTEGER greater than 0 flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("LL=[0-9]+"))) {
     cerr << "UNRECOGNIZED FLAG flag";
     exit(1);
   }
    if (regex_match(argv[i], regex("-LL[0-9]+"))) {
     cerr << "MISSING = SIGN flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("-IN=[0-9]+"))) {
     n = Parse_string_Int(argv[i]);
     flag = 1;
   }
   if (regex_match(argv[i], regex("IN=[0-9]+"))) {
     cerr << "UNRECOGNIZED FLAG flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("-IN=?-[0-9]+"))) {
     cerr << "VALUE NOT INTEGER greater than 0 flag";
     exit(1);
   }
     if (regex_match(argv[i], regex("-IN[0-9]+"))) {
     cerr << "MISSING = SIGN flag”";
     exit(1);
   }
   if (regex_match(argv[i], regex("-SP=[0-9]+"))) {
     s = Parse_string_Int(argv[i]);
     flag = 1;
   }
   if (regex_match(argv[i], regex("SP=[0-9]+"))) {
     cerr << "UNRECOGNIZED FLAG flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("SP=-?[0-9]+"))) {
     cerr << "VALUE NOT INTEGER greater than 0 flag";
     exit(1);
   }
   if (regex_match(argv[i], regex("-SP[0-9]+"))) {
     cerr << "MISSING = SIGN flag";
     exit(1);
   }
   i++;
 }
 if (argc > 1) { //if argc is greater than one file name provided
   file.open(argv[1]); //if file exist opens file
   if (!file.is_open()) { //if no file name provide or wrong file displays error unable to open file
     cerr << "Unable to open file" << endl;
     exit(1);
   } else {
     string word;
     string * words = new string[m];
     for (int i = 0; i < m; i++) {
       words[i] = " ";
     }
     i = 0;
     while (file >> word) {
       wordcount = wordcount + 1;
       if (i < m) {
         words[i] = word;
         i++;
       } else {
         truncflag = 1;
       }
     }
     string line;
     while (getline(file, line)) {
 
       if (line.empty()) {
         while (line.empty())
           getline(file, line);
         istringstream ss(line);
         string first_word;
         if (ss >> first_word) {
           for (int l = 0; l < m; l++) {
             if (words[l].compare(first_word) == 0) {
               words[l] = push(" ", n, " ") + words[l];
             }
           }
         }
       }
     }
     string o = " ";
     o = push(o, n, " ");
     i = 0;
     while (i < m) {
       string temp = words[i] + " ";
       int j = temp.length();
       while (j + words[i + 1].length() < t) {
         temp += words[i + 1] + " ";
         j = temp.length();
         i++;
       }
       o += temp;
       o = push(o, s, "\n");
       i++;
     }
     cout << o;
     cout << "The maximum allowed number of words number is: " << m << endl;
     if (truncflag == 1) {
       cout << "The read file contains number of words exceeding the allowed maximum" << endl;
       cout << "It has been truncated accordingly." << endl;
     } else
       cout << "The read file cotains: " << wordcount<<" words";
   }
 }
}

