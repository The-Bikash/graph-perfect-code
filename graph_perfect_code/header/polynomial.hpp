#pragma once

#include <list>
#include <string>
#include <utility>
#include <integer.hpp>
#include <dynamic_array.hpp>

using int64 = long long;

template<class field> class polynomial
{

private:

	struct node
	{
		field coeff;

		dynamic_array<int64> expo;
		
		constexpr void print()const
		{
			std::cout << "[" << coeff << ",(";

			for (const auto& i : expo)
			{
				std::cout << i << ' ';
			}

			std::cout << ")]";
		}

		[[nodiscard]] constexpr bool operator <  (const node& that)const noexcept
		{
			int64 n = expo.size();

			const int64* expo_ptr = this->expo.data();
			const int64* xexpo_ptr = that.expo.data();

			for (int64 i = 0; i < n; ++i)
			{
				if (*(expo_ptr + i) == *(xexpo_ptr + i)) continue;

				if (*(expo_ptr + i) > *(xexpo_ptr + i)) return true;

				return false;
			}

			return false;
		}

		[[nodiscard]] constexpr bool operator == (const node& x)const noexcept
		{
			int64 size = (int64)expo.size();

			if (size != x.expo.size())
			{
				return false;
			}

			const int64* expo_ptr = expo.data();
			const int64* xexpo_ptr = x.expo.data();

			for (int64 i = 0; i < size; ++i)
			{
				if (*(expo_ptr + i) != *(xexpo_ptr + i))
				{
					return false;
				}
			}

			return true;
		}

		[[nodiscard]] constexpr node operator +  (const node& x)const noexcept
		{
			return { coeff + x.coeff,expo }; // both pair's expo must be same
		}

		[[nodiscard]] constexpr node operator *  (const node& x)const noexcept
		{
			int64 size = expo.size(); node Tmp; Tmp.expo = size;

			const int64* expo_ptr = this->expo.data();
			const int64* xexpo_ptr = x.expo.data();

			int64* Tmpexpo_ptr = Tmp.expo.data();

			Tmp.coeff = this->coeff * x.coeff;

			for (int64 i = 0; i < size; ++i)
			{
				*(Tmpexpo_ptr + i) = *(expo_ptr + i) + *(xexpo_ptr + i);
			}

			return Tmp;
		}

		constexpr node& operator += (const node& x)noexcept
		{
			coeff += x.coeff;  // both pair's expo must be same

			return *this;
		}
	};

	dynamic_array<std::string> vL; // variable list

	std::list<node> fx; // polynomial list representation

public:

	constexpr polynomial()noexcept
	{

	}

	constexpr polynomial(const field& coeff, const dynamic_array<std::string>& vL)noexcept :vL(vL)
	{
		fx.emplace_back(coeff, dynamic_array<int64>(vL.size(), 0ll));
	}

	constexpr polynomial(const field& coeff, const dynamic_array<int64>& expo, const dynamic_array<std::string>& vL)noexcept :vL(vL)
	{
		fx.emplace_back(coeff, expo);
	}

	constexpr polynomial(const std::list<std::pair<field, dynamic_array<int64>>>& fx, const dynamic_array<std::string> vL)noexcept : vL(vL)
	{
		//for (const auto& pair_ : fx)
		//{
		//	if (pair_.second.size() != vL.size()) throw("ERROR");
		//}

		//std::set<std::string> TmpSet(vL.begin(), vL.end());

		//if (TmpSet.size() != vL.size())
		//{
		//	throw("ERROR");  // Searching duplicates Variable;
		//}
		
		this->vL = vL;

		for (const auto& pair_ : fx)
		{
			this->fx.emplace_back(pair_.first, pair_.second);
		}

		this->fx.sort();
	}

	constexpr polynomial(const polynomial& pol)noexcept
	{
		this->vL = pol.vL;
		this->fx = pol.fx;
	}

	constexpr polynomial(polynomial&& pol)noexcept
	{
		this->vL = std::move(pol.vL);
		this->fx = std::move(pol.fx);
	}

	constexpr polynomial& operator = (polynomial&& pol)noexcept
	{
		this->vL = std::move(pol.vL);
		this->fx = std::move(pol.fx);

		return *this;
	}

	constexpr field operator()(const dynamic_array<field>& x)const
	{

		if (x.size() != vL.size()) throw("ERROR");

		int64 n = fx.size(), m = x.size(), i = 0, j = 0;

		field sum = 0ll, Tmp = 1ll;

		static dynamic_array<std::pair<int64, field>> Tmpcatch;

		Tmpcatch = m;

		for (i = 0; i < m; ++i)
		{
			// reset Tmpcatch

			Tmpcatch[i].first = 0ll;

			Tmpcatch[i].second = 1ll; 
		}

		for (auto rit = fx.rbegin(); rit != fx.rend(); ++rit)
		{
			Tmp = 1ll;

			for (j = 0; j < m; ++j)
			{
				if (rit->expo[j] >= Tmpcatch[j].first)
				{
					Tmpcatch[j].second *= pow(x[j], rit->expo[j] - Tmpcatch[j].first);

					Tmpcatch[j].first = rit->expo[j];

					Tmp *= Tmpcatch[j].second;

					continue;
				}

				Tmp *= pow(x[j], rit->expo[j]);
			}

			sum += Tmp * rit->coeff;
		}

		return sum;
	}

	constexpr polynomial operator + (const polynomial& f)const noexcept
	{
		polynomial TmpPoly;

		if (f.vL == vL)
		{
			auto iterator1 = fx.begin();

			auto iterator2 = f.fx.begin();

			auto iterator1e = fx.end();

			auto iterator2e = f.fx.end();

			while (iterator1 != iterator1e && iterator2 != iterator2e)
			{
				if (*iterator1 == *iterator2)
				{
					TmpPoly.fx.emplace_back(*iterator1 + *iterator2);

					++iterator1;
					++iterator2;

					continue;
				}

				if (*iterator1 < *iterator2)
				{
					TmpPoly.fx.push_back(*iterator1);

					++iterator1;

					continue;
				}

				TmpPoly.fx.push_back(*iterator2);

				++iterator2;

			}

			while (iterator1 != iterator1e)
			{
				TmpPoly.fx.push_back(*iterator1);

				++iterator1;
			}

			while (iterator2 != iterator2e)
			{
				TmpPoly.fx.push_back(*iterator2);

				++iterator2;
			}

			TmpPoly.vL = vL;

			return TmpPoly;
		}

		polynomial P1 = *this, P2 = f;

		upgrade_poly(P1, P2);

		auto iterator1 = P1.fx.begin();

		auto iterator2 = P2.fx.begin();

		auto iterator1e = P1.fx.end();

		auto iterator2e = P2.fx.end();

		while (iterator1 != iterator1e && iterator2 != iterator2e)
		{
			if (*iterator1 == *iterator2)
			{
				TmpPoly.fx.emplace_back(*iterator1 + *iterator2);

				++iterator1;
				++iterator2;

				continue;
			}

			if (*iterator1 < *iterator2)
			{
				TmpPoly.fx.push_back(*iterator1);

				++iterator1;

				continue;
			}

			TmpPoly.fx.push_back(*iterator2);

			++iterator2;

		}

		while (iterator1 != iterator1e)
		{
			TmpPoly.fx.push_back(*iterator1);

			++iterator1;
		}

		while (iterator2 != iterator2e)
		{
			TmpPoly.fx.push_back(*iterator2);

			++iterator2;
		}

		TmpPoly.vL = P1.vL;

		return TmpPoly;

	}

	constexpr polynomial& operator += (const polynomial& f)noexcept {

		if (f.vL == vL)
		{
			auto iterator1 = fx.begin();

			auto iterator2 = f.fx.begin();

			while (iterator1 != fx.end() && iterator2 != f.fx.end())
			{

				if (*iterator1 == *iterator2)
				{
					*iterator1 += *iterator2;

					++iterator1;
					++iterator2;

					continue;
				}

				if (*iterator1 < *iterator2)
				{
					// Actually this is *ptr1 > *ptr2.

					++iterator1;

					continue;
				}

				iterator1 = fx.insert(iterator1, *iterator2);

				++iterator2;

			}

			while (iterator2 != f.fx.end())
			{
				fx.push_back(*iterator2);

				++iterator2;
			}

			return *this;
		}

		polynomial p2 = f;

		upgrade_poly(*this, p2);

		auto iterator1 = fx.begin();

		auto iterator2 = p2.fx.begin();

		while (iterator1 != fx.end() && iterator2 != p2.fx.end())
		{

			if (*iterator1 == *iterator2)
			{
				*iterator1 += *iterator2;

				++iterator1;
				++iterator2;

				continue;
			}

			if (*iterator1 < *iterator2)
			{
				// Actually this is *ptr1 > *ptr2.

				++iterator1;

				continue;
			}

			iterator1 = fx.insert(iterator1, *iterator2);

			++iterator2;

		}

		while (iterator2 != p2.fx.end())
		{
			fx.push_back(*iterator2);

			++iterator2;
		}

		return *this;
	}

	constexpr polynomial operator * (const polynomial& f)const
	{
		polynomial TmpPoly;

		if (f.vL == vL)
		{
			auto iterator1 = fx.begin();
			auto iterator2 = f.fx.begin();

			while (iterator1 != fx.end())
			{
				iterator2 = f.fx.begin();

				while (iterator2 != f.fx.end())
				{
					TmpPoly.fx.emplace_back(*iterator1 * *iterator2);

					++iterator2;
				}

				++iterator1;
			}

			TmpPoly.fx.sort();

			auto iteratorx = TmpPoly.fx.begin();
			auto iterator3 = ++TmpPoly.fx.begin();

			bool Delete = false;

			while (iterator3 != TmpPoly.fx.end())
			{
				if (*iteratorx == *iterator3)
				{
					Delete = true;

					*iteratorx += *iterator3;
				}
				else
				{
					++iteratorx;

					if (Delete)
					{
						iteratorx = TmpPoly.fx.erase(iteratorx, iterator3);

						Delete = false;
					}
				}

				++iterator3;
			}

			TmpPoly.vL = vL;

			return TmpPoly;

		}

		polynomial P1 = *this, P2 = f;

		upgrade_poly(P1, P2);

		auto iterator1 = P1.fx.begin();
		auto iterator2 = P2.fx.begin();

		while (iterator1 != P1.fx.end())
		{
			iterator2 = P2.fx.begin();

			while (iterator2 != P2.fx.end())
			{
				TmpPoly.fx.emplace_back(*iterator1 * *iterator2);

				++iterator2;
			}

			++iterator1;
		}

		TmpPoly.fx.sort();

		auto iteratorx = TmpPoly.fx.begin();
		auto iterator3 = ++TmpPoly.fx.begin();

		bool Delete = false;

		while (iterator3 != TmpPoly.fx.end())
		{
			if (*iteratorx == *iterator3)
			{
				Delete = true;

				*iteratorx += *iterator3;
			}
			else
			{
				++iteratorx;

				if (Delete)
				{
					iteratorx = TmpPoly.fx.erase(iteratorx, iterator3);

					Delete = false;
				}
			}

			++iterator3;
		}

		TmpPoly.vL = P1.vL;

		return TmpPoly;
	}

	constexpr dynamic_array<std::string> var_list()const
	{
		return vL;
	}

private:

	constexpr void upgrade_poly(polynomial& p1, polynomial& p2)const noexcept
	{
		//std::cout << "Upgrade poly cost\n";

		dynamic_array<std::string> TmpVarlist = p1.vL;

		int64 n1 = p1.vL.size(), n2 = p2.vL.size(), i, j;

		dynamic_array<int64> TmpPosition; int64 TmpIndex = n1;

		// Code for upgrade variable list

		for (j = 0; j < n2; ++j)
		{
			for (i = 0; i < n1; ++i)
			{
				if (p1.vL[i] == p2.vL[j])
				{
					TmpPosition.push_back(i);

					break;
				}
			}

			if (i == n1)
			{
				TmpPosition.push_back(TmpIndex++);

				TmpVarlist.push_back(p2.vL[j]);
			}
		}

		// Code for upgrade P1 Polynomial

		int64 n3 = TmpVarlist.size() - p1.vL.size();

		for (auto& pair_ : p1.fx)
		{
			for (int64 i = 0; i < n3; ++i)
			{
				pair_.expo.push_back(0);
			}
		}

		p1.vL = TmpVarlist;

		// Code for upgrade P2 Polynomial

		dynamic_array<int64> TmpExpo(TmpVarlist.size(), 0);

		for (auto& pair_ : p2.fx)
		{
			for (int64 i = 0; i < pair_.expo.size(); ++i)
			{
				TmpExpo[TmpPosition[i]] = pair_.expo[i];
			}
				
			pair_.expo = TmpExpo;

			for (auto& e : TmpExpo)
			{
				e = 0;  // reset TmpExpo;
			}
		}

		p2.vL = TmpVarlist;

		return;
	}

public:

	constexpr void printExpo(const dynamic_array<int64>& x)const noexcept
	{
		int64 index = 0;

		for (const auto& i : x)
		{
			if (i != 0)
				if (i != 1)
					std::cout << vL[index] << '^' << i;
				else std::cout << vL[index];
			index++;
		}
	}

	constexpr void printdata()const noexcept
	{
		std::cout << "\nVarible List : ";

		for (const auto& str : vL)
			std::cout << str << " ";

		std::cout << "\nF(";

		for (const auto& var : vL)
			std::cout << var << " ";

		std::cout << ") = ";

		for (const auto& pair : fx)
			std::cout << " + (" << pair.coeff << ")",
			printExpo(pair.expo);
	}

	constexpr void print(const bool yes = true)const noexcept
	{
		std::cout << "\nF(";
		if (yes)
			for (const auto& var : vL)
				std::cout << var << " ";

		std::cout << ") = ";

		for (const auto& pair : fx)
			std::cout << " + (" << pair.coeff << ")",
			printExpo(pair.expo);
	}

};

template<class arr_type> std::ostream& operator << (std::ostream& cout, const polynomial<arr_type>& p)noexcept
{
	p.print(false); return cout;
}

inline polynomial<integer> random_polynomial(const int64 var_count) {

	dynamic_array<std::string> var_array(var_count);

	std::string* var_array_ptr = var_array.data();

	for (int64 i = 0; i < var_count; ++i)
	{
		*(var_array_ptr + i) = "x" + std::to_string(i);
	}
	
	std::list<std::pair<integer, dynamic_array<int64>>> node_list;

	for (int64 i = 0; i < var_count; ++i)
	{
		node_list.emplace_back(random_integer(20), random_int(1, 9, var_count));
	}

	node_list.emplace_back(random_integer(200), random_int(0, 0, var_count));

	return polynomial(node_list, var_array);
}


