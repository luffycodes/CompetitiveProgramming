t = int(raw_input())
while(t>0):
	a = raw_input().split(" ")
	try:
		m = int(a[0])
		n = int(a[1])
		val1 = m/2
		val2 = n/2
		val1 = n*val1
		val2 = m*val2
		if(val1<val2):
			print m*n-val1
		else:
			print m*n-val2
		#if(m<n):
		#	if(m%2==1):
		#		m = m/2 +1
		#	else:
		#		m = m/2
		#	print m*n
		#else:
		#	if(n%2==1):
		#		n = n/2 +1
		#	else:
		#		n = n/2
		#	print n*m
		t = t-1
	except ValueError:
		t = t
