from random import randint, seed

def get_key_plain(value):
	return value
	
def get_key_hash(value):
	return value.__hash__()

def get_key_random(value):
	seed(value.__hash__())

	return randint(0, 2**32)


functions = {
	'value'		: get_key_plain,
	'hash'		: get_key_hash,
	'random'	: get_key_random,
}
