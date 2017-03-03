#!/usr/bin/env python

import sys

__author__ = 'shodi'

def formater(text_line):
	index_C = text_line.index('C')
	index_A = text_line.index('A')
	__id = text_line[1:index_C]
	__arrival_time = text_line[index_C + 1:index_A]
	__stages = text_line[index_A:]
	print ("%s\n%s\n%s" %(__id, __arrival_time, __stages))

def main(file_name, client_id):
	with open(file_name, 'r') as fp:
		line = fp.readline()
		while not line.startswith('U' + str(client_id)):
			line = fp.readline()
			if line == '':
				print 'ID fora do range'
				return
		formater(line)
		
if __name__=='__main__':
	main(sys.argv[1], sys.argv[2])
