/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 10:14:10 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/31 13:37:14 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.class.hpp"

AbstractVm::AbstractVm(void)
{
	this->_stack.reserve(0);
}

AbstractVm::AbstractVm(AbstractVm const &src)
{
	*this = src;
}

AbstractVm::~AbstractVm(void)
{
	this->_stack.clear();
}

AbstractVm&				AbstractVm::operator=(AbstractVm const &rhs)
{
	this->_stack.reserve(rhs._stack.size());
	this->_stack.insert(this->_stack.begin(), rhs._stack.begin(), rhs._stack.end());
	return *this;
}

void					AbstractVm::push(eOperandType type, std::string &value)
{
	Factory				tmp;

	this->_stack.insert(this->_stack.begin(), tmp.createOperand(type, value));
}

void					AbstractVm::setColor(eOperandType type)
{
	std::map<eOperandType, std::string>				colors;
	std::map<eOperandType, std::string>::iterator	it;

	colors[Int8] = ANSI_COLOR_RED;
	colors[Int16] = ANSI_COLOR_GREEN;
	colors[Int32] = ANSI_COLOR_YELLOW;
	colors[Float] = ANSI_COLOR_MAGENTA;
	colors[Double] = ANSI_COLOR_CYAN;
	it = colors.begin();
	while (it != colors.end())
	{
		if (it->first == type)
		{
			std::cout << it->second;
			return ;
		}
		it++;
	}
}

void					AbstractVm::dump(void)
{
	std::vector<IOperand const *>::iterator	it;

	it = this->_stack.begin();
	while (it != this->_stack.end())
	{
		this->setColor((*it)->getType());
		std::cout << (*it)->toString() << std::endl;
		std::cout << ANSI_COLOR_RESET;
		it++;
	}
}

void					AbstractVm::assert(eOperandType type, std::string &value)
{
	if (this->_stack.size() == 0)
		throw EmptyStackException("assert");
	std::vector<IOperand const *>::iterator	it;

	it = this->_stack.begin();
	if ((**it).getType() != type)
		throw AssertException("assert error : wrong type");
	if ((**it).toString() != value)
		throw AssertException("assert error : wrong value");
}

void					AbstractVm::pop(void)
{
	if (this->_stack.size() == 0)
		throw EmptyStackException("pop");
	this->_stack.erase(this->_stack.begin());
}

void					AbstractVm::add(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("add");
	it = this->_stack.begin();
	res = **it + **(it + 1);
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::sub(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("sub");
	it = this->_stack.begin();
	res = **(it + 1) - **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::mul(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("mul");
	it = this->_stack.begin();
	res = **(it + 1) * **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::div(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("div");
	it = this->_stack.begin();
	res = **(it + 1) / **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::mod(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("mod");
	it = this->_stack.begin();
	res = **(it + 1) % **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::max(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("max");
	it = this->_stack.begin();
	res = **(it + 1) > **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::min(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("min");
	it = this->_stack.begin();
	res = **(it + 1) < **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::avg(void)
{
	std::vector<IOperand const *>::iterator	it;
	Factory				tmp;
	eOperandType		type;
	IOperand const		*res;
	IOperand const		*two;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("avg");
	it = this->_stack.begin();
	res = (**(it + 1) + **it);
	type = res->getType();
	two = tmp.createOperand(type, "2.0");
	res = *res / *two;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::pow(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("pow");
	it = this->_stack.begin();
	res = (**(it + 1)).op_pow(**it);
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::bit_and(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("and");
	it = this->_stack.begin();
	res = **(it + 1) & **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::bit_or(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("or");
	it = this->_stack.begin();
	res = **(it + 1) | **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::bit_xor(void)
{
	std::vector<IOperand const *>::iterator	it;
	IOperand const		*res;

	if (this->_stack.size() < 2)
		throw NotEnoughElementException("xor");
	it = this->_stack.begin();
	res = **(it + 1) ^ **it;
	this->pop();
	this->pop();
	this->_stack.insert(this->_stack.begin(), res);
}

void					AbstractVm::print(void)
{
	if (this->_stack.size() == 0)
		throw EmptyStackException("print");
	std::vector<IOperand const *>::iterator	it;

	it = this->_stack.begin();
	if ((**it).getType() != Int8)
		throw AssertException("assert error for print : wrong type");

	int				tmp = std::stoi((**it).toString());
	int8_t			v;

	v = static_cast<int8_t>(tmp);
	std::cout << v;
}

AbstractVm::EmptyStackException::EmptyStackException(void) : std::runtime_error("")
{
	this->_message = "";
}

AbstractVm::EmptyStackException::EmptyStackException(std::string message) : std::runtime_error(message)
{
	this->_message = message;
}

AbstractVm::EmptyStackException::EmptyStackException(EmptyStackException const &src) : std::runtime_error(src._message)
{
    *this = src;
}

AbstractVm::EmptyStackException::~EmptyStackException(void) throw()
{
}

AbstractVm::EmptyStackException&          AbstractVm::EmptyStackException::operator=(EmptyStackException const &rhs)
{
    (void) rhs;
    return *this;
}

const char*                                 AbstractVm::EmptyStackException::what() const throw()
{
	std::string								error;

	if (this->_message.size() > 0)
		error = this->_message + ": the stack is empty";
	else
		error = "The stack is empty";
    return (error.c_str());
}

AbstractVm::NotEnoughElementException::NotEnoughElementException(void) : std::runtime_error("")
{
	this->_message = "";
}

AbstractVm::NotEnoughElementException::NotEnoughElementException(std::string message) : std::runtime_error(message)
{
	this->_message = message;
}

AbstractVm::NotEnoughElementException::NotEnoughElementException(NotEnoughElementException const &src) : std::runtime_error(src._message)
{
    *this = src;
}

AbstractVm::NotEnoughElementException::~NotEnoughElementException(void) throw()
{
}

AbstractVm::NotEnoughElementException&          AbstractVm::NotEnoughElementException::operator=(NotEnoughElementException const &rhs)
{
    (void) rhs;
    return *this;
}

const char*                                 AbstractVm::NotEnoughElementException::what() const throw()
{
	std::string								error;

	if (this->_message.size() > 0)
		error = this->_message + ": the stack has less than 2 element";
	else
		error = "The stack has less than 2 element";
    return (error.c_str());
}

AbstractVm::AssertException::AssertException(void) : std::runtime_error("Assert error")
{
	this->_message = "Assert error";
}

AbstractVm::AssertException::AssertException(std::string const &message) : std::runtime_error(message)
{
	this->_message = message;
}

AbstractVm::AssertException::AssertException(AssertException const &src) : std::runtime_error(src._message)
{
    *this = src;
}

AbstractVm::AssertException::~AssertException(void) throw()
{
}

AbstractVm::AssertException&          AbstractVm::AssertException::operator=(AssertException const &rhs)
{
    (void) rhs;
    return *this;
}

const char*                                 AbstractVm::AssertException::what() const throw()
{
    return (this->_message.c_str());
}