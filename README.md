Experiments performed for this assignemt were using two different set of test inputs
running in 4096(0x1000) bytes of memory
1st test input using only allocations
A:0:512:A    
A:1:1024:B   
A:2:2048:C   
A:3:256:D    
using first fit:
chunk 0 location : 512 bytes - allocated
chunk 512 location : 1024 bytes - allocated
chunk 1536 location : 2048 bytes - allocated
chunk 3584 location : 256 bytes - allocated
chunk 3840 location : 216 bytes - free
3840 bytes allocated
216 bytes free
using best fit:
chunk 0 location : 512 bytes - allocated
chunk 512 location : 1024 bytes - allocated
chunk 1536 location : 2048 bytes - allocated
chunk 3584 location : 256 bytes - allocated
chunk 3840 location : 216 bytes - free
3840 bytes allocated
216 bytes free
using worst fit:
chunk 0 location : 512 bytes - allocated
chunk 512 location : 1024 bytes - allocated
chunk 1536 location : 2048 bytes - allocated
chunk 3584 location : 256 bytes - allocated
chunk 3840 location : 216 bytes - free
3840 bytes allocated
216 bytes free
2nd test input:
A:0:800:A    
A:1:1200:B   
A:2:400:C    
F:1           
A:3:600:D    
F:0           
A:4:1000:E   
running in 4096(0x1000) bytes of memory
using first fit:
chunk 0 location : 800 bytes - free
chunk 800 location : 600 bytes - allocated
chunk 1400 location : 600 bytes - free
chunk 2000 location : 400 bytes - allocated
chunk 2400 location : 1000 bytes - allocated
chunk 3400 location : 656 bytes - free
2000 bytes allocated
2056 bytes free
using best fit:
chunk 0 location : 800 bytes - free
chunk 800 location : 600 bytes - allocated
chunk 1400 location : 600 bytes - free
chunk 2000 location : 400 bytes - allocated
chunk 2400 location : 1000 bytes - allocated
chunk 3400 location : 656 bytes - free
2000 bytes allocated
2056 bytes free
using worst fit:
chunk 0 location : 800 bytes - free
chunk 800 location : 1000 bytes - allocated
chunk 1800 location : 200 bytes - free
chunk 2000 location : 400 bytes - allocated
chunk 2400 location : 600 bytes - allocated
chunk 3000 location : 1056 bytes - free
2000 bytes allocated
2056 bytes free
3rd test input: using Large and Small Allocations
A:0:2000:A  
A:1:500:B    
A:2:1000:C   
F:0           
A:3:300:B    
using first fit:
chunk 0 location : 300 bytes - allocated
chunk 300 location : 1700 bytes - free
chunk 2000 location : 500 bytes - allocated
chunk 2500 location : 1000 bytes - allocated
chunk 3500 location : 556 bytes - free
1800 bytes allocated
2256 bytes free
using best fit:
chunk 0 location : 2000 bytes - free
chunk 2000 location : 500 bytes - allocated
chunk 2500 location : 1000 bytes - allocated
chunk 3500 location : 300 bytes - allocated
chunk 3800 location : 256 bytes - free
1800 bytes allocated
2256 bytes free
using worst case:
chunk 0 location : 300 bytes - allocated
chunk 300 location : 1700 bytes - free
chunk 2000 location : 500 bytes - allocated
chunk 2500 location : 1000 bytes - allocated
chunk 3500 location : 556 bytes - free
1800 bytes allocated
2256 bytes free
Final report:
based on my experiments in my code, 
the least overall number of chunks: all three algorithms have the same number of chunks in each three experiment
Greatest Number of Successful Allocations: all three algorithms handle the same number of successful allocations in each three experiments
