/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.template.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 15:53:27 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/31 16:48:10 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_CLASS_HPP
# define OPERAND_CLASS_HPP

#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
#include "Factory.class.hpp"

template<class T>
class		Operand: public IOperand
{
	public:
		class           DivisionByZeroException: public std::exception
        {
        public:
            DivisionByZeroException(void) {}
            DivisionByZeroException(DivisionByZeroException const &src) {*this = src;}
            ~DivisionByZeroException(void) throw() {}

            DivisionByZeroException&      operator=(DivisionByZeroException const &rhs)
			{
				(void) rhs;
				return *this;
			}

            virtual const char*         what() const throw() {return "divisor is equal to 0";}
        };
		class           BitwiseOpException: public std::exception
		{
        public:
            BitwiseOpException(void) {
				this->_message = "Bitwise operator error";
			}
            BitwiseOpException(std::string message) {
				this->_message = message;
			}
            BitwiseOpException(BitwiseOpException const &src) {*this = src;}
            ~BitwiseOpException(void) throw() {}

            BitwiseOpException&      operator=(BitwiseOpException const &rhs)
			{
				(void) rhs;
				return *this;
			}

            virtual const char*         what() const throw() {return this->_message.c_str();}

		private:
			std::string					_message;
        };
		Operand(void): _type(Int8), _v(0)
		{
			this->_str_v = "0";
		}
		Operand(const eOperandType &type, T v, std::string str_v): _type(type), _v(v)
		{
			this->_str_v = str_v;
		}
		Operand(Operand const &src)
		{
			*this = src;
		}
		Operand&					operator=(Operand const &rhs)
		{
			this->_type = rhs._type;
			this->_v = rhs->_v;
			this->_str_v = rhs._str_v;
		}
		virtual ~Operand(void) {}


		virtual IOperand const		*op_pow( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << pow(this->_v, other);
			std::string				str_value = stream.str();
			if (str_value.compare("inf") == 0 || str_value.compare("nan") == 0)
				throw std::out_of_range("result after pow has overflow");
			if (str_value.compare("-inf") == 0 || str_value.compare("-nan") == 0)
				throw std::out_of_range("result after pow has underflow");
			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator+(IOperand const & rhs) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (this->getType() > rhs.getType())
				type = this->getType();
			else
				type = rhs.getType();


			std::stringstream		stream;

			stream << this->_v + other;
			std::string				str_value = stream.str();

			if (str_value.compare("inf") == 0 || str_value.compare("nan") == 0)
				throw std::out_of_range("result after + has overflow");
			if (str_value.compare("-inf") == 0 || str_value.compare("-nan") == 0)
				throw std::out_of_range("result after + has underflow");
			return tmp.createOperand(type, str_value);
		}
		virtual IOperand const		*operator-( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << this->_v - other;
			std::string				str_value = stream.str();

			if (str_value.compare("inf") == 0 || str_value.compare("nan") == 0)
				throw std::out_of_range("result after - has overflow");
			if (str_value.compare("-inf") == 0 || str_value.compare("-nan") == 0)
				throw std::out_of_range("result after - has underflow");
			return tmp.createOperand(type, str_value);
		}
		virtual IOperand const		*operator*( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << this->_v * other;
			std::string				str_value = stream.str();

			if (str_value.compare("inf") == 0 || str_value.compare("nan") == 0)
				throw std::out_of_range("result after * has overflow");
			if (str_value.compare("-inf") == 0 || str_value.compare("-nan") == 0)
				throw std::out_of_range("result after * has underflow");
			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator/( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (other == 0)
				throw DivisionByZeroException();
			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << this->_v / other;
			std::string				str_value = stream.str();

			if (str_value.compare("inf") == 0 || str_value.compare("nan") == 0)
				throw std::out_of_range("result after / has overflow");
			if (str_value.compare("-inf") == 0 || str_value.compare("-nan") == 0)
				throw std::out_of_range("result after / has underflow");
			return tmp.createOperand(type, str_value);
		}
		virtual IOperand const		*operator%( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					other = std::stod(rhs.toString());

			if (other == 0)
				throw DivisionByZeroException();
			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << fmod(this->_v, other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator>( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					curr = std::stod(this->toString());
			double					other = std::stod(rhs.toString());

			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << (curr > other ? curr : other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator<( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			double					curr = std::stod(this->toString());
			double					other = std::stod(rhs.toString());

			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			std::stringstream		stream;

			stream << (curr < other ? curr : other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator&( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			int						other = std::stod(rhs.toString());

			if (this->getType() == Float || rhs.getType() == Float ||
				this->getType() == Double || rhs.getType() == Double)
				throw BitwiseOpException("Bitwise operator & cannot be applied to double or float");
			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			int						curr = static_cast<int>(this->_v);
			std::stringstream		stream;

			stream << (curr & other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator|( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			int						other = std::stod(rhs.toString());

			if (this->getType() == Float || rhs.getType() == Float ||
				this->getType() == Double || rhs.getType() == Double)
				throw BitwiseOpException("Bitwise operator | cannot be applied to double or float");
			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			int						curr = static_cast<int>(this->_v);
			std::stringstream		stream;

			stream << (curr | other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual IOperand const		*operator^( IOperand const & rhs ) const
		{
			Factory					tmp;
			eOperandType			type;
			int						other = std::stod(rhs.toString());

			if (this->getType() == Float || rhs.getType() == Float ||
				this->getType() == Double || rhs.getType() == Double)
				throw BitwiseOpException("Bitwise operator ^ cannot be applied to double or float");
			if (this->getPrecision() > rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();

			int						curr = static_cast<int>(this->_v);
			std::stringstream		stream;

			stream << (curr ^ other);
			std::string				str_value = stream.str();

			return tmp.createOperand(type, str_value);
		}

		virtual int					getPrecision( void ) const
		{
			return this->_type;
		}
		virtual eOperandType		getType( void ) const
		{
			return this->_type;
		}
		virtual std::string const 	&toString( void ) const
		{
			return (this->_str_v);
		}
	private:
		const eOperandType			_type;
		T							_v;
		std::string					_str_v;
};

#endif