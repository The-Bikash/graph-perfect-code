#pragma once

#include <string>
#include <graph.hpp>
#include <algorithm>
#include <integer.hpp>
#include <polynomial.hpp>
#include <dynamic_array.hpp>

int64 vertexCount = 5*10ll;

dynamic_array<integer> solution(const dynamic_array<int64>& private_key)
{
	int64 i = 0, j = 0;

	dynamic_array<integer> private_sol(vertexCount, 0ll);

	integer* private_sol_ptr = private_sol.data();

	//const int64* private_key_ptr = private_key.data();

	for (const auto& v : private_key)
	{
		*(private_sol_ptr + v) = 1ll;
	}

	return private_sol;
}

class Person
{

private:

	dynamic_array<int64> _private_key;

	dynamic_array<integer> _private_sol;

	graph _public_key;

public:

	Person()
	{
		_private_key = random_distinct_int(0, vertexCount-1, vertexCount / 5);
		_private_sol = solution(_private_key);
		_public_key = _private_key;

		/*_private_key = random_int(1, 3, N);
		_private_sol = solution(_private_key);*/
	}

	graph public_key()const
	{
		return _public_key;
	}
	void private_key()const
	{
		std::cout << "(Graph perfect code) : \n " << _private_key;
	}

	std::string message(polynomial<integer>& pol)const
	{
		dynamic_array<integer> private_sol = _private_sol;

		for (int64 i = _private_sol.size(); i < pol.var_list().size(); ++i)
		{
			private_sol.emplace_back(0ll);
		}

		integer messageNum = pol(private_sol);

		std::cout << "\n\nHi I am Alice . I have decrypted the cipher text. The message is : \n\n";

		return  ConvertIntegerToMessage(messageNum);
	}
};

void input(std::string& message)
{
	std::cout << "\n\nEnter a message : "; std::getline(std::cin, message);
}

dynamic_array<std::string> var_vec(int64 n)
{
	dynamic_array<std::string> var_list(n);

	for (int64 i = 0; i < n; ++i)
	{
		var_list[i] = 't' + std::to_string(i);
	}

	return var_list;
}
