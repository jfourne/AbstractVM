/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <jfourne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 11:26:41 by jfourne           #+#    #+#             */
/*   Updated: 2019/02/20 16:58:02 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVM_HPP
# define AVM_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>
#include "IOperand.class.hpp"
#include "AbstractVm.class.hpp"

typedef struct		s_cmd
{
	std::string		name;
	eOperandType	type;
	std::string		value;
}					t_cmd;

int			exec_avm(std::vector<t_cmd> &cmd_list);

#endif