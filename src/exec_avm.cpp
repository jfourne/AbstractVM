/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_avm.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 12:18:24 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/21 15:01:12 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avm.hpp"
#include "AbstractVm.class.hpp"

void				browse_cmd_tab(std::vector<t_cmd>::iterator &it,
									bool &found, AbstractVm &vm, bool &cmd_exit)
{
	std::map<std::string, void (AbstractVm::*)(void)>			avm_cmd;
	std::map<std::string, void (AbstractVm::*)(void)>::iterator	it_avm_cmd;
	void							(AbstractVm::*tmp_func_ptr)(void);


	avm_cmd["dump"] = &AbstractVm::dump;
	avm_cmd["pop"] = &AbstractVm::pop;
	avm_cmd["add"] = &AbstractVm::add;
	avm_cmd["sub"] = &AbstractVm::sub;
	avm_cmd["mul"] = &AbstractVm::mul;
	avm_cmd["div"] = &AbstractVm::div;
	avm_cmd["mod"] = &AbstractVm::mod;
	avm_cmd["max"] = &AbstractVm::max;
	avm_cmd["min"] = &AbstractVm::min;
	avm_cmd["avg"] = &AbstractVm::avg;
	avm_cmd["pow"] = &AbstractVm::pow;
	avm_cmd["and"] = &AbstractVm::bit_and;
	avm_cmd["or"] = &AbstractVm::bit_or;
	avm_cmd["xor"] = &AbstractVm::bit_xor;
	avm_cmd["print"] = &AbstractVm::print;
	it_avm_cmd = avm_cmd.begin();
	while (it_avm_cmd != avm_cmd.end())
	{
		if ((*it).name.compare("exit") == 0)
		{
			cmd_exit = true;
			return ;
		}
		if ((*it).name.compare(it_avm_cmd->first) == 0)
		{
			tmp_func_ptr = it_avm_cmd->second;
			(vm.*tmp_func_ptr)();
			found = true;
		}
		it_avm_cmd++;
	}
}

void				browse_cmd_param_tab(std::vector<t_cmd>::iterator &it,
										bool &found, AbstractVm &vm)
{
	std::map<std::string, void (AbstractVm::*)(eOperandType type, std::string &value)>				avm_cmd_param;
	std::map<std::string, void (AbstractVm::*)(eOperandType type, std::string &value)>::iterator	it_avm_cmd_param;
	void			(AbstractVm::*tmp_param_func_ptr)(eOperandType type, std::string &value);

	avm_cmd_param["push"] = &AbstractVm::push;
	avm_cmd_param["assert"] = &AbstractVm::assert;
	it_avm_cmd_param = avm_cmd_param.begin();
	while (it_avm_cmd_param != avm_cmd_param.end())
	{
		if ((*it).name.compare(it_avm_cmd_param->first) == 0)
		{
			tmp_param_func_ptr = it_avm_cmd_param->second;
			(vm.*tmp_param_func_ptr)((*it).type, (*it).value);
			found = true;
		}
		it_avm_cmd_param++;
	}
}

int					exec_avm(std::vector<t_cmd> &cmd_list)
{
	bool							found;
	bool							cmd_exit = false;
	AbstractVm						vm;
	std::vector<t_cmd>::iterator	it;

	try
	{
		it = cmd_list.begin();
		while (it != cmd_list.end() && cmd_exit == false)
		{
			found = false;
			browse_cmd_tab(it, found, vm, cmd_exit);
			if (cmd_exit == false)
				browse_cmd_param_tab(it, found, vm);
			it++;
		}
		return (EXIT_SUCCESS);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (EXIT_FAILURE);
	}
}