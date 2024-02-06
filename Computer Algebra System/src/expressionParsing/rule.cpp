#include "rule.h"

namespace Parsing {

	bool AugmentedRule::operator==(const AugmentedRule& rule) const {
		bool equal = true;
		if (rule.size() == size()) {
			for (int i = 0; i < size(); i++) {
				if (rule[i] != m_rule[i]) {
					equal = false;
				}
			}
		}
		else {
			equal = false;
		}
		return equal;
	}

	MathsToken AugmentedRule::operator[](int index) const {
		if (index >= size()) {
			return MathsToken::NULL_TOKEN;
		}
		else {
			return m_rule[index];
		}
	}

	AugmentedRule AugmentedRule::getUpdatedState() {
		int dotLocation = getDotLocation();
		std::vector<MathsToken> newState;
		for (int i = 0; i < dotLocation; i++) {
			newState.push_back(m_rule[i]);
		}
		newState.push_back(m_rule[dotLocation + 1]);
		newState.push_back(MathsToken::DOT);
		for (int i = dotLocation + 2; i < m_rule.size(); i++) {
			newState.push_back(m_rule[i]);
		}
		return AugmentedRule(newState);
	}

	int AugmentedRule::getDotLocation() {
		typename std::vector<MathsToken>::iterator it = std::find(m_rule.begin(), m_rule.end(), MathsToken::DOT);
		return static_cast<int>(std::distance(m_rule.begin(), it));
	}

	AugmentedRule BNFRule::buildAugmented(int index) {
		std::vector<MathsToken> rule = { production, MathsToken::ARROW, MathsToken::DOT };
		for (MathsToken token : m_definitions[index]) {
			rule.push_back(token);
		}
		rule.push_back(MathsToken::END_OF_FILE);
		return AugmentedRule(rule);
	}

}