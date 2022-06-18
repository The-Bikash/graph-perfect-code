#pragma once

#include <iostream>
#include <cstdlib>
#include <random>
#include <dynamic_array.hpp>

using uint = unsigned int;
using int64 = long long;

class graph
{

private:

	dynamic_array<dynamic_array<int64>> aL;

	dynamic_array<std::pair<int64, int64>> eL;

public:
	graph() {};

	graph(const dynamic_array<dynamic_array<int64>>& AdjacencyList)noexcept :aL(AdjacencyList)
	{
		int64 index = 0;
		for (const auto& a : aL)
		{
			for (const auto& v : a)
				if (v > index)
					eL.emplace_back(index, v);
			++index;
		}
	};

	graph(const dynamic_array<int64>& graph_perfect_code)noexcept
	{
		int64 i, j, size = graph_perfect_code.size(); aL = size;

		std::random_device device;

		std::mt19937 rng(device());

		std::uniform_int_distribution<unsigned int> dist(0, 1); // distribution in range [start, end]

		bool allow;

		for (i = 0; i < size; ++i)
		{
			for (j = i; j < size; ++j)
			{
				/*if (size <= 100)
				{
					allow = static_cast<bool>(dist(rng));
				}
				else if (size > 100 && size <= 200)
				{
					allow = static_cast<bool>(dist(rng) * dist(rng));
				}
				else if (size > 200 && size <= 300)
				{
					allow = static_cast<bool>(dist(rng) * dist(rng) * dist(rng));
				}
				else if (size > 300 && size <= 400)
				{
					allow = static_cast<bool>(dist(rng) * dist(rng) * dist(rng) * dist(rng));
				}
				else if (size > 400 && size <= 500)
				{
					allow = static_cast<bool>(dist(rng) * dist(rng) * dist(rng) * dist(rng) * dist(rng));
				}
				else if (size > 500 && size <= 600)
				{
					allow = static_cast<bool>(dist(rng) * dist(rng) * dist(rng) * dist(rng) * dist(rng) * dist(rng));
				}
				else
				{
					allow = static_cast<bool>(dist(rng) * dist(rng) * dist(rng) * dist(rng) * dist(rng) * dist(rng));
				}*/

				aL[i].push_back(j);
				aL[j].push_back(i);
			}
		}

		int64 index = 0;

		for (const auto& a : aL)
		{
			for (const auto& v : a)
			{
				if (v > index)
				{
					eL.emplace_back(index, v);
				}
			}
			++index;
		}
	}

	graph(const graph& graph)noexcept
	{
		aL = graph.aL;
		eL = graph.eL;
	}

	graph(graph&& graph)noexcept
	{
		aL = std::move(graph.aL);
		eL = std::move(graph.eL);
	}

	graph& operator = (const graph& graph) noexcept
	{
		if (this != &graph)
		{
			aL = graph.aL;
			eL = graph.eL;
		}
		
		return *this;
	}

	graph& operator = (graph&& graph)noexcept
	{
		if (this != &graph)
		{
			aL = std::move(graph.aL);
			eL = std::move(graph.eL);
		}
		return *this;
	}

	dynamic_array<std::pair<int64, int64>> edge_list()const
	{
		return eL;
	}
	dynamic_array<dynamic_array<int64>> adj_list()const
	{
		return aL;
	}
	constexpr int64 vertex_count()const
	{
		return static_cast<int64>(aL.size());
	}

	constexpr int64 edge_count()const
	{
		return static_cast<int64>(eL.size());
	}

	void print()const 
	{
		int64 i = 0, j = 0, n = (int64)aL.size();
		std::vector<bool> a; a.resize(n);
		std::vector<std::vector<bool>> aM; aM.resize(n, a);
		for (const auto& L : aL) {
			for (const auto& v : L)
				aM[i][v] = 1;
			i++;
		}
		std::cout << "\n\nGraph : \n";
		for (i = 0; i < n; ++i) {
			std::cout << '\n' << '(';
			for (j = 0; j < n; ++j)
				std::cout << aM[i][j] << ' ';
			std::cout << ')';
		}
	}

};

const std::ostream& operator <<(const std::ostream& cout, const graph& g) {
	g.print(); return cout;
}

template<typename arr_type> std::ostream& operator <<(std::ostream& cout, std::vector<arr_type>& Container) {
	std::cout << std::endl; for (const auto& i : Container) std::cout << i << ' '; return cout;
}


template<class T1, class ...T2> void Print(T1 arg, T2 ...args) {
	std::cout << arg << " ";
	if constexpr (sizeof...(args) > 0) Print(args...);
}




