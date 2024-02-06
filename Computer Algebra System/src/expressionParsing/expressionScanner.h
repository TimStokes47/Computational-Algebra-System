#include "MathematicalSymbol.h"
#include <string>

namespace Parsing {

	class ExpressionScanner {
	public:
		ExpressionScanner(const std::string& expression)
			: m_expression(expression), m_index(0)
		{}

		Symbol* readNextToken() {
			bool readingInteger = false;
			bool readingFloat = false;
			int intValue = 0;
			float floatValue = 0.0f;
			float factor = 1.0f;

			if (m_index == m_expression.length()) {
				return new EndOfFile;
			}

			while (m_expression[m_index] >= '0' && m_expression[m_index] <= '9') {
				readingInteger = true;
				intValue = intValue * 10 + (m_expression[m_index] - '0');
				m_index++;
			}

			if (m_expression[m_index] == '.') {
				readingFloat = true;
				readingInteger = false;
				floatValue = (float)intValue;
				m_index++;
			}

			while (m_expression[m_index] >= '0' && m_expression[m_index] <= '9') {
				factor /= 10.0f;
				floatValue = floatValue + factor * (m_expression[m_index] - '0');
				m_index++;
			}

			if (readingInteger) {
				nameLastRead = true;
				return new Integer(intValue);
			}

			if (readingFloat) {
				nameLastRead = true;
				return new Float(floatValue);
			}

			if ((m_expression[m_index] >= 'a' && m_expression[m_index] <= 'z') || (m_expression[m_index] >= 'A' && m_expression[m_index] <= 'Z')) {
				nameLastRead = true;
				char character = m_expression[m_index];
				m_index++;
				return new Variable(character);
			}

			switch (m_expression[m_index]) {
			case '+':
				m_index++;
				nameLastRead = false;
				return new Addition;
			case '-':
				m_index++;
				if (nameLastRead) {
					nameLastRead = false;
					return new Subtraction;
				}
				else {
					return new UnaryMinus;
				}
			case '*':
				m_index++;
				nameLastRead = false;
				return new Multiplication;
			case '/':
				m_index++;
				nameLastRead = false;
				return new Division;
			case '(':
				m_index++;
				nameLastRead = false;
				return new Symbol(MathsToken::OPEN_BRACKET);
			case ')':
				m_index++;
				nameLastRead = true;
				return new Symbol(MathsToken::CLOSE_BRACKET);
			}
		}

		std::vector<Symbol*> tokeniseExpression() {
			std::vector<Symbol*> tokenisedExpression;

			tokenisedExpression.push_back(readNextToken());
			while (tokenisedExpression[tokenisedExpression.size() - 1]->getType() != MathsToken::END_OF_FILE) {
				tokenisedExpression.push_back(readNextToken());
			}
			tokenisedExpression.pop_back();
			return tokenisedExpression;
		}

	private:
		std::string m_expression;
		unsigned int m_index;
		bool nameLastRead = false;
	};

}