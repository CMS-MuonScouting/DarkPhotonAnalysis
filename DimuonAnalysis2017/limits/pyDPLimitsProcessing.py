import os
import subprocess
import commands

m=10.
for d in range(0,300):
	m=m+(m*0.01)

	if d<90 or d>112:
		continue
	
	os.system("combine -M AsymptoticLimits dpCard"+str(d)+".txt -m "+str(m)+" -S 0 --run blind")	
	
