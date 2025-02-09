/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edegraev <edegraev@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:54:21 by edegraev          #+#    #+#             */
/*   Updated: 2024/12/27 13:42:33 by edegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/stat.h> 
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

class Lib {

	private:
		Lib(void);
		Lib(Lib const &src);
		Lib &operator=(Lib const &rhs);

	public:
		~Lib();

		static int stoi(std::string str);
		static float stof(std::string str);
		static double stod(std::string str);
		static unsigned long stoul(std::string str);
		static std::string to_string(int n);
		static bool isDirectory(const std::string& path);
		static bool isIndexPresent(const std::string& path);
		static std::string readFile(const std::string &filename);
		static bool fileExists(const std::string &filename);
		static void trim(std::string& str);
		static bool parseHost(std::string& value);
		static bool isUnit(char u);
		static int parsePort(std::string value);
		static bool isMainOptionKey(std::string key);
		static bool isFile(const std::string& name);
		static std::string getDirectory(const std::string& url);
};
