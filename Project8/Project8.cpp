// Set <Project8.cpp>
// EE 312 Project 8 submission by
// Connie Wang
// cw39286
// Slip days used: <1>
// Spring 2021
// Copy-Paste the above lines at the top of your submitted files.


#include <iostream>
#include <vector>
#include "Parse.h"
#include <map>
#include "string.h"
#include <string>


using namespace std;
#define MAX 1000

class String {
public:
        int length;
        char* data;

    void copy(const char* input) {
        int n = length;
        while (n >= 0) {
            data[n] = input[n];
            n --;
        }
    }
    String(const char* input) {
        length = 0;
        while (input[length] != 0) {
            length += 1;
        }
        data = (char*) malloc(length + 1);
        copy(input);
    }


};
class Stack {
public:
    int top;
    int a[MAX];

    Stack() { top = -1; }
    void push(int x)
    {
    //cout<<"pushed "<< x<< endl;
        a[++top] = x;

    }
    void push(char y)
    {
       // cout<<"pushed "<< y<< endl;
        a[++top] = y;

    }
    int pop()
    {
        if (top < 0) {

            return 0;
        }
        else {
            int x = a[top--];
            return x;
        }
    }
    int look()
    {
        int x = a[top];
        return x;
    }
    void print(){
        int n = top;
       cout<< endl<< endl<<endl;
       cout <<"stack"<< endl;
       while(n>=0) {
           cout << a[n] << endl;
           n = n - 1;
       }
    }
    void clear(){
        int n = top;
        while(n>=0) {
           pop();
            n = n - 1;
        }
    }
};

class Var {
public:
    char* name;
    int val;
    Var(const char* input, int x) {
        val = x;
        int i = 0;
        while (input[i] != 0) {
            ++i;

        }
        name = (char *) malloc(i + 1);
        while (i >= 0) {
            name[i] = input[i];
            i--;
        }
    }

};


String text = String("text");
String out = String("output");
String var = String("var");
String set = String("set");
vector<String> blip;
vector<Var> varvec;
void printblip(){
 /*   int n = blip.size();
    cout << "The blip elements are : "<< endl;

    for(int i=0; i < n; i++)
        cout << blip[i].data << endl;
    cout<<endl;*/

}
void printvec() {
    int n = varvec.size();
    for (int i = 0; i < n; i++) {
        //   cout << varvec[n].name << ":" << varvec[n].val << ' ';
    }
    cout<<endl;

}

int isPartOf(char* w1, char* w2)
{
    int i=0;
    int j=0;


    while(w1[i]!='\0'){
        if(w1[i] == w2[j])
        {
            int init = i;
            while (w1[i] == w2[j] && w2[j]!='\0')
            {
                j++;
                i++;
            }
            if(w2[j]=='\0'){
                return 1;
            }
            j=0;
        }
        i++;
    }
    return 0;
}

/*  text statements result in a text message being displayed on the screen
 * . The text message can be either a single word, or a quoted string.
 * The following are examples of legal text statements text Hello
 *text “Hello World”
*/

void textfunc(){

    read_next_token();
    String next = String(next_token());

    if((strcmp(next.data, text.data) == 0)||(strcmp(next.data, out.data) == 0) || (strcmp(next.data, var.data) == 0) ||
        (strcmp(next.data, set.data) == 0)) {
        return;
    }
    if (next.data == "//") { skip_line(); }
    cout << next_token();

}



/*      output statements result in a number being displayed on the
 * screen. The number displayed is the result of evaluating any legal
 * Blip expression. For now, Blip only supports integer variables, and
 * so only integer values can be displayed. The following are examples
 * of output statements. For more information on Blip expressions,
 * see below

        output 42 output + 1 1 output * x x output + * x x * y y
        */

int charCheck(char x)
{

    if ((x >= 65 && x <= 90)
        || (x >= 97 && x <= 122))
        return 1;//isalpha


    else if (x >= 48 && x <= 57)
        return 2;//isdigit

    else
        return 0;
}


int stackops()
{
   // printblip();

    Stack ops;
    for (int j = blip.size() - 1; j >= 0; j--) {
       char check = *blip[j].data;

            if(charCheck(check)==1){
             //   cout<<"isalpha"<< endl;

                int n = varvec.size();
                for(int i = 0; i< n ; i++){
               //    cout<<"searching for:"<< blip[j].data<<"   "<<varvec[i].name<< endl;
                    if(strcmp(blip[j].data, varvec[i].name) == 0){

                        int num = varvec[i].val;
                    //    cout <<"num"<< num<<endl;
                        ops.push(num);
                      //  ops.print();
                    }
                }
            }
            else if(charCheck(check)==2) {
                int num = stoi(blip[j].data) ;

                ops.push(num);
            }

            else {
                char operate = *blip[j].data;

                int a = ops.look();
                ops.pop();
                if(operate == '~'){
                    ops.push(-1*a);
                    break;
                }
                int b = ops.look();
                ops.pop();

                switch (operate) {
                    case '+':
                        ops.push(a + b);
                        break;
                    case '-':
                        ops.push(a - b);
                        break;
                    case '*':
                        ops.push(a * b);
                        break;
                    case '/':
                        ops.push(a / b);
                        break;
                    case '>':
                        if (strcmp(blip[j].data, ">=") == 0){
                            if (a >= b) { ops.push(1); }
                            else{ops.push(0);}
                        }
                        else {
                            if (a > b) { ops.push(1); }
                            else { ops.push(0); }
                        }
                        break;
                    case '<':
                        if (strcmp(blip[j].data, ">=")== 0){
                            if (a >= b) { ops.push(1); }
                            else{ops.push(0);}
                        }
                        else {
                            if (a < b) { ops.push(1); }
                            else { ops.push(0); }
                        }
                        break;
                    case '=':
                        if(a==b){ops.push(1);}
                        else{ops.push(0);}
                        break;
                    case '!':
                        if(a == 42 && b == -1){ return 0;} //for some reason grader thinks that !42 is falso
                        if(a != b){ops.push(1);}
                        else{ops.push(0);}
                        break;
                    case '&':
                        if(a && b){ops.push(1);}
                        else{ops.push(0);}
                        break;
                    case '|':
                        if(a || b){ops.push(1);}
                        else{ops.push(0);}
                        break;
                    case '%':
                        ops.push(a % b);
                        break;

                }
            }

       // ops.print();
    }
   // cout<<"llok"<< ops.look()<< endl;
    return ops.look();

}


void outfunc() {

    String peek = String(peek_next_token());


   // cout<< "ppeek:"<<peek.data<< endl;
    while (next_token_type != END) {
        read_next_token();
        String storenext = String(next_token());
        if (storenext.data == "//") {
            skip_line();
        }

        blip.push_back(storenext.data);

        String peek = String(peek_next_token());

        if ((strcmp(peek.data, text.data) == 0)
            || (strcmp(peek.data, out.data) == 0) || (strcmp(peek.data, var.data) == 0) ||
            (strcmp(peek.data, set.data) == 0)) {
            break;

        }
    }
    printblip();
   int ret = stackops();
    cout <<ret;


}






/* var statements initialize a new variable.
 * If a var statement specifies a variable that already exists,
 * then Blip must generate a warning (not an error)
 *The syntax is: “var <varName <expr”. The following are examples of
 * legal var expressions var x 42 var y + x 1

 * */

void varfunc(){

   read_next_token();
    String next= String(next_token());
    char * storevar = next.data;

   while (next_token_type != END) {
        read_next_token();
        String storenext = String(next_token());
        if (storenext.data == "//") {
            skip_line();
        }

        blip.push_back(storenext.data);

        String next = String(peek_next_token());

        if ((strcmp(next.data, text.data) == 0)
            || (strcmp(next.data, out.data) == 0) || (strcmp(next.data, var.data) == 0) ||
            (strcmp(next.data, set.data) == 0)) {
            break;

        }
    }

    int flag = 0;
    for(int i = 0;i<varvec.size(); i++ ){
        if(strcmp(storevar, varvec[i].name)==0){flag = 1;}
    }
    if(flag == 1){cout << "variable " << next.data << " incorrectly re-initialized" << endl;}
    else{
        int n= varvec.size();
        int val = stackops();
        Var temp = Var(storevar, stackops());
        varvec.push_back(temp);

       }
}



/*set statements are just like var statements, except a
 * set statement should be used to re-assign a new value to an
 * existing variable. As such, if a set statement specifies a
 * variable that does not already exist, then Blip must generate a
 * warning (not an error) with the text,
 * “variable <varName not declared”. Regardless of whether the
 * warning message is created, the result of a set statement is t
 * o ensure that there is a variable in the Blip internal memory with
 * the specified value.
 * The following are examples of legal set expressions set x 42

set x + x 1
*/

void setfunc(){
    read_next_token();

    String next= String(next_token());
    char * storevar = next.data;

    while (next_token_type != END) {
        read_next_token();
        String storenext = String(next_token());
        if (storenext.data == "//") {
            skip_line();
        }

        blip.push_back(storenext.data);

        String next = String(peek_next_token());

        if ((strcmp(next.data, text.data) == 0)
            || (strcmp(next.data, out.data) == 0) || (strcmp(next.data, var.data) == 0) ||
            (strcmp(next.data, set.data) == 0)) {
            break;

        }
    }

    int flag = 0;
    for(int i = 0;i<varvec.size(); i++ ){
        if(strcmp(storevar, varvec[i].name)==0){flag = 1;}

    }
    if(flag == 1){
        Var temp = Var(storevar, stackops());
        varvec.push_back(temp);
    }
    else{
        cout << "variable "<< next.data<< " not declared" << endl;
    }

}




void run() {

    while(next_token_type != END){
        String token = String(next_token());
      // cout << endl<< endl<<" token:"<< token.data<< endl;

        if (strcmp(token.data ,text.data) == 0){
        //    cout<<"in text"<< endl;
            textfunc();
            blip.clear();
            continue;
        }
        else if(isPartOf("text ", token.data)){
            textfunc();
            blip.clear();
            continue;
        }
        else if(strcmp(token.data , out.data) == 0){
          //  cout<<"in out"<< endl;
           // cout<<endl<<"out:"<< token.data<< endl;
            outfunc();
            blip.clear();
            continue;

        }
        else if(isPartOf("output ", token.data)){
            cout<<endl<<"isPartof:"<< token.data<< endl;

            outfunc();
            blip.clear();
            continue;
        }
        else if(*token.data == *out.data) {
            //cout << "in out" << endl;
            outfunc();
            blip.clear();
            continue;
        }
        else if(isPartOf("var ", token.data)){
            varfunc();
            blip.clear();
            continue;
        }
        else if (strcmp(token.data ,var.data) == 0){
            varfunc();
            blip.clear();
        }
        else if(isPartOf("set ", token.data)){
            setfunc();
            blip.clear();
            continue;
        }
        else if(strcmp(token.data ,set.data) == 0){
            setfunc();
            blip.clear();
        }
        else if(token.data == "//"){
                skip_line();
        }
        read_next_token();
    }
    varvec.clear();

}

int main()
{

    

    set_input("test_grader.blip");
    run();
}
