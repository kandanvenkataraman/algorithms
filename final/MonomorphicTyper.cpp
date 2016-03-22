// topcoder SRM 286 Div 2 level 3
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Expression {

	string  name;

	list<Expression> expressionList;
};

struct Val {
	string name;

	string type;

	list<string> typeList;

};



class MonomorphicTyper {

map<string, Val> valMap;

Val GetVal(string &s)
{
	Val v;
	int i = 0;
	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		i++;

	v.name = s.substr(0, i);
	if (s[i] == '(') {
		i++;
		int start = i;
		while (s[i] != ')') {
			while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
				i++;
			v.typeList.push_back(s.substr(start, i - start));
			if (s[i] == ',') {
				i++;
				start = i;
			}
		}
		i++;
	}
	i++;
	v.type = s.substr(i, s.length()-i);
	return v;
}

Expression GetExpression(string &expression, int &i)
{
	Expression e;
	int start = i;
	while ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z'))
		i++;

	e.name = expression.substr(start, i-start);

	if (i == expression.length() || expression[i] != '(')
		return e;

	i++; // skipping over '('
	while (expression[i] != ')') {
		e.expressionList.push_back(GetExpression(expression, i));
		if (expression[i] == ',')
			i++;
	}
	i++;
	return e;
}

string EvalExpression(Expression &e)
{
	if (valMap.find(e.name) == valMap.end())
		return string("");;

	map<string, Val>::iterator iter = valMap.find(e.name);

	if (iter->second.typeList.size() != e.expressionList.size())
		return string("");;

	list<string>::iterator iter2 = iter->second.typeList.begin();
	list<Expression>::iterator iter3 = e.expressionList.begin();
	while(iter3 != e.expressionList.end()) {
		
		if (EvalExpression(*iter3) != *iter2)
			return string("");
		
		iter2++;
		iter3++;
	}

	return iter->second.type;
}

public:
string infer(string expression, vector<string> definitions)
{

	for (int i = 0; i < definitions.size(); i++) {

		Val v = GetVal(definitions[i]);

		valMap[v.name] = v;
	}

	int idx = 0;
	Expression e = GetExpression(expression, idx);

	return EvalExpression(e);

}
};
