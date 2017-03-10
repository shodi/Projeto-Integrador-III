#!/usr/bin/env python

import sys

POSSIBLE_ARRAY = ['A', 'B', 'C', 'D', 'E']

class Config:
	def __init__(self):
		self._atendentes = None
		self.postos = None
		self.__time_for_change = None
	
	def checkIntegrity(self):
		counter = 0
		for key in self.postos:
			counter += self.postos[key]['qtd']
		return True if self._atendentes is counter else False

def relations(dictionary, line):
	for i in POSSIBLE_ARRAY:
		dictionary.postos[i] = dict()
		dictionary.postos[i]['relation'] = line.count(i)

def quantity(obj, line):
	for i in POSSIBLE_ARRAY:
		obj.postos[i]['qtd'] = line.count(i)

def main(file_name):
	with open(file_name, 'r') as fp:
		config = Config()
		for i in xrange(4):
			if i is 0:
				config._atendentes = int(fp.readline())
			if i is 1:
				config.postos = dict()
				line = fp.readline()[3:]
				relations(config, line)
			if i is 2:
				line = fp.readline()[3:]
				quantity(config, line)	
				if not config.checkIntegrity():
					print 'Something went wrong'
			if i is 3:
				config.__time_for_change = int(fp.readline()[6:])
			if i is 4:
				line = fp.readline()
				while line is not "":
					config.postos[line[:1]]['time_to_attend'] = int(line[1:2])
					config.postos[line[:1]]['name'] = line[3:]
							

if __name__ == '__main__':
	main(sys.argv[1])
