/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:34:25 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/20 16:32:37 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_CLASS_HPP
# define LEXERPARSER_CLASS_HPP

#include "avm.hpp"

class			LexerParser
{
	public:
		LexerParser();
		LexerParser(LexerParser const &src);
		~LexerParser();

		LexerParser&				operator=(LexerParser const &rhs);

		int							read_from_file(char *file);
		int							read_from_stdin(void);


	private:
		void						parse_line(void);
		void						print_error(void);
		int							read_lines(std::vector<std::string> &lines);
		eOperandType				convert_type_str(std::smatch &match);
		void						search_avm_cmd_param(void);
		void						search_avm_cmd(void);
		std::vector<std::string>	_error_list;
		std::vector<t_cmd>			_cmd_list;
		std::string					_line;
		int							_line_nb;
		bool						_cmd_exit;
};

#endif