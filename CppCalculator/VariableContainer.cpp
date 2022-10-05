#include "VariableContainer.h"

void VariableContainer::writeVariable(std::string name, float value) {
	std::map<std::string, float>::iterator it;

	for (it = mapa.begin(); it != mapa.end(); it++) {				//je¿eli zmienna ju¿ istnieje - zmieniamy wartoœæ
		if (it->first == name) it->second = value;
	}

	mapa.insert(std::pair<std::string, float>(name, value));
}

float VariableContainer::getVariable(std::string name) {
	std::map<std::string, float>::iterator it;

	for (it = mapa.begin(); it != mapa.end(); it++) {
		if (it->first == name) return it->second;
	}
}

std::string VariableContainer::insertVariables(std::string input) {
	std::string answer = input;
	std::map<std::string, float>::iterator it;

	for (it = mapa.begin(); it != mapa.end(); it++) {
		std::regex repl(it->first);

		std::ostringstream ss;
		ss << it->second;

		answer = std::regex_replace(answer, repl, ss.str());
	}

	return answer;
}

std::map<std::string, float> VariableContainer::getVariableList() {
	return mapa;
}