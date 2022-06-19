#pragma once

#include <iostream>
#include <cstdlib>
#include <random>
#include <dynamic_array.hpp>

using uint = unsigned int;
using int64 = long long;

dynamic_array<dynamic_array<int64>> my_partition(dynamic_array<int64>& set, const int64& size)
{
	dynamic_array<dynamic_array<int64>> Tmp(size);

	set.shuffle();
	
	if (set.size() != size * 4)
	{
		throw("Error");
	}

	for (int64 i = 0; i < size; ++i)
	{
		for (int64 j = 0; j < 4; ++j)
		{
			Tmp[i].push_back(set[i * 4 + j]);
		}
	}

	return Tmp;
}

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
		int64 vertexCount = 5 * graph_perfect_code.size();

		std::cout << graph_perfect_code << "\n\n";

		int64 size = graph_perfect_code.size(); aL = vertexCount;

		dynamic_array<bool> available(vertexCount,true);

		for (int64 i = 0; i < size; ++i)
		{
			available[graph_perfect_code[i]] = false;
		}

		dynamic_array<int64> set; set.reserve(vertexCount - size);

		for (int64 i = 0; i < vertexCount; ++i)
		{
			if (available[i])
			{
				set.push_back(i);
			}
		}

		std::cout << set.size()<<" "<< size;

		dynamic_array<dynamic_array<int64>> partition = my_partition(set, size);

		set.shuffle();

		for (int64 i = 0; i < size; ++i)
		{
			aL[graph_perfect_code[i]].push_back(graph_perfect_code[i]);

			for (const auto& e : partition[i])
			{
				aL[graph_perfect_code[i]].push_back(e);

				aL[e].push_back(graph_perfect_code[i]);
			}
		}

		for (int64 i = 0; i < set.size(); ++i)
		{
			aL[set[i]].push_back(set[i]);

			for (int64 j = 1; j < 4; ++j)
			{
				if (aL[set[i]].size() > 4) break;

				aL[set[i]].push_back(set[(i + j) % set.size()]);

				aL[set[(i + j) % set.size()]].push_back(set[i]);
			}

		}

		//std::cout << aL;

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
		dynamic_array<bool> a(n,false);
		dynamic_array<dynamic_array<bool>> aM(n, a);
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




