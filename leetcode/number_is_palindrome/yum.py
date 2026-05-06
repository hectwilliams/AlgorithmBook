
def isPalindrome( x: int) -> bool:

    # this apprach does not use strings 

    if x < 0:
	return False 
    if x == 0:
	return True

    a = x #copy 

    num_digits = math.floor(math.log10(a)) + 1

    index = 0
    eff_index = 0 

    effective_mid = math.floor(num_digits / 2)  
    isOdd = int(num_digits % 2  == 1)
    arr = [0] * (effective_mid + isOdd)

    isvalid = True
    forward_index = 0
    reverse_index = 0

    while 1:
	
	v = (a % 10 )
	
	if forward_index != effective_mid:
	    arr[forward_index] = v

	if forward_index < effective_mid:
	    forward_index += 1
	    reverse_index = forward_index + isOdd
	    
	elif reverse_index > 0:
	    reverse_index -= 1
	    
	    if reverse_index != effective_mid:
		# print(  f" index: {reverse_index} expect: {arr[reverse_index] }  variable { v}"  )  
		# if odd  length, skip reading the middle value !
		isvalid =  (arr[reverse_index] ==v) and isvalid
	    
	else:
	    
	    break

	a = int(a/10)    

    return isvalid
