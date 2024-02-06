#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "grammar.h"

class Expression {
public:
	Expression() : Expression(0) {}
	Expression(std::string expression);
	Expression(int value);
	Expression(float value);
	Expression(Parsing::Node* root);
	Expression(const Expression& expression);
	
	operator float() const;
	operator std::string() const;

	Expression operator+=(const Expression& rhs);
	Expression operator+=(float rhs);
	Expression operator-=(const Expression& rhs);
	Expression operator-=(float rhs);
	Expression operator*=(const Expression& rhs);
	Expression operator*=(float rhs);
	Expression operator/=(const Expression& rhs);
	Expression operator/=(float rhs);

	friend Expression operator+(const Expression& lhs, const Expression& rhs);
	friend Expression operator+(const Expression& lhs, float rhs);
	friend Expression operator+(float lhs, const Expression& rhs);
	friend Expression operator+(const Expression& lhs, int rhs);
	friend Expression operator+(int lhs, const Expression& rhs);
	
	friend Expression operator-(const Expression& lhs, const Expression& rhs);
	friend Expression operator-(const Expression& lhs, float rhs);
	friend Expression operator-(float lhs, const Expression& rhs);	
	friend Expression operator-(const Expression& lhs, int rhs);
	friend Expression operator-(int lhs, const Expression& rhs);
	
	friend Expression operator*(const Expression& lhs, const Expression& rhs);
	friend Expression operator*(const Expression& lhs, float rhs);
	friend Expression operator*(float lhs, const Expression& rhs);	
	friend Expression operator*(const Expression& lhs, int rhs);
	friend Expression operator*(int lhs, const Expression& rhs);
	
	friend Expression operator/(const Expression& lhs, const Expression& rhs);
	friend Expression operator/(const Expression& lhs, float rhs);
	friend Expression operator/(float lhs, const Expression& rhs);
	friend Expression operator/(const Expression& lhs, int rhs);
	friend Expression operator/(int lhs, const Expression& rhs);

	Expression operator-();
private:
	static void initialiseMathsGrammar();
	static bool s_isGrammarInitialised;
	static Parsing::Grammar s_grammar;

	Parsing::Node* m_root;
};

#endif