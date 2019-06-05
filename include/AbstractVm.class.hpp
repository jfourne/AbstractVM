/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AbstractVm.class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 10:06:50 by jfourne           #+#    #+#             */
/*   Updated: 2019/05/31 13:34:20 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACTVM_CLASS_HPP
# define ABSTRACTVM_CLASS_HPP

#include <vector>
#include <map>
#include "Operand.template.hpp"
#include "Factory.class.hpp"
# define ANSI_COLOR_RED     "\x1b[31m"  // Int8
# define ANSI_COLOR_GREEN   "\x1b[32m"  // Int16
# define ANSI_COLOR_YELLOW  "\x1b[33m"  // Int32
# define ANSI_COLOR_MAGENTA "\x1b[35m"  // Float
# define ANSI_COLOR_CYAN    "\x1b[36m"  // Double
# define ANSI_COLOR_RESET   "\x1b[0m"

class			AbstractVm
{
	public:
		class           EmptyStackException: public std::runtime_error
        {
        public:
            EmptyStackException(void);
            EmptyStackException(std::string message);
            EmptyStackException(EmptyStackException const &src);
            ~EmptyStackException(void) throw();

            EmptyStackException&      operator=(EmptyStackException const &rhs);

            virtual const char*         what() const throw();

        private:
            std::string         _message;
        };
		class           NotEnoughElementException: public std::runtime_error
        {
        public:
            NotEnoughElementException(void);
            NotEnoughElementException(std::string message);
            NotEnoughElementException(NotEnoughElementException const &src);
            ~NotEnoughElementException(void) throw();

            NotEnoughElementException&      operator=(NotEnoughElementException const &rhs);

            virtual const char*         what() const throw();

        private:
            std::string         _message;
        };
       	class           AssertException: public std::runtime_error
        {
        public:
            AssertException(void);
            AssertException(std::string const &message);
            AssertException(AssertException const &src);
            ~AssertException(void) throw();

            AssertException&		operator=(AssertException const &rhs);

            virtual const char*     what() const throw();
		private:
			std::string				_message;
        };
		AbstractVm(void);
		AbstractVm(AbstractVm const &src);
		~AbstractVm(void);

		AbstractVm&		operator=(AbstractVm const &rhs);

		void			push(eOperandType type, std::string &value);
		void			dump(void);
        void            assert(eOperandType type, std::string &value);
		void			pop(void);
        void            add(void);
        void            sub(void);
        void            mul(void);
        void            div(void);
        void            mod(void);
        void            max(void);
        void            min(void);
        void            avg(void);
        void            pow(void);
        void            bit_and(void);
        void            bit_or(void);
        void            bit_xor(void);
		void			print(void);

	private:
        void            setColor(eOperandType type);
		std::vector<IOperand const *>	_stack;
};

#endif