
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "rule.h"
#include <map>
#include <string>
#include <stack>
#include <iostream>
#include <memory>
#include <fstream>


namespace Parsing {

	class Grammar {
	public:
		Grammar() = default;
		Grammar(std::map<std::string, std::vector<MathsToken>> _rules);

		bool isTerminal(MathsToken token);

		std::vector<MathsToken> first(MathsToken token);

		std::vector<AugmentedRule> closure(std::vector<AugmentedRule> set);

		std::vector<AugmentedRule> goTo(std::vector<AugmentedRule> set, MathsToken input);

		std::vector<std::vector<AugmentedRule>> buildCC();

		void buildTable();
		void writeTable();
		void loadTable(std::ifstream& actionFile, std::ifstream& goToFile);

		Node* parseExpression(std::vector<Symbol*> expression);

		std::vector<BNFRule> m_rules;
		std::map<std::string, std::vector<MathsToken>> rules;

	private:
		std::vector<MathsToken> m_terminals;
		std::vector<MathsToken> m_nonTerminals;

		std::map<std::string, std::map<MathsToken, std::string>> m_action;
		std::map<std::string, std::map<MathsToken, std::string>> m_goTo;
	};

}

#endif