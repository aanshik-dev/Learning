import cv2
import mediapipe as mp
import time
import random

cap = cv2.VideoCapture(0)

mpHands = mp.solutions.hands
hands = mpHands.Hands(False, 1) 
mpDraw = mp.solutions.drawing_utils

while True:
 success, img = cap.read()
 imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
 results = hands.process(imgRGB)
 lmlist = []
 if results.multi_hand_landmarks:
  for handLms in results.multi_hand_landmarks:
   for id, lm in enumerate(handLms.landmark):
    h, w, c = img.shape
    cx, cy = int(lm.x*w), int(lm.y*h)
    print(id, cx, cy)
    """
    finding the correct landmark:

    for id, lm in enumerate(handLms.landmark):
        cx, cy = int(lm.x * w), int(lm.y * h)
        cv2.putText(img, str(id), (cx, cy), cv2.FONT_HERSHEY_SIMPLEX, 
                    0.5, (0, 255, 0), 1, cv2.LINE_AA)
    """
    if id == 9:
     cv2.circle(img, (cx, cy), 15, (255, 120, 255), cv2.FILLED)
     print(id, cx, cy)
     mpDraw.draw_landmarks(img, handLms, mpHands.HAND_CONNECTIONS)  
 cv2.imshow("Image", img)
 cv2.waitKey(1)    