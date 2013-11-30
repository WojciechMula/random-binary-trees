#include <unordered_map>

class StlUnorderedMapAdapter {
	public:
		typedef std::unordered_map<string_t, string_t> unordered_map_t;
		unordered_map_t map;

		StlUnorderedMapAdapter() : map() {}

		bool insert(const string_t string) {
			map[string] = string;
			
			return true;
		}

		bool find(const string_t string) {
			return map.count(string);
		}
};

