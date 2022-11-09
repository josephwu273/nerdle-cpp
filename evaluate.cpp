//https://www.geeksforgeeks.org/expression-evaluation/
#include <string>
#include <stack>
#include <cmath>
#include <iostream>
#include <exception>
using std::string;
using std::cout;
using std::stack;
using std::domain_error;
// Function to find precedence of
// operators.
int precedence(char op){
	if(op == '+'||op == '-'){return 1;}
	if(op == '*'||op == '/'){return 2;}
	if(op ==  '^'){return 3;}
	return 0;
}

// Function to perform arithmetic operations.
float applyOp(float a,  float b, char op){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
		        if(b==0){throw domain_error("divide by 0");}
		        else{return a / b;}
		case '^': return pow(a,b);
		default: return -1;
	}
}

// Function that returns value of
// expression after evaluation.
int evaluate(string tokens){
	int i;
	bool neg = false;
	bool can_take_bin = false;
	stack <float> values; // stack to store integer values.
	stack <char> ops; // stack to store operators.
	
	for(i = 0; i < tokens.length(); i++){
	    char t = tokens[i];
		
		if(isdigit(t)){
			float val = 0;
			while(i < tokens.length() && isdigit(tokens[i])){
				val = (val*10) + (t -'0');
				i++;
			}
			val = (neg)? -val : val;
			values.push(val);
			neg = false;
			can_take_bin = true;
			i--;
		}
		else if(!can_take_bin){
		    if(t=='-'){neg = !neg;}
		    continue;
		}
		// Current token is an operator.
		else
		{
		    if(t=='*' and tokens[i+1]=='*'){
		        t = '^';
		        i++;
		    }
			while(!ops.empty() && precedence(ops.top())>=precedence(t)){
				float val2 = values.top();
				values.pop();
				
				float val1 = values.top();
				values.pop();
				
				char op = ops.top();
				ops.pop();
				//cout<< val1 << op <<val2 << "\n";
				values.push(applyOp(val1, val2, op));
			}
			
			// Push current token to 'ops'.
			ops.push(t);
			can_take_bin = false;
		}
	}
	
	// Entire expression has been parsed at this
	// point, apply remaining ops to remaining
	// values.
	while(!ops.empty()){
		float val2 = values.top();
		values.pop();
				
		float val1 = values.top();
		values.pop();
				
		char op = ops.top();
		ops.pop();
		//cout<< val1 << op <<val2 << "\n";
		values.push(applyOp(val1, val2, op));
	}
	return values.top();
}

int main() {
	cout << evaluate("--4**+2") << "\n";
	cout << evaluate("5---4") << "\n";
	cout << evaluate("3/2*4") << "\n";
	try{
	    cout<<evaluate("5/0");
	}
	catch(domain_error d){
	    cout<<"nice try";
	    
	}
	return 0;
}