 def findMedianSortedArrays(nums1: List[int], nums2: List[int]) -> float:
        
        length = len(nums1) + len(nums2) 
        
        if length <=1:
            return (nums1 or nums2 )[0]

        isEven = length % 2  == 0

        midpoint = math.floor(length / 2) - int(isEven)
        
        n_values = 2 if isEven else 1 # even (2 values ) , odd 1 value 
        
        index = 0
        target_1 = 0
        target_2 = 0 
        
        while nums1 or nums2:
            
            value = 0

            # get single min of lists at each state
            if nums2 and nums1:
                if nums2[0] < nums1[0]:
                    value = nums2.pop(0)
                else:
                    value = nums1.pop(0)
            elif nums2:
                value = nums2.pop(0)
            elif nums1:
                value = nums1.pop(0)
        
            if index == midpoint:
                target_1 = value 
            if index == midpoint + 1:
                target_2 = value
                break 
            
            index+= 1

        if n_values == 1:
            return target_1
            
        if n_values == 2:
            return (target_1 + target_2) / 2
