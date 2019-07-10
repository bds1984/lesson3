#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using vector_const_iter=std::vector<std::string>::const_iterator;

std::vector<std::string> split(std::string&& str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.emplace_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.emplace_back(str.substr(start));

    return r;
	
}

int main(int, char **)
{
	try
	{
		std::vector<std::vector<std::string> > ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			std::vector<std::string> v = split(std::move(line), '\t');
			ip_pool.emplace_back(split(std::move(v.at(0)), '.'));
		}

// My reverse lexicographically sort BEGIN
		//std::sort with my self-made comparator (lambda)

		std::sort( ip_pool.begin(), ip_pool.end(),	[](std::vector<std::vector<std::string>>::const_iterator& frst, std::vector<std::vector<std::string>>::const_iterator& scnd) {
			
			bool ret_res { false };
			vector_const_iter iter_frst {};
			vector_const_iter iter_scnd {};

			for (iter_frst = frst.cbegin(), iter_scnd = scnd.cbegin(); iter_frst != frst.cend(), iter_scnd != scnd.cend(); )
			{
				if (std::stoi(*iter_frst) == std::stoi(*iter_scnd)) { ++iter_frst; ++iter_scnd; }
				   
				else if (std::stoi(*iter_frst) > std::stoi(*iter_scnd)) { ret_res = true; break; }
				
				else { ret_res = false; break; }
			}
			return ret_res;
			});

//My reverse lexicographically sort END

//filters  BEGIN
		decltype(ip_pool) ip_pool_filter_1;        //temporary storage for filter 1
		ip_pool_filter_1.reserve(ip_pool.size());

		decltype(ip_pool) ip_pool_filter_46_70;   //temporary storage for filter 46,70
		ip_pool_filter_46_70.reserve(ip_pool.size());

		decltype(ip_pool) ip_pool_filter_any_46;  //temporary storage for filter any 46
		ip_pool_filter_any_46.reserve(ip_pool.size());


		for (const auto& iter : ip_pool) 
		{
			//filter 1
			if (std::stoi(*iter.cbegin()) == 1) { ip_pool_filter_1.emplace_back(iter); }

			//filter 46,70 
			if (std::stoi(*iter.cbegin()) == 46 && std::stoi( *(iter.cbegin() + 1) ) == 70) { ip_pool_filter_46_70.emplace_back(iter); }

			//filter any 46
			if(
				std::stoi( *iter.cbegin() ) == 46 || 
				std::stoi( *(iter.cbegin() + 1) ) == 46 ||
				std::stoi( *(iter.cbegin() + 2) ) == 46 || 
				std::stoi( *(iter.cbegin() + 3) ) == 46   
				) { ip_pool_filter_any_46.emplace_back(iter); }

		}

		for (const auto& iter : ip_pool_filter_1) { ip_pool.emplace_back(iter); }
		ip_pool_filter_1.resize(0);

		for (const auto& iter : ip_pool_filter_46_70) { ip_pool.emplace_back(iter); }
		ip_pool_filter_46_70.resize(0);

		for (const auto& iter : ip_pool_filter_any_46) { ip_pool.emplace_back(iter); }
		ip_pool_filter_any_46.resize(0);

//filters  END
		
		for(const auto& ip:ip_pool)
		{
			for (vector_const_iter ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
			{
				if (ip_part != ip.begin())
				{
					std::cout << ".";
				}
				std::cout << *ip_part;
			}
			std::cout <<std::endl;
		}
		
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
