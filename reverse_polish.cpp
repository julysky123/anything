/*-------------------------------------------*/
/*    역폴란드 표기법의 평가 polish_p.cpp    */
/*-------------------------------------------*/
#include <iostream>
#include <cstdlib>      // for exit()
#include <cctype>       // for is...()
#include <vector>
#include <string>
using namespace std;

bool polish(char* s);
int execute();
int getvalue(int ch);
int order(int ch);
void push(int n);
int pop();
int top();

struct Variable{
	int type;
	union {
		int* p;
		int n;
	}v;
};

enum class SymType{VAR, FUNC};
struct Sym{
	string name;
	SymType type;
};

class SymManager {
	vector<Sym> symTable;
};



#define STK_SIZ 20
int stack[STK_SIZ + 1];                          /* 스택 */
int stkct;                                     /* 스택 포인터 */
char plsh_out[80];                             /* 역폴란드 출력 */

int main()
{
	char siki[80];
	int ans;

	cout << "입력: "; cin.getline(siki, 80);     /* 한 줄 읽기 */
	polish(siki);
	if (plsh_out[0] == '\0') exit(1);            /* 유효한 식이 없다 */
	ans = execute();
	cout << "변환: " << plsh_out << endl;
	cout << "결과: " << ans << endl;

	return 0;
}

//한칸씩 token 순회하면서 tokenKind로 비교하도록한다.
bool polish(char* s)
{
	int wk;
	char* out = plsh_out;

	stkct = 0;
	for (;;) {
		while (isspace(*s)) { ++s; }           /* 공백 건너뛰기         */
		if (*s == '\0') {                      /* 행의 끝이다           */
			while (stkct > 0) {                /* 스택의 나머지를 출력  */
				*out = pop();
				if (*out  == '(') {
					puts("'('와 ')'의 개수가 맞지 않습니다.\n"); 
					(*out)++;
					return false;
				}
				else if (*out == '[') {
					puts("'['와 ']'의 개수가 맞지 않습니다.\n");
					(*out)++;
					return false;
				}
				else if (*out == '!') {
					puts("함수가 닫히지 않았습니다.\n");
					(*out)++;
					return false;
				}
				(*out)++;
			}
			break;
		}
		if (islower(*s) || isdigit(*s) || *s=='!') {       /* 변수 or 함수 ident check */
			//var 인지 func 인지 symtable에서 확인.

			if (islower(*s) || isdigit(*s)) {				//var 이면
				if (false) { return false; }//syntax	
				*out++ = *s++; continue;
			}
			else if(*s=='!'){		//함수이면.
				if (false) { return false; }//syntax	
				push(*s++);
				s++;
				continue;
			}
			else {	// errornum시 (실제 구문에서는 맨위로 올릴것.)
				//syntax 오류. 
			}

		}
		switch (*s) {
		case '(':                              /* ( 라면 저장          */
			if (false) { return false; }//syntax				   
			push(*s);
			break;
		case ')':                              /* ) 라면                */
			if (false) { return false; }//syntax				   
			while (top() != '(' && top() != '!') {      /* ( 를 만날 때까지 출력 */
				wk = pop();
				*out++ = wk;
				if (stkct == 0) { puts("'('와 ')'의 개수가 맞지 않습니다.\n"); return false; } //syntax
			}
			if (pop() == '!') {
				*out++ = '!';
			}
			break;
		case '[':
			if (false) { return false; }//syntax				   
			push(*s);
			break;
		case ']':
			if (false) { return false; }//syntax				   
			while ((wk = pop()) != '[') {      /* ( 를 만날 때까지 출력 */
				*out++ = wk;
				if (stkct == 0) { puts("'['와 ']'의 개수가 맞지 않습니다.\n"); return false; } //syntax
			}
			*out++ = '[';
			break;

		case ',':
			if (false) { return false; }//syntax	//
			while (top() != '!') {
				wk = pop();
				*out++ = wk;
				if (stkct == 0) { puts("','의 위치가 올바르지 않습니다.\n"); return false; } //syntax
			}
			break;

		default:                               /*  연산자             */
			if (order(*s) == -1) {             /* 이용부적합문자      */
				cout << "바르지 않은 문자: " << *s << endl; return false;
			}            /* 자신보다 우선순위가 높은 요소가 스택 탑에 있는 동안*/
			while (stkct > 0 && (order(stack[stkct]) >= order(*s))) {
				*out++ = pop();                /* 스택 내용을 출력 */
			}
			push(*s);                          /* 현재 요소를 저장      */
		}
		s++;
	}
	*out = '\0';
	return true;
}

int execute()                                            /* 식의 계산  */
{
	int d1, d2;
	char* s;

	stkct = 0;
	for (s = plsh_out; *s; s++) {
		if (islower(*s))                       /* 변수라면           */
			push(getvalue(*s));                /* 값을 스택에 저장   */
		else if (isdigit(*s))                  /* 숫자라면           */
			push(*s - '0');                    /* 값을 스택에 저장   */
		else {                                 /* 연산자라면         */
			d2 = pop(); d1 = pop();            /* 두 값을 꺼낸다     */
			switch (*s) {
			case '+': 
				push(d1 + d2); break;      /* 계산결과를 저장한다 */
			case '-': push(d1 - d2); break;
			case '*': push(d1 * d2); break;
			case '/': if (d2 == 0) { puts("0으로 나눔"); exit(1); }
					push(d1 / d2); break;
			case '=':
				push(d1);
				break;
			case '[':	//arr
				push(d1);
				break;
			//	push((int)((int*)d1 + d2)); break;
			case '!':	//func
				//symbol table에서 변수 개수 확인 후 pop해서 쓰기.

				//saveStat
				//push(d1);
				//push(d2);
				push(d1 + d2);
				break;
			case '.':  //member
				push(d1);
				break;

			}
		

		}
	}
	if (stkct != 1) { cout << "error\n"; exit(1); }
	return pop();                                      /* 계산 결과를 반환한다 */
}

int getvalue(int ch)                                   /* 1~26을 반환한다 */
{
	if (islower(ch)) return ch - 'a' + 1;
	return 0;
}

int order(int ch)                                        /* 우선순위 */
{
	switch (ch) {
	case '.': return 5;
	case '*': case '/': return 4;
	case '+': case '-': return 3;
	case '=': return 2;
	case '(':           return 1;
	}
	return -1;
}

void push(int n)                                     /* 스택 저장 */
{
	if (stkct + 1 > STK_SIZ) { puts("stack overflow"); exit(1); }
	stack[++stkct] = n;
}

int pop()                                            /* 스택 추출 */
{
	if (stkct < 1) { puts("stack underflow"); exit(1); }
	return stack[stkct--];
}

int top()                                            /* 스택 추출 */
{
	if (stkct < 1) { puts("stack underflow"); exit(1); }
	return stack[stkct];
}
