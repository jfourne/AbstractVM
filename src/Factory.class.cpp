/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:32:17 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/31 16:49:44 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.class.hpp" 
#include "Operand.template.hpp"

Factory::Factory(void)
{
	create_func_ptr();
}

Factory::Factory(Factory const &src)
{
	*this = src;
}

Factory::~Factory(void)
{
}

Factory&			Factory::operator=(Factory const &rhs)
{
	this->create_func_ptr();
	(void) rhs;
	return *this;
}

void				Factory::create_func_ptr(void)
{
	this->_f[Int8] = &Factory::createInt8;
	this->_f[Int16] = &Factory::createInt16;
	this->_f[Int32] = &Factory::createInt32;
	this->_f[Float] = &Factory::createFloat;
	this->_f[Double] = &Factory::createDouble;
}

IOperand const		*Factory::createOperand(eOperandType type, std::string const &value) const
{
	return (this->*_f[type])(value);
}

IOperand const		*Factory::createInt8(std::string const &value) const
{
	try
	{
		int				tmp = std::stoi(value);
		int8_t			v;

		if (tmp < INT8_MIN)
			throw UnderflowException("int8 : underflow error");
		else if (tmp > INT8_MAX)
			throw OverflowException("int8 : overflow error");
		v = static_cast<int8_t>(tmp);
		IOperand				*int8 = new Operand<int8_t>(Int8, v, value);
		
		return (int8);
	}
	catch (std::out_of_range &e)
	{
		if (value.find("-") == std::string::npos)
			throw OverflowException("int8 : overflow error");
		else
			throw UnderflowException("int8 : underflow error");
	}
}

IOperand const		*Factory::createInt16(std::string const &value) const
{
	try
	{
		int				tmp = std::stoi(value);
		int16_t			v;

		if (tmp < INT16_MIN)
			throw UnderflowException("int16 : underflow error");
		else if (tmp > INT16_MAX)
			throw OverflowException("int16 : overflow error");
		v = static_cast<int16_t>(tmp);

		IOperand		*int16 = new Operand<int16_t>(Int16, v, value);

		return (int16);
	}
	catch (std::out_of_range &e)
	{
		if (value.find("-") == std::string::npos)
			throw OverflowException("int16 : overflow error");
		else
			throw UnderflowException("int16 : underflow error");
	}
}

IOperand const		*Factory::createInt32(std::string const &value) const
{
	try
	{
		int32_t			v = std::stoi(value);
		IOperand		*int32 = new Operand<int32_t>(Int32, v, value);

		return (int32);
	}
	catch (std::out_of_range &e)
	{
		if (value.find("-") == std::string::npos)
			throw OverflowException("int32 : overflow error");
		else
			throw UnderflowException("int32 : underflow error");
	}
}

IOperand const		*Factory::createFloat(std::string const &value) const
{
	try
	{
		float			v = std::stof(value);
		IOperand		*my_float = new Operand<float>(Float, v, value);

		return (my_float);
	}
	catch (std::out_of_range &e)
	{
		if (value.find("-") == std::string::npos)
			throw OverflowException("float : overflow error");
		else
			throw UnderflowException("float : underflow error");
	}
}

IOperand const		*Factory::createDouble(std::string const &value) const
{
	try
	{
		double			v = std::stod(value);
		IOperand		*my_double = new Operand<double>(Double, v, value);

		return (my_double);
	}
	catch (std::out_of_range &e)
	{
		if (value.find("-") == std::string::npos)
			throw OverflowException("double : overflow error");
		else
			throw UnderflowException("double : underflow error");
	}
}

Factory::UnderflowException::UnderflowException(void) : std::exception()
{
	this->_message = "Underflow error";
}

Factory::UnderflowException::UnderflowException(std::string const &message) : std::exception()
{
	this->_message = message;
}

Factory::UnderflowException::UnderflowException(UnderflowException const &src) : std::exception()
{
    *this = src;
}

Factory::UnderflowException::~UnderflowException(void) throw()
{
}

Factory::UnderflowException&          Factory::UnderflowException::operator=(UnderflowException const &rhs)
{
    (void) rhs;
    return *this;
}

const char*                                 Factory::UnderflowException::what() const throw()
{
    return (this->_message.c_str());
}

Factory::OverflowException::OverflowException(void) : std::exception()
{
	this->_message = "Overflow error";
}

Factory::OverflowException::OverflowException(std::string const &message) : std::exception()
{
	this->_message = message;
}

Factory::OverflowException::OverflowException(OverflowException const &src) : std::exception()
{
    *this = src;
}

Factory::OverflowException::~OverflowException(void) throw()
{
}

Factory::OverflowException&          Factory::OverflowException::operator=(OverflowException const &rhs)
{
    (void) rhs;
    return *this;
}

const char*                                 Factory::OverflowException::what() const throw()
{
    return (this->_message.c_str());
}