#include <map>

class StlMapAdapter {
	public:
		typedef std::map<string_t, string_t> map_t;
		map_t map;

		StlMapAdapter() : map() {}

		bool insert(const string_t string) {
			map[string] = string;
			
			return true;
		}

		bool find(const string_t string) {
			return map.count(string);
		}
};
