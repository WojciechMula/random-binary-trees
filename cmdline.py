from optparse import OptionParser
from key_function import functions

def get_options(argv):
	parser = OptionParser()

	parser.add_option('-k',
		help='name of key function',
		type='choice',
		choices=sorted(functions.keys()),
		dest='key',
	)

	parser.add_option('-f',
		help='input text file',
		action='store',
		dest='file',
	)

	parser.add_option('-s',
		help='sort file lines',
		action='store_true',
		dest='sort',
		default=False,
	)
	
	parser.add_option('-l',
		help='limit number of lines processed by program',
		type='int',
		dest='limit',
		default=0,
	)

	parser.add_option('-i',
		help='show depths histogram',
		action='store_true',
		dest='histogram',
		default=False,
	)

	(options, parameters) = parser.parse_args(argv)

	validate(options, parser)

	return options


def validate(options, parser):
	if not options.file:
		parser.error('-f is required')	

	if not options.key:
		parser.error('-k is required')	

	options.key_function = functions[options.key]
