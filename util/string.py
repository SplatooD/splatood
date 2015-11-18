import codecs

out = []
for i in codecs.encode(raw_input()):
	out.append(hex(ord(i)+0x80))

out.append("0x00");

print "{",",".join(out),"};"
