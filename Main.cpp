#include<iostream>
#include<sstream>
#include<vector>
#include<string.h>
#include<stack>
#include<math.h>
using namespace std;
bool check_Number_Or_Digit(const string &sub_Expression);
int operator_Sub_Expression(const string &sub_Expression);
bool check_Operator(const string &Sub_Expression);
float process_Operator(const float a,const float b,const string &Operator);
int main()
{
    string in_Expression("3 ^ 4 + ( 3 ^ 2 / 11 *  3 - 2  )");
    //cout<<"Input the Expression : ";
    //getline(cin,in_Expression);
    istringstream iss(in_Expression);
    vector <string> sub_Expression;
    while (iss)
    {
        string sub_String;
        iss>>sub_String;
        if(sub_String!="")
        sub_Expression.push_back(sub_String);
    }
    vector <string> Out_Expression;
    stack <string> Operator;
    for(int i=0 ; i< sub_Expression.size() ; ++i )
    {
        if(check_Number_Or_Digit(sub_Expression[i]))
            Out_Expression.push_back(sub_Expression[i]);
        if(sub_Expression[i] == "(")
            Operator.push(sub_Expression[i]);
        if(sub_Expression[i] == ")")
            {
                while(Operator.top() != "("&& !Operator.empty())
                {
                    Out_Expression.push_back(Operator.top());
                    Operator.pop();
                }
                Operator.pop();
            }
        if(check_Operator(sub_Expression[i]))
            {
                while ( !Operator.empty() && operator_Sub_Expression(Operator.top()) >= operator_Sub_Expression(sub_Expression[i]))
                {
                    Out_Expression.push_back(Operator.top());
                    Operator.pop();
                }
                Operator.push(sub_Expression[i]);
            }
    }
    while (!Operator.empty())
    {
        Out_Expression.push_back(Operator.top());
        Operator.pop();
    }
    float num1,num2;
    stack <float> Result;
    for (int i = 0; i < Out_Expression.size(); i++)
    {
        cout<<Out_Expression[i]<<" ";
        if(check_Number_Or_Digit(Out_Expression[i]))
                Result.push(stof(Out_Expression[i]));
        if(check_Operator(Out_Expression[i]))
        {
            num2=Result.top();Result.pop();
            num1=Result.top();Result.pop();
            Result.push(process_Operator(num1,num2,Out_Expression[i]));
        }
        
    }
    cout<<endl<<"Result of Expression is : "<<Result.top();
    cout<<endl;

}
float process_Operator(const float a,const float b,const string &Operator)
{
    if(Operator=="+")
            return a+b;
    else if(Operator=="-")
            return a-b;
    else if(Operator=="*")
            return a*b;
    else if(Operator=="/")
            return a/b;
    else if(Operator=="^")
            return pow(a,b);
    return 0;
}
bool check_Number_Or_Digit(const string &sub_Expression)
{
    for(int index = 0 ; index < sub_Expression.size() ; ++index )
        if(isdigit(sub_Expression[index]))
            return true;
    return false;
}
int operator_Sub_Expression(const string &sub_Expression)
{
    if(sub_Expression=="("||sub_Expression==")")
        return 0;
    else if(sub_Expression=="+"||sub_Expression=="-")
        return 1;
    else if(sub_Expression=="*"||sub_Expression=="/")
        return 2;
    else return 3;
}
bool check_Operator(const string &Sub_Expression)
{
    return (isdigit(Sub_Expression[0])==false && Sub_Expression!="(" && Sub_Expression!=")");
}