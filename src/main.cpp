/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 10:52:45 by jfourne           #+#    #+#             */
/*   Updated: 2019/06/03 09:40:59 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AbstractVm.class.hpp"
#include "LexerParser.class.hpp"
#include "avm.hpp"

int				main(int ac, char **av)
{
	int			ret = EXIT_FAILURE;
	LexerParser	avm_lexer_parser;

	if (ac == 1)
		ret = avm_lexer_parser.read_from_stdin();
	else if (ac == 2)
		ret = avm_lexer_parser.read_from_file(av[1]);
	else
	{
		std::cerr << "avm can only read from standard input with 0 argument"
		<< " or with 1 argument to read from a file" << std::endl;
	}
	return (ret);
}
