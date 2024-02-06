#ifndef MATHEMATICAL_SYMBOL_H
#define MATHEMATICAL_SYMBOL_H

#include <memory>
#include <string>
#include <map>

namespace Parsing {

	enum class MathsToken {
		NULL_TOKEN = -5,
		END_OF_FILE = -4,
		EPSILON = -3,
		ARROW = -2,
		DOT = -1,

		NAME,
		OPERATOR_ADD,
		OPERATOR_SUBTRACT,
		OPERATOR_MULTIPLY,
		OPERATOR_DIVIDE,
		OPERATOR_UNARY,
		OPEN_BRACKET,
		CLOSE_BRACKET,
		GOAL,
		EXPRESSION,
		TERM,
		VALUE,
		FACTOR,

		_COUNT,
		_BEGIN = 0,
		_END = _COUNT
	};

	class Node;

	class Symbol {
	public:
		Symbol(MathsToken type)
			: m_type(type)
		{}
		virtual ~Symbol() {}
		MathsToken getType() { return m_type; }
		virtual std::string createString(Node* child) { return ""; }
		virtual float evaluate(Node* child) { return 0.0f; }


	protected:
		MathsToken m_type;
	};



	class Node {
	public:
		Node(std::unique_ptr<Symbol> symbol) : m_symbol(std::move(symbol)) {}
		Node(Node* node) {
			m_symbol = node->m_symbol;
			if (node->child)
				child = new Node(node->child);
			if (node->next)
				next = new Node(node->next);
			
		}

		/*~Node() {
			if (child) delete child;
			if (next) delete next;
		}*/
		//std::shared_ptr<Node> parent = nullptr;
		Node* child = nullptr;
		Node* next = nullptr;
		//std::shared_ptr<Node> previous = nullptr;

		std::string createString() {
			return m_symbol->createString(child);
		}

		std::shared_ptr<Symbol>& getSymbol() { return m_symbol; }

		float evaluate() {
			return m_symbol.get()->evaluate(child);
		}

		void restructure(Node* parent, Node* previous) {
			if (m_symbol->getType() == MathsToken::EXPRESSION || m_symbol->getType() == MathsToken::FACTOR || m_symbol->getType() == MathsToken::VALUE || m_symbol->getType() == MathsToken::TERM) {
				Node* symbolToRestructure = child;
				Node* previousNode = nullptr;

				while (symbolToRestructure) {
					symbolToRestructure->restructure(this, previousNode);
					previousNode = symbolToRestructure;
					symbolToRestructure = symbolToRestructure->next;
				}

			}
			else if (m_symbol->getType() == MathsToken::OPERATOR_UNARY) {
				child = next;
				child->restructure(this, nullptr);
				next = nullptr;
			}
			else if (m_symbol->getType() == MathsToken::OPEN_BRACKET) {
				parent->child = next;
			}
			else if (m_symbol->getType() == MathsToken::CLOSE_BRACKET) {
				Node* temp = parent->child;
				while (temp->next != this) {
					temp = temp->next;
				}
				temp->next = nullptr;
			}
			else if (m_symbol->getType() == MathsToken::OPERATOR_ADD || m_symbol->getType() == MathsToken::OPERATOR_SUBTRACT || m_symbol->getType() == MathsToken::OPERATOR_MULTIPLY || m_symbol->getType() == MathsToken::OPERATOR_DIVIDE) {
				child = previous;
				child->next = next;
				parent->child = this;
				next = next->next;
				child->next->restructure(this, child);
			}
		}

		void removeChains() {
			Node* symbol = child;
			while (symbol) {
				symbol->removeChains();
				symbol = symbol->next;
			}

			if (m_symbol->getType() == MathsToken::EXPRESSION || m_symbol->getType() == MathsToken::FACTOR || m_symbol->getType() == MathsToken::VALUE || m_symbol->getType() == MathsToken::TERM) {
				if (child && !child->next) {
					m_symbol = std::move(child->m_symbol);
					child = child->child;
					//if (previous) previous->next = child;
				}
			}
		}

	private:
		std::shared_ptr<Symbol> m_symbol;
	};

	class Expression : public Symbol {
	public:
		Expression() : Symbol(MathsToken::EXPRESSION) {}
	};

	class Name : public Symbol {
	public:
		Name() : Symbol(MathsToken::NAME) {}
	};

	class Operator : public Symbol {
	public:
		Operator(MathsToken type) : Symbol(type) {}
	};

	class Addition : public Operator {
	public:
		Addition() : Operator(MathsToken::OPERATOR_ADD) {}
		float evaluate(Node* child) {
			auto temp = child;
			float value = 0.0f;
			while (temp) {
				value += temp->evaluate();
				temp = temp->next;
			}
			return value;
		}

		std::string createString(Node* child) {
			return "(" + child->createString() + "+" + child->next->createString() + ")";
		}
	};

	class Subtraction : public Operator {
	public:
		Subtraction() : Operator(MathsToken::OPERATOR_SUBTRACT) {}
		float evaluate(Node* child) {
			auto temp = child;
			float value = temp->evaluate();
			while (temp->next) {
				value -= temp->next->evaluate();
				temp = temp->next;
			}
			return value;
		}

		std::string createString(Node* child) {
			return "(" + child->createString() + "-" + child->next->createString() + ")";
		}
	};

	class UnaryMinus : public Operator {
	public:
		UnaryMinus() : Operator(MathsToken::OPERATOR_UNARY) {}
		float evaluate(Node* child) {
			return -child->evaluate();
		}

		std::string createString(Node* child) {
			return "-" + child->createString();
		}
	};

	class Multiplication : public Operator {
	public:
		Multiplication() : Operator(MathsToken::OPERATOR_MULTIPLY) {}
		float evaluate(Node* child) {
			/*auto temp = child;
			float value = temp->getSymbol()->evaluate(temp->child);
			while (temp->next) {
				value *= temp->next->getSymbol()->evaluate(temp->next->child);
				temp = temp->next;
			}
			return value;*/
			auto* temp = child;
			float value = temp->evaluate();
			while (temp->next) {
				value *= temp->next->evaluate();
				temp = temp->next;
			}
			return value;
		}

		std::string createString(Node* child) {
			return child->createString() + "*" + child->next->createString();
		}
	};

	class Division : public Operator {
	public:
		Division() : Operator(MathsToken::OPERATOR_DIVIDE) {}
		float evaluate(Node* child) {
			auto temp = child;
			float value = temp->evaluate();
			while (temp->next) {
				value /= temp->next->evaluate();
				temp = temp->next;
			}
			return value;
		}

		std::string createString(Node* child) {
			return child->createString() + "/" + child->next->createString();
		}
	};

	class Integer : public Name {
	public:
		Integer(int value) : m_value(value) {}

		float evaluate(Node* child) override { return static_cast<float>(m_value); }

		std::string createString(Node* child) {
			return std::to_string(m_value);
		}

	private:
		int m_value;
	};

	class Float : public Name {
	public:
		Float(float value) : m_value(value) {}
		float evaluate(Node* child) override { return m_value; }

		std::string createString(Node* child) {
			return std::to_string(m_value);
		}

	private:
		float m_value;
	};

	class Variable : public Name {
	public:
		Variable(char character) : m_character(character) {
			s_map[m_character] = 1.0f;
		}
		float evaluate(Node* child) override { return s_map[m_character]; }
		static std::map<char, float> s_map;

		std::string createString(Node* child) {
			return std::string(1, m_character);
		}

	private:
		char m_character;
	};

	class EndOfFile : public Symbol {
	public:
		EndOfFile() : Symbol(MathsToken::END_OF_FILE) {}
	};

}

#endif