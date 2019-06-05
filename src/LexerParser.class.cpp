/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:03:24 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/21 14:55:18 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LexerParser.class.hpp"

LexerParser::LexerParser()
{
    this->_line_nb = 1;
    this->_cmd_exit = false;
}

LexerParser::LexerParser(LexerParser const &src)
{
    *this = src;
}

LexerParser::~LexerParser()
{
}

LexerParser&        LexerParser::operator=(LexerParser const &rhs)
{
    this->_error_list = rhs._error_list;
    this->_cmd_list = rhs._cmd_list;
    this->_line = rhs._line;
    this->_line_nb = rhs._line_nb;
    this->_cmd_exit = rhs._cmd_exit;
    return *this;
}

void                            LexerParser::print_error(void)
{
	std::vector<std::string>::iterator	it;

	it = this->_error_list.begin();
	while (it != this->_error_list.end())
	{
		std::cout << *it << std::endl;
		it++;
	}
}

int				                 LexerParser::read_from_file(char *file)
{
	std::ifstream				ifs;

	ifs.open(file);
	if (ifs.is_open())
	{
		while (std::getline(ifs, this->_line))
		{
			this->parse_line();
			this->_line_nb++;
		}
		if (this->_cmd_exit == false)
			this->_error_list.push_back("No exit instruction found");
		else if (this->_cmd_list.size() > 0 && this->_error_list.size() == 0)
			return (exec_avm(this->_cmd_list));
		else if (this->_cmd_list.size() == 0)
			std::cerr << "Command list is empty" << std::endl;
		if (this->_error_list.size() > 0)
			this->print_error();
	}
	else
		std::cerr << "Error opening file : " << file << std::endl;
	return (EXIT_FAILURE);
}

int				                LexerParser::read_lines(std::vector<std::string> &lines)
{
	std::regex					end("^(;;)\\s*(\\;.*)?$");
	std::string					line;

	while (std::regex_match(line, end) == false)
	{
		std::getline(std::cin, line);
		if (std::cin.eof())
			return (EXIT_FAILURE);
		lines.push_back(line);
	}
	return (EXIT_SUCCESS);
}

int				                LexerParser::read_from_stdin(void)
{
	std::vector<std::string>			lines;
	std::vector<std::string>::iterator	it;

	if (read_lines(lines) == EXIT_FAILURE)
		this->_error_list.push_back("Input have to end with ';;'");
	if (lines.size() > 0)
	{
		it = lines.begin();
		while (it != lines.end())
		{
			this->_line = *it;
			this->parse_line();
			this->_line_nb++;
			it++;
		}
		if (this->_cmd_exit == false)
			this->_error_list.push_back("No exit instruction found");
		else if (this->_cmd_list.size() > 0 && this->_error_list.size() == 0)
			return (exec_avm(this->_cmd_list));
		else if (this->_cmd_list.size() == 0)
			std::cerr << "Command list is empty" << std::endl;
	}
	if (this->_error_list.size() > 0)
		this->print_error();
	return (EXIT_FAILURE);
}

eOperandType		LexerParser::convert_type_str(std::smatch &match)
{
	std::map<std::string, eOperandType>				type_str;
	std::map<std::string, eOperandType>::iterator	it;

	type_str["int8"] = Int8;
	type_str["int16"] = Int16;
	type_str["int32"] = Int32;
	type_str["float"] = Float;
	type_str["double"] = Double;
	it = type_str.begin();
	while (it != type_str.end())
	{
		if (it->first.compare(match[0]) == 0)
			return (it->second);
		it++;
	}
	return (Double);
}

void				LexerParser::search_avm_cmd_param(void)
{
	t_cmd			tmp;
	std::smatch		match;
	std::regex		name_cmd_param("^(push|assert)");
	std::regex		cmd_type("(float|double|int8|int16|int32)");
	std::regex		cmd_value("\\(-?[0-9]+(\\.[0-9]+)?\\)");

	std::regex_search(this->_line, match, name_cmd_param);
	tmp.name = match[0];
	std::regex_search(this->_line, match, cmd_type);
	tmp.type = convert_type_str(match);
	std::regex_search(this->_line, match, cmd_value);
	tmp.value = match[0];
	tmp.value = tmp.value.substr(1, tmp.value.size() - 2);
	this->_cmd_list.push_back(tmp);
}

void				LexerParser::search_avm_cmd(void)
{
	t_cmd			tmp;
	std::smatch		match;
	std::regex		name_cmd("^(dump|pop|add|sub|mul|div|mod|print|max|min|avg|pow|and|or|xor|exit)");

	std::regex_search(this->_line, match, name_cmd);
	tmp.name = match[0];
	if (tmp.name.compare("exit") == 0)
		this->_cmd_exit = true;
	tmp.type = Int8;
	tmp.value = "0";
	this->_cmd_list.push_back(tmp);
}

void				LexerParser::parse_line(void)
{
	std::smatch		match;
	std::regex		check_cmd("^(dump|pop|add|sub|mul|div|mod|print|exit|push|assert|max|min|avg|pow|and|or|xor)\\s*");
	std::regex		avm_cmd("^(dump|pop|add|sub|mul|div|mod|print|max|min|avg|pow|and|or|xor|exit)\\s*(\\;.*)?$");
	std::regex		avm_cmd_param("^(push|assert)\\s+((float|double)\\(-?[0-9]+\\.[0-9]+\\)|(int8|int16|int32)\\(-?[0-9]+\\))\\s*(\\;.*)?$");

	if (std::regex_match(this->_line, avm_cmd))
		this->search_avm_cmd();
	else if (std::regex_match(this->_line, avm_cmd_param))
		this->search_avm_cmd_param();
	else if (std::regex_match(this->_line, std::regex("^(;){1}.*")) || this->_line.size() == 0)
		return ;
	else if (std::regex_search(this->_line, match, check_cmd) == false)
	{
		this->_error_list.push_back("Unknown command in line " + std::to_string(this->_line_nb) + " : " + this->_line);
		return ;
	}
	else
		this->_error_list.push_back("Error in line " + std::to_string(this->_line_nb) + " : " + this->_line);
}