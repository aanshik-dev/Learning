<div style= "width: 100%; background-image: linear-gradient(90deg,rgb(20, 0, 36),rgb(31, 0, 56),rgb(66, 13, 94)); background-size: contain;">
<div style= "backdrop-filter: blur(15px) brightness(150%); padding: 25px" >

# 🐦‍🔥🔥 **DSA NOTES** 🔥🐦‍🔥

<br>

## 🐦‍🔥 KADANE'S ALGORITHM

> Kadane's Algorithm: It says that, if the sum of Sub Array becomes negative then adding it to further elements will decrease the Max possible sum, so it is better to reset it to 0.
> Problem: Given an array of integers, find the Maximum Sum of Sub Array.
> Algorithm:
> 🔸 `Iterate & add each value to 'sum'`
> 🔸 `Update 'maxSum' with 'max(sum, maxSum)'`
> 🔸 `Set 'sum = 0' if 'sum < 0'`


```cpp
  vector<int> vect = {1, -2, 6, 45, 7, 3, -24, 11, -14};
  int sum = 0, maxSum = INT_MIN, st = 0, end = 0;
  for (int i = 0; i < vect.size(); i++) {
    sum += vect[i];
    if (sum > maxSum) {
      maxSum = sum;
      end = i;
    }
    if (sum < 0) {
      st = i + 1;
      sum = 0;
    }
  }
  cout << maxSum << st << end << endl ;
```

</div>
</div>
