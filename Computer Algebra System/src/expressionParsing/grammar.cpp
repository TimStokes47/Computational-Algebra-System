#include "grammar.h"

#include <map>
#include <string>
#include <stack>
#include <iostream>
#include <memory>
#include <fstream>

//void generateParents(std::shared_ptr<Node> root) {
//	auto temp = root->child;
//	while (temp) {
//		temp->parent = root;
//		if (temp->next) {
//			temp->next->previous = temp;
//		}
//		generateParents(temp);
//		temp = temp->next;
//	}
//}

namespace Parsing {

	Grammar::Grammar(std::map<std::string, std::vector<MathsToken>> _rules)
		: m_terminals{}, m_nonTerminals{}, rules(_rules)
	{

		for (int i = static_cast<int>(MathsToken::_BEGIN); i < static_cast<int>(MathsToken::_END); i++) {
			MathsToken token = static_cast<MathsToken>(i);
			bool isTerminal = true;
			for (auto rule : rules) {
				if (rule.second[0] == token) {
					isTerminal = false;
				}
			}
			if (isTerminal) {
				m_terminals.push_back(token);
			}
			else {
				m_nonTerminals.push_back(token);
			}
		}

		for (MathsToken nonTerminal : m_nonTerminals) {
			m_rules.push_back({ nonTerminal });
		}
		for (auto rule : rules) {
			for (auto& formattedRule : m_rules) {
				if (formattedRule.production == rule.second[0]) {
					std::vector<MathsToken> definition = {};
					for (int i = 2; i < rule.second.size(); i++) {
						definition.push_back(rule.second[i]);
					}
					formattedRule.addDefinition(definition);
				}
			}
		}
		std::ifstream actionFile("action.txt");
		std::ifstream goToFile("goTo.txt");

		if (actionFile.is_open() && goToFile.is_open()) {
			loadTable(actionFile, goToFile);
		}
		else {
			buildTable();
		}
	}

	bool Grammar::isTerminal(MathsToken token) {
		bool isTerminal = false;
		for (auto terminal : m_terminals) {
			if (terminal == token) isTerminal = true;
		}
		return isTerminal;
	}

	std::vector<MathsToken> Grammar::first(MathsToken token) {
		if (isTerminal(token) || token == MathsToken::EPSILON || token == MathsToken::END_OF_FILE) {
			return { token };
		}

		if (token == MathsToken::NULL_TOKEN) {
			return {};
		}

		for (BNFRule rule : m_rules) {
			if (rule.production == token) {
				std::vector<MathsToken> set = {};
				for (ProductionDefinition definition : rule) {
					if (definition[0] != token) {
						for (MathsToken symbol : first(definition[0])) {
							if (std::find(set.begin(), set.end(), symbol) == set.end()) {
								set.push_back(symbol);
							}
						}
					}
				}
				return set;
			}
		}
	}

	std::vector<AugmentedRule> Grammar::closure(std::vector<AugmentedRule> set) {
		std::vector<AugmentedRule> closureSet = set;
		bool hasSetChanged = true;
		int itemsChecked = 0;

		while (hasSetChanged) {
			hasSetChanged = false;
			int setSize = static_cast<int>(closureSet.size());
			for (int i = itemsChecked; i < setSize; i++) {
				itemsChecked++;
				int dotLocation = closureSet[i].getDotLocation();
				for (BNFRule rule : m_rules) {
					if (rule.production == closureSet[i][dotLocation + 1]) {
						for (ProductionDefinition definition : rule) {
							std::vector<MathsToken> newItem = { rule.production, MathsToken::ARROW, MathsToken::DOT };
							newItem.insert(newItem.end(), definition.begin(), definition.end());

							for (MathsToken token : first(closureSet[i][dotLocation + 2])) {
								newItem.push_back(token);
								if (std::find(closureSet.begin(), closureSet.end(), newItem) == closureSet.end()) {
									closureSet.push_back(newItem);
									hasSetChanged = true;
								}
								newItem.pop_back();
							}
						}
					}
				}
			}
		}

		return closureSet;
	}

	std::vector<AugmentedRule> Grammar::goTo(std::vector<AugmentedRule> set, MathsToken input) {
		std::vector<AugmentedRule> moved = {};
		if (input == MathsToken::NULL_TOKEN) {
			return moved;
		}
		for (AugmentedRule augmentedRule : set) {
			int dotLocation = augmentedRule.getDotLocation();
			if (augmentedRule[dotLocation + 1] == input && dotLocation < augmentedRule.size() - 2) {
				AugmentedRule updatedRule = augmentedRule.getUpdatedState();
				if (std::find(moved.begin(), moved.end(), updatedRule) == moved.end()) {
					moved.push_back(updatedRule);
				}
			}
		}
		return closure(moved);
	}

	std::vector<std::vector<AugmentedRule>> Grammar::buildCC() {
		std::vector<std::vector<AugmentedRule>> cc = {};
		AugmentedRule initialRule = m_rules[0].buildAugmented(0);
		std::vector<AugmentedRule> cc0 = closure({ initialRule });
		cc.push_back(cc0);

		bool hasSetChanged = true;
		int processedSets = 0;
		while (hasSetChanged) {
			hasSetChanged = false;
			int size = static_cast<int>(cc.size());
			for (int i = processedSets; i < size; i++) {
				for (auto augmentedRule : cc[i]) {
					int dotLocation = augmentedRule.getDotLocation();
					auto temp = goTo(cc[i], augmentedRule[dotLocation + 1]);
					if (temp.size() > 0 && std::find(cc.begin(), cc.end(), temp) == cc.end()) {
						cc.push_back(temp);
						hasSetChanged = true;
					}
				}
				processedSets++;
			}
		}
		return cc;
	}

	void Grammar::buildTable() {
		auto cc = buildCC();
		for (int i = 0; i < cc.size(); i++) {
			for (AugmentedRule augmentedRule : cc[i]) {
				int dotLocation = augmentedRule.getDotLocation();

				if (isTerminal(augmentedRule[dotLocation + 1]) || augmentedRule[dotLocation + 1] == MathsToken::END_OF_FILE) {
					if (dotLocation == augmentedRule.size() - 2) {
						int ruleNumber = 0;
						for (auto rule : m_rules) {
							for (auto definition : rule) {
								ruleNumber++;
								if (rule.production == augmentedRule[0]) {
									bool match = true;
									for (int j = 0; j < definition.size(); j++) {
										if (definition[j] != augmentedRule[j + 2]) {
											match = false;
										}
									}
									if (match) {
										std::string id = "s" + std::to_string(i);
										std::string r = "r" + std::to_string(ruleNumber);
										m_action[id][augmentedRule[dotLocation + 1]] = r;
									}
								}
							}
						}
					}
					else {
						for (int j = 0; j < cc.size(); j++) {
							if (goTo(cc[i], augmentedRule[dotLocation + 1]) == cc[j]) {
								std::string id = "s" + std::to_string(i);
								std::string s = "s" + std::to_string(j);
								m_action[id][augmentedRule[dotLocation + 1]] = s;
							}
						}
					}
				}
				if (augmentedRule[dotLocation + 1] == MathsToken::END_OF_FILE && augmentedRule[0] == MathsToken::GOAL) {
					std::string id = "s" + std::to_string(i);
					m_action[id][MathsToken::END_OF_FILE] = "accept";
				}
			}

			for (MathsToken nonTerminal : m_nonTerminals) {
				for (int j = 0; j < cc.size(); j++) {
					if (goTo(cc[i], nonTerminal) == cc[j]) {
						std::string id = "s" + std::to_string(i);
						std::string s = "s" + std::to_string(j);
						m_goTo[id][nonTerminal] = s;
					}
				}
			}
		}
		writeTable();
	}

	void Grammar::writeTable() {
		std::ofstream actionFile("action.txt");
		for (auto const& [state, val] : m_action) {
			actionFile << state << "\n";
			for (auto const& [token, action] : val) {
				actionFile << static_cast<int>(token) << " " << action << "\n";
			}
			actionFile << "\n";
		}
		actionFile.close();

		std::ofstream goToFile("goTo.txt");
		for (auto const& [state, val] : m_goTo) {
			goToFile << state << "\n";
			for (auto const& [token, goTo] : val) {
				goToFile << static_cast<int>(token) << " " << goTo << "\n";
			}
			goToFile << "\n";
		}
		goToFile.close();
	}

	void Grammar::loadTable(std::ifstream& actionFile, std::ifstream& goToFile) {
		std::string line;
		std::string state = "";
		while (std::getline(actionFile, line)) {
			if (line[0] == 's') {
				state = line;
			}
			else {
				int position = line.find_first_of(' ');
				if (position != -1) {
					MathsToken token = static_cast<MathsToken>(std::stoi(line.substr(0, position)));
					std::string action = line.substr(position + 1, line.size() - position - 1);
					m_action[state][token] = action;
				}
			}
		}
		actionFile.close();

		while (std::getline(goToFile, line)) {
			if (line[0] == 's') {
				state = line;
			}
			else {
				int position = line.find_first_of(' ');
				if (position != -1) {
					MathsToken token = static_cast<MathsToken>(std::stoi(line.substr(0, position)));
					std::string goTo = line.substr(position + 1, line.size() - position - 1);
					m_goTo[state][token] = goTo;
				}
			}
		}
		goToFile.close();
	}

	Node* Grammar::parseExpression(std::vector<Symbol*> expression) {
		Node* root = nullptr;
		int numInFrontier = 0;
		std::string state = "s0";
		std::stack<std::string> stack;
		stack.push(state);
		int index = 0;
		Symbol* word = expression[index];

		while (true) {
			state = stack.top();

			if (m_action[state].find(word->getType()) == m_action[state].end()) {
				return nullptr;
			}
			else if (m_action[state][word->getType()][0] == 'r') {
				std::vector<MathsToken> rule = rules[m_action[state][word->getType()].substr(1, m_action[state][word->getType()].size() - 1)];
				int nodesToPop = (static_cast<int>(rule.size()) - 2);

				for (int i = 0; i < nodesToPop * 2; i++) {
					stack.pop();
				}
				numInFrontier -= nodesToPop;

				Node* parent = new Node(std::make_unique<Symbol>(rule[0]));
				Node* temp = root;
				if (numInFrontier == 0) {
					parent->child = temp;
					root = parent;
				}
				else {
					for (int i = 0; i < numInFrontier - 1; i++) {
						temp = temp->next;
					}
					parent->child = temp->next;
					temp->next = parent;
				}
				numInFrontier++;

				state = stack.top();
				stack.push(std::to_string(static_cast<int>(rule[0])));
				stack.push(m_goTo[state][rule[0]]);
			}
			else if (m_action[state][word->getType()][0] == 's') {
				stack.push(std::to_string(static_cast<int>(word->getType())));
				stack.push(m_action[state][word->getType()]);

				Node* newNode = new Node(std::unique_ptr<Symbol>(word));

				if (root == nullptr) {
					root = newNode;
				}
				else {
					Node* temp = root;
					while (temp->next != nullptr) temp = temp->next;
					temp->next = newNode;
				}
				numInFrontier++;
				index++;
				if (index >= expression.size()) {
					word = new EndOfFile;
				}
				else {
					word = expression[index];
				}
			}
			else if (m_action[state][word->getType()] == "accept") {
				break;
			}
		}
		//generateParents(root);
		return root;
	}
}