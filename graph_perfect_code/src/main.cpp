// Graph Perfect Code

#include <person.hpp>


graph public_key; // Global Variable

void GenerateB1(dynamic_array<polynomial<integer>>& B1, const dynamic_array<std::string>& var_vec) {

	dynamic_array<int64> expo(vertexCount, 0ll);

	std::list<std::pair<integer, dynamic_array<int64>>> pair_list;

	dynamic_array<dynamic_array<int64>> N = public_key.adj_list();

	for (int64 v = 0; v < vertexCount; ++v)
	{
		for (const auto& u : N[v])
		{
			expo[u] = 1ll;

			pair_list.emplace_back(-1ll, expo);

			expo[u] = 0ll;
		}

		pair_list.emplace_back(1ll, expo);

		B1.emplace_back(pair_list, var_vec);

		pair_list.clear();
	}
}

void GenerateB2(dynamic_array<polynomial<integer>>& B2, const dynamic_array<std::string>& var_vec)
{
	dynamic_array<int64> expo(vertexCount, 0ll); int64 size = 0ll;

	dynamic_array<dynamic_array<int64>> N = public_key.adj_list();

	for (int64 v = 0; v < vertexCount; ++v)
	{
		size = N[v].size();

		// code for generate all possible combination of uu' such that u,u' in N[v]

		for (int64 i = 0; i < size; ++i)
		{
			for (int64 j = i + 1; j < size; ++j)
			{
				expo[N[v][i]] = 1ll;
				expo[N[v][j]] = 1ll;

				B2.emplace_back(1ll, expo, var_vec);

				expo[N[v][i]] = 0ll;
				expo[N[v][j]] = 0ll;
			}
		}
	}
}

int main()
{

	Person Alice;

	public_key = Alice.public_key();

	std::cout << "\n\nPublic Key : " << public_key;

	std::cout << "\n\nprivate Key";  Alice.private_key();

	int64 edgeCount = public_key.edge_count();

	std::string message;  input(message);

	integer message_num = ConvertMessageToInteger(message);

	dynamic_array<polynomial<integer>> B1; B1.reserve(1 * vertexCount);
	dynamic_array<polynomial<integer>> B2; B2.reserve(edgeCount * (2 * edgeCount - 1) / 2);

	dynamic_array<std::string> var = var_vec(vertexCount);

	GenerateB1(B1, var);
	GenerateB2(B2, var);

	polynomial<integer> sum_pol1 = { 0ll, var };
	polynomial<integer> sum_pol2 = { 0ll, var };

	for (int64 i = 0; i < vertexCount; ++i)
	{
		sum_pol1 += B1[i];
	}

	for (int64 i = 0; i < 3 * vertexCount; ++i)
	{
		sum_pol2 += B2[i];
	}

	polynomial<integer> cipher_text =
		sum_pol1 * random_polynomial(20) +
		sum_pol2 * random_polynomial(20) + polynomial<integer>(message_num, var);

	std::cout << "Cipher Text is : " << cipher_text;

	std::cout << Alice.message(cipher_text);

	
	std::cin.get();
	std::cin.get();

	return 0;

}

