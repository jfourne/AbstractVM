/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:20:10 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/13 14:45:58 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_CLASS_HPP
# define FACTORY_CLASS_HPP

#include "IOperand.class.hpp"

class		Factory
{
	public:
       	class           UnderflowException: public std::exception
        {
        public:
            UnderflowException(void);
            UnderflowException(std::string const &message);
            UnderflowException(UnderflowException const &src);
            ~UnderflowException(void) throw();

            UnderflowException&		operator=(UnderflowException const &rhs);

            virtual const char*     what() const throw();
		private:
			std::string				_message;
        };
       	class           OverflowException: public std::exception
        {
        public:
            OverflowException(void);
            OverflowException(std::string const &message);
            OverflowException(OverflowException const &src);
            ~OverflowException(void) throw();

            OverflowException&		operator=(OverflowException const &rhs);

            virtual const char*     what() const throw();
		private:
			std::string				_message;
        };	
		Factory(void);
		Factory(Factory const &src);
		Factory&		operator=(Factory const &rhs);
		~Factory(void);

		IOperand const	*createOperand(eOperandType type, std::string const &value) const;

	private:
		void			create_func_ptr(void);
		IOperand const	*createInt8(std::string const &value) const;
		IOperand const	*createInt16(std::string const &value) const;
		IOperand const	*createInt32(std::string const &value) const;
		IOperand const	*createFloat(std::string const &value) const;
		IOperand const	*createDouble(std::string const &value) const;
		IOperand const	*(Factory::*_f[5])(std::string const &value) const;
};

#endif