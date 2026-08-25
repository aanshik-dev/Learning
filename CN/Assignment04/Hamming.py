def check_Parity(stream, r, i):
    tot = 0
    j = 2**i-1
    while(j < len(stream)):
      for k in range(2**i):
        if(j == len(stream)):
          break
        tot += stream[j]
        j += 1
      for k in range(2**i):
        if(j == len(stream)):
          break
        j += 1
    if tot%2 == 0:
      return True
    else:
      return False


def hamming_encode(data):
  """
  # data = [ 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1]
  # 1 0 1 0 0 1 1 0 0 1  1  0  1  1  0  0  0  1  1
  # P P 1 P 0 1 1 P 0 1  1  0  1  1  0  P  0  1  1
  """
  m = len(data)  # 14
  r = 0  # 5
  # Calculate number of parity bit
  while (2 ** r) < (m + r + 1):
      r += 1
  # initalizing 0 stream
  stream = [0] * (m + r)  # 19
  data_ptr = 0
  pwr = 0

  # placing data bits at pos other then parity
  for i in range(len(stream)):
      if 2 ** pwr == i+1:
          stream[i] = 0
          pwr += 1
      else:
          stream[i] = data[data_ptr]
          data_ptr += 1

  # Calculating parity and then placing at pos
  i = 0
  while i < r:
      stream[2**i-1] = 0 if check_Parity(stream, r, i) else 1
      i += 1
  return stream, r

def recover(stream):
  i = 0
  binPos = []
  sol = []
  errPos = 0
  while i < r:
    bit = int(not check_Parity(stream, r, i))
    binPos.append(bit)
    i += 1
  
  # Binary to Decimal
  for i in range(len(binPos)):
    errPos += binPos[i] * 2**i

  # Flipping the bit
  if errPos != 0:
    stream[errPos-1] = stream[errPos-1]^1

  # Removing the parity bits
  recoveredCode = stream.copy()
  for i in range(r - 1, -1, -1):
    recoveredCode.pop(2**i - 1)
  
  return stream, errPos, recoveredCode


data = [1,0,1,1,0,1,1,0,1,1,0,0,1,1]
data = list(map(int, input("Enter Binary Data : ")))

print(f'Data: {data}')
stream, r = hamming_encode(data)
print(f'Hamming Code: {stream}')

# User input to flip the bit
flip = int(input(f'Enter the bit pos to flip: [1 - {len(stream)}] : '))
while  flip < 0 or flip > len(stream):
  flip = int(input(f'Invalid Bit position! Please choose from [1 - {len(stream)}] : '))

corrupted = stream.copy()
if(flip != 0):
  corrupted[flip-1] = corrupted[flip-1]^1
  print(f'Corrupted transmission: {corrupted}')
else:
  print(f'Clean transmission: {corrupted}')

recoveredCode, errPos, recovered = recover(corrupted)
print(f'Error bit position (Syndrome): {errPos}\nRecovered hamming code: {recoveredCode}\nRecovered data: {recovered}')
