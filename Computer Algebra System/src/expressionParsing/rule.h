#pragma once

#include "MathematicalSymbol.h"
#include <vector>

namespace Parsing {

	class ProductionDefinition {
	public:
		ProductionDefinition(std::vector<MathsToken> definition)
			: m_definition(definition)
		{}
		MathsToken& operator[](int index) {
			return m_definition[index];
		}
		int size() const { return static_cast<int>(m_definition.size()); }
		auto begin() { return m_definition.begin(); }
		auto end() { return m_definition.end(); }

	private:
		std::vector<MathsToken> m_definition;
	};

	class AugmentedRule {
	public:
		AugmentedRule(std::vector<MathsToken> rule)
			: m_rule(rule)
		{}

		auto begin() const { return m_rule.begin(); }
		auto end() const { return m_rule.end(); }

		int size() const { return static_cast<int>(m_rule.size()); }
		bool operator==(const AugmentedRule& rule) const;
		MathsToken operator[](int index) const;

		AugmentedRule getUpdatedState();
		int getDotLocation();

	private:
		std::vector<MathsToken> m_rule;
	};

	class BNFRule {
	public:
		BNFRule(MathsToken _production)
			: production(_production)
		{}

		void addDefinition(ProductionDefinition definition) {
			m_definitions.push_back(definition);
		}

		auto begin() { return m_definitions.begin(); }
		auto end() { return m_definitions.end(); }

		AugmentedRule buildAugmented(int index);

		std::vector<ProductionDefinition> definitions() { return m_definitions; }
		MathsToken production;

	private:
		std::vector<ProductionDefinition> m_definitions;
	};

}