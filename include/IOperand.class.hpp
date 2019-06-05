/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 13:44:54 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/21 14:48:07 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_CLASS_HPP
# define IOPERAND_CLASS_HPP

#include <iostream>

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
	public:
		virtual int					getPrecision( void ) const = 0; // Precision of the type of the instance
		virtual eOperandType		getType( void ) const = 0; // Type of the instance
		virtual IOperand const		*operator+( IOperand const & rhs ) const = 0; // Sum
		virtual IOperand const		*operator-( IOperand const & rhs ) const = 0; // Difference
		virtual IOperand const		*operator*( IOperand const & rhs ) const = 0; // Product
		virtual IOperand const		*operator/( IOperand const & rhs ) const = 0; // Quotient
		virtual IOperand const		*operator%( IOperand const & rhs ) const = 0; // Modulo
		virtual IOperand const		*operator>( IOperand const & rhs ) const = 0; // Max
		virtual IOperand const		*operator<( IOperand const & rhs ) const = 0; // Min
		virtual IOperand const		*operator&( IOperand const & rhs ) const = 0; // And
		virtual IOperand const		*operator|( IOperand const & rhs ) const = 0; // Or
		virtual IOperand const		*operator^( IOperand const & rhs ) const = 0; // Xor
		virtual IOperand const		*op_pow( IOperand const & rhs ) const = 0; // Pow
		virtual std::string const 	&toString( void ) const = 0; // String representation of the instance
		virtual ~IOperand( void ) {}
};

#endif