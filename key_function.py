from random import randint, seed
from hash.fnv import get as fnv_hash
from zlib import crc32, adler32   
import hashlib
from hashlib import md5

def get_key_no_transform(value):
	return value
	
def get_key_hash(value):
	return value.__hash__()

def get_key_random(value):
	seed(value.__hash__())

	return randint(0, 2**32)

def get_key_md5(value):
	m = hashlib.md5()
	m.update(value)

	return m.digest()


functions = {
	'none'		: get_key_no_transform,
	'hash'		: get_key_hash,
	'random'	: get_key_random,
	'fnv'		: fnv_hash,
	'crc32'		: crc32,
	'adler32'	: adler32,
	'md5'		: get_key_md5,
}
