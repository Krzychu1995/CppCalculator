#include <math.h>
#include <string>
#include <regex>
#include <queue>
#include <stack>
#include <map>
#include <sstream>

#ifndef VariableContainer_src
#define VariableContainer_src

class VariableContainer {
public:
	void writeVariable(std::string name, float value);
	float getVariable(std::string name);
	std::string insertVariables(std::string input);
	std::map<std::string, float> getVariableList();
private:
	std::map<std::string, float> mapa;
};

#endif // !VariableContainer_src
