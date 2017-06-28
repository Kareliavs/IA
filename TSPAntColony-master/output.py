'''Algo tester'''

from os import *
import time
import readfiles as rf

def antAlgo():
    
    system('g++ TSPConstructor.cpp -o TSPConstructor')
    system('./TSPConstructor')
    system('g++ antal.cpp -o antal')

    #t1 = time()
    
    system('./antal')

    rf.cityRead()


antAlgo()
    
    

    

