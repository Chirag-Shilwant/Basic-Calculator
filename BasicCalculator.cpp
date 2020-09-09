#include <bits/stdc++.h>
using ll = long long int;
using ld = long double;
using namespace std;

string arrPostfix[10000000];
ll arrSize;


template <class T>
class Node
{
  public:

    T val;
    Node<T> *next;

};


template <class T>
class Stack
{
   private:
    Node<T> *head;
    ll size;

   public:
     Stack(){
        head = NULL;
        size = 0;
     }
     void push(T x);
     void pop();
     T top();
     bool isEmpty()
     {
         if(size == 0) return true;
         return false;
     }
};

template <class T>
void Stack<T> :: push(T x)
    {
        if(isEmpty())
        {
            Node<T> *temp = new Node<T>;
            temp->val = x;
            temp->next = NULL;
            head = temp;
        }
        else
        {
            Node<T> *temp = new Node<T>;
            temp->val = x;
            temp->next = head;
            head = temp;
        }
        size++;
    }


template <class T>
void Stack<T> :: pop()
    {
         if(isEmpty())
         {
             cout << "Empty stack\n";
         }
         else
         {
             Node<T> *t = head;
             head = head->next;
             t->next = NULL;
             free(t); 
         }
         size--;
    }



template <class T>
T Stack<T> :: top()
    {
         if(!isEmpty())
         {
             return head->val;
         }
         return T(NULL);
    }


ll checkPrecedence(char c) 
{ 
    if(c == '*' or c == '/' or c == '%') 
    return 2; 
    
    else if(c == '+' or c == '-') 
    return 1; 
    else if(c =='(')
    return 0; 
    else 
    return -1;
}     


ld evaluate()
{
    Stack<ld>S;

    for(ll index = 0; index < arrSize; index++)
    {
        if(arrPostfix[index] == "+" or arrPostfix[index] == "-" or arrPostfix[index] == "*" or arrPostfix[index] == "/" or arrPostfix[index] == "%")
        {
            if(arrPostfix[index] == "+")
            {
                ld num2 = S.top();
                S.pop();
                ld num1 = S.top();
                S.pop();
                S.push(num1 + num2);
            }

            else if(arrPostfix[index] == "-")
            {
                ld num2 = S.top();
                S.pop();
                ld num1 = S.top();
                S.pop();
                S.push(num1 - num2);
            }

            else if(arrPostfix[index] == "*")
            {
                ld num2 = S.top();
                S.pop();
                ld num1 = S.top();
                S.pop();
                S.push(num1 * num2);
            }

            else if(arrPostfix[index] == "/")
            {
                ld num2 = S.top();
                S.pop();
                if(num2 == 0) return INT32_MIN;
                ld num1 = S.top();
                S.pop();
                S.push(num1 / num2);
            }
            
            else if(arrPostfix[index] == "%")
            {
                ll num2 = (ll)S.top();
                S.pop();
                ll num1 = (ll)S.top();
                S.pop();
                S.push((ld)(num1 % num2));
            }
        }
        else
        {
            S.push(stold(arrPostfix[index]));
        }
    }
    ld ans = S.top();
    S.pop();
    return ans;
}

// checks if c is digit (floats also allowed)
bool isDigit(char c)
{
    if((c >='0' and c <= '9') or (c == '.')) return true;
    return false;
}

// decides if '-' is operand or operator
bool isOperator(char c)
{
    if(c == ' ' or c == '(' or c == '+' or c == '-' or c == '*' or c == '/' or c == '%')  
        return true;

    return false;    
}

// converts infix expression to Postfix
void toPostfix(string infixString)
{
    Stack<char> S;
    
    string ans; 

    char prev = ' ';
    ll index = 0;

   for(char c : infixString)
   {
       if(c == '(')
             S.push(c); 

       else if((isOperator(prev) and c == '-') or isDigit(c) ) // isOperator(prev) handles negative int
            ans += c;
       
       else if(c == ')')
       {
           
           if(ans.size()) 
                arrPostfix[index++] = ans;

           ans = "";
           while(!S.isEmpty() and S.top() != '(')
           {
               string temp1(1, S.top()); 
               arrPostfix[index++] = temp1;
               S.pop();
           }

           S.pop();   // '(' will be poped       
       } 
       
       else
       {
           if(ans.size()) 
             arrPostfix[index++] = ans;
           ans = "";

           if(S.isEmpty())
             S.push(c);

            else
            {
               while(checkPrecedence(S.top()) >= checkPrecedence(c))
               {
                   string temp(1, S.top());    
                   arrPostfix[index++] = temp;
                   S.pop();
               }
               S.push(c);
            }  
       }

       prev = c;
   }

   if(ans.size()) arrPostfix[index++] = ans;

   while(!S.isEmpty())
   {
       string temp(1, S.top()); 
       arrPostfix[index++] = temp;
       S.pop();
   }

    arrSize = index;
    
   ld finalAns = evaluate();

   if(finalAns == INT16_MIN)
    cout << "Can't use negative values with % operator\n";

   else if(finalAns == INT32_MIN) 
    cout << "Divide by 0 error\n";
   
   else
    cout << "Answer is : " << fixed << setprecision(5) << finalAns << endl;

}

// Driver Code
int main()
{
    string infixString;
    cout << "Enter an infix expression\n";
    cin >> infixString;

    toPostfix(infixString);    
    return 0;
}
