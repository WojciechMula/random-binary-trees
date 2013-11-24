def prepare_data(data, get_key):
	tmp = [get_key(x) for x in data]
	tmp.sort()

	ordered = []

	def aux(a, b):
		if a > b:
			return

		c = (a + b)/2
		ordered.append(tmp[c])

		aux(a, c - 1)
		aux(c + 1, b)

	aux(0, len(tmp) - 1)

	return ordered
