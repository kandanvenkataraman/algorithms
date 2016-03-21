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

public:
string infer(string expression, vector<string> definitions)
{

	for (int i = 0; i < definitions.size(); i++) {

		Val v = GetVal(definition[i]);

		valMap[v.name] = v;
	}

	Expression e = GetExpression(expression);

	if (EvalExpression(e))
		return valMap[e.name];

	return string("");
}
};
