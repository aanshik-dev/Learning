def xor_div(stream, gen):
  """
  stream = message bits + appended zeros
  gen = generator polynomial bits
  returns the remainder after mod-2 division
  """
  rem = stream.copy()
  glen = len(gen)
  i = 0
  while i <= len(rem) - glen:
    if rem[i] == 1:
      for j in range(glen):
        rem[i+j] = rem[i+j] ^ gen[j]
    i += 1
  return rem[-(glen-1):]


def crc_encode(msg, gen):
  glen = len(gen)
  appended = msg + [0]*(glen-1)
  rem = xor_div(appended, gen)
  frame = msg + rem
  return frame, rem


def crc_check(frame, gen):
  rem = xor_div(frame, gen)
  accepted = True
  for bit in rem:
    if bit != 0:
      accepted = False
  return rem, accepted


msg = list(map(int, input("Enter Message : ")))
gen = list(map(int, input("Enter Generator : ")))

print(f'Message: {msg}')
print(f'Generator: {gen}')

frame, rem = crc_encode(msg, gen)
print(f'CRC Remainder: {rem}')
print(f'Transmitted Frame: {frame}')

rem_check, accepted = crc_check(frame, gen)
print(f'Receiver check on clean frame -> remainder {rem_check} -> {"ACCEPT" if accepted else "REJECT"}')

flip = int(input(f'Enter the bit pos to flip: [1 - {len(frame)}] : '))
while flip < 0 or flip > len(frame):
  flip = int(input(f'Invalid Bit position! Please choose from [1 - {len(frame)}] : '))

corrupted = frame.copy()
if flip != 0:
  corrupted[flip-1] = corrupted[flip-1]^1
  print(f'Corrupted transmission: {corrupted}')
else:
  print(f'Clean transmission: {corrupted}')

rem_corrupt, accepted_corrupt = crc_check(corrupted, gen)
print(f'Receiver check on corrupted frame -> remainder {rem_corrupt} -> {"ACCEPT" if accepted_corrupt else "REJECT"}')