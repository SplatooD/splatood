import sys

use_rle = False
if "--rle" in sys.argv:
	use_rle = True

out = []

previous = "NO"
count = 0

with open(sys.argv[1]) as f:
	x = f.read()
	for i in x:
		c = hex(ord(i))
		if len(c) == len('0x0'):
			c = c[:2] + '0' + c[2]
		if use_rle:
			if c == previous:
				count += 1
			else:
				if count:
					out.append( hex(count) )
					out.append( previous )
				count = 1
				previous = c
		else:
			out.append( c )
	if use_rle and count:
		out.append( hex(count) )
		out.append( previous )

print "const unsigned char __rename_me__[",len(out),"] = {",",".join(out),"};"
