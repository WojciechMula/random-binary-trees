from sys import argv
from optparse import OptionParser
from random import randint, choice, seed

def main(options):
	chars = 'abcdefghijklmnopqrstuvwxyz' + \
		    'ABCDEFGHIJKLMNOPQRSTUVWXYZ' + \
			'0123456789' + \
			'./-'

	if options.seed is not None:
		seed(options.seed)

	def pred():
		return randint(0, 100) > (100 - options.share_prefix_prob)

	previous = ''
	for i in xrange(options.count):
		curr = ''
		if pred:
			k = randint(0, options.max_length - options.min_length)
			curr = previous[:k]

		length = randint(options.min_length, options.max_length) - len(curr)
		if length > 0:
			curr = curr + ''.join(choice(chars) for j in xrange(length))
		else:
			curr = curr + choice(chars)

		print curr

		previous = curr


def get_options(argv):
	parser = OptionParser(usage="""%prog [options]

Generate lines of random strings""")

	parser.add_option('-s', '--seed',
		help='random generator seed',
		type='int',
		dest='seed'
	)

	parser.add_option('-c', '--count',
		help='lines count [default: %default]',
		type='int',
		dest='count',
		default=10000
	)

	parser.add_option('--min',
		help='min string length [default: %default]',
		type='int',
		dest='min_length',
		default=3
	)

	parser.add_option('--max',
		help='max string length [default: %default]',
		type='int',
		dest='max_length',
		default=150
	)
	
	parser.add_option('--share-prefix-prob',
		help='probability [0..100] of sharing some prefix with previously generated string [default: %default]',
		type='int',
		dest='share_prefix_prob',
		default=50,
	)

	(options, parameters) = parser.parse_args(argv)

	return options


if __name__ == '__main__':
	options = get_options(argv[1:])
	main(options)
