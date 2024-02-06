#include "expression.h"
#include "expressionScanner.h"

Expression::Expression(std::string expression)
{
	if (!s_isGrammarInitialised) {
		initialiseMathsGrammar();
	}
	Parsing::ExpressionScanner scanner(expression);
	m_root = s_grammar.parseExpression(scanner.tokeniseExpression());
	if (m_root) {
		m_root->restructure(nullptr, nullptr);
		m_root->removeChains();
	}
	else {
		m_root = new Parsing::Node(std::make_unique<Parsing::Integer>(0));
	}
}

Expression::Expression(int value)
{
	m_root = new Parsing::Node(std::make_unique<Parsing::Integer>(value));
}

Expression::Expression(float value)
{
	m_root = new Parsing::Node(std::make_unique<Parsing::Float>(value));
}

Expression::Expression(Parsing::Node* root)
{
	m_root = root;
}

Expression::Expression(const Expression& expression)
{
	m_root = new Parsing::Node(expression.m_root);
}

Expression::operator float() const
{
	return m_root->evaluate();
}

Expression::operator std::string() const
{
	return m_root->createString();
}

Expression Expression::operator+=(const Expression& rhs)
{
	return *this + rhs;
}

Expression Expression::operator+=(float rhs)
{
	return (*this + rhs);
}

Expression Expression::operator-=(const Expression& rhs)
{
	return *this - rhs;
}

Expression Expression::operator-=(float rhs)
{
	return *this - rhs;
}

Expression Expression::operator*=(const Expression& rhs)
{
	return *this * rhs;
}

Expression Expression::operator*=(float rhs)
{
	return *this * rhs;
}

Expression Expression::operator/=(const Expression& rhs)
{
	return *this / rhs;
}

Expression Expression::operator/=(float rhs)
{
	return *this / rhs;
}

Expression Expression::operator-()
{
	Parsing::Node* root = new Parsing::Node(std::make_unique<Parsing::UnaryMinus>());
	root->child = m_root;

	return Expression(root);
}

void Expression::initialiseMathsGrammar()
{
	std::map<std::string, std::vector<Parsing::MathsToken>> mathsRules;
	mathsRules["1"] = { Parsing::MathsToken::GOAL, Parsing::MathsToken::ARROW, Parsing::MathsToken::EXPRESSION };

	mathsRules["2"] = { Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::ARROW, Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::OPERATOR_ADD, Parsing::MathsToken::TERM };
	mathsRules["3"] = { Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::ARROW, Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::OPERATOR_SUBTRACT, Parsing::MathsToken::TERM };
	mathsRules["4"] = { Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::ARROW, Parsing::MathsToken::TERM };

	mathsRules["5"] = { Parsing::MathsToken::TERM, Parsing::MathsToken::ARROW, Parsing::MathsToken::TERM, Parsing::MathsToken::OPERATOR_MULTIPLY, Parsing::MathsToken::VALUE };
	mathsRules["6"] = { Parsing::MathsToken::TERM, Parsing::MathsToken::ARROW, Parsing::MathsToken::TERM, Parsing::MathsToken::OPERATOR_DIVIDE, Parsing::MathsToken::VALUE };
	mathsRules["7"] = { Parsing::MathsToken::TERM, Parsing::MathsToken::ARROW, Parsing::MathsToken::VALUE };

	mathsRules["8"] = { Parsing::MathsToken::VALUE, Parsing::MathsToken::ARROW, Parsing::MathsToken::OPERATOR_UNARY, Parsing::MathsToken::FACTOR };
	mathsRules["9"] = { Parsing::MathsToken::VALUE, Parsing::MathsToken::ARROW, Parsing::MathsToken::FACTOR };

	mathsRules["10"] = { Parsing::MathsToken::FACTOR, Parsing::MathsToken::ARROW, Parsing::MathsToken::OPEN_BRACKET, Parsing::MathsToken::EXPRESSION, Parsing::MathsToken::CLOSE_BRACKET };
	mathsRules["11"] = { Parsing::MathsToken::FACTOR, Parsing::MathsToken::ARROW, Parsing::MathsToken::NAME };


	s_grammar = Parsing::Grammar(mathsRules);
}

bool Expression::s_isGrammarInitialised = false;
Parsing::Grammar Expression::s_grammar;

Expression operator+(const Expression& lhs, const Expression& rhs)
{
	Parsing::Node* root = new Parsing::Node(std::make_unique<Parsing::Addition>());
	root->child = lhs.m_root;
	root->child->next = new Parsing::Node(rhs.m_root);
	root->child->next->next = nullptr;

	return Expression(root);
}

Expression operator+(const Expression& lhs, float rhs)
{
	return lhs + Expression(rhs);
}

Expression operator+(float lhs, const Expression& rhs)
{
	return Expression(lhs) + rhs;
}

Expression operator+(const Expression& lhs, int rhs)
{
	return lhs + Expression(rhs);
}

Expression operator+(int lhs, const Expression& rhs)
{
	return Expression(lhs) + rhs;
}

Expression operator-(const Expression& lhs, const Expression& rhs)
{
	Parsing::Node* root = new Parsing::Node(std::make_unique<Parsing::Subtraction>());
	root->child = lhs.m_root;
	root->child->next = new Parsing::Node(rhs.m_root);
	root->child->next->next = nullptr;

	return Expression(root);
}

Expression operator-(const Expression& lhs, float rhs)
{
	return lhs - Expression(rhs);
}

Expression operator-(float lhs, const Expression& rhs)
{
	return Expression(lhs) - rhs;
}

Expression operator-(const Expression& lhs, int rhs)
{
	return lhs - Expression(rhs);
}

Expression operator-(int lhs, const Expression& rhs)
{
	return Expression(lhs) - rhs;
}

Expression operator*(const Expression& lhs, const Expression& rhs)
{
	Parsing::Node* root = new Parsing::Node(std::make_unique<Parsing::Multiplication>());
	root->child = lhs.m_root;
	root->child->next = new Parsing::Node(rhs.m_root);
	root->child->next->next = nullptr;

	return Expression(root);
}

Expression operator*(const Expression& lhs, float rhs)
{
	return lhs * Expression(rhs);
}

Expression operator*(float lhs, const Expression& rhs)
{
	return Expression(lhs) * rhs;
}

Expression operator*(const Expression& lhs, int rhs)
{
	return lhs * Expression(rhs);
}

Expression operator*(int lhs, const Expression& rhs)
{
	return Expression(lhs) * rhs;
}

Expression operator/(const Expression& lhs, const Expression& rhs)
{
	Parsing::Node* root = new Parsing::Node(std::make_unique<Parsing::Division>());
	root->child = lhs.m_root;
	root->child->next = new Parsing::Node(rhs.m_root);
	root->child->next->next = nullptr;
	return Expression(root);
}

Expression operator/(const Expression& lhs, float rhs)
{
	return lhs / Expression(rhs);
}

Expression operator/(float lhs, const Expression& rhs)
{
	return Expression(lhs) / rhs;
}

Expression operator/(const Expression& lhs, int rhs)
{
	return lhs / Expression(rhs);
}

Expression operator/(int lhs, const Expression& rhs)
{
	return Expression(lhs) / rhs;
}