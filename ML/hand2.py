import cv2
import mediapipe as mp
import time
import random
import serial

class HandDetector():
    def __init__(self, mode = False, maxHands = 2,modelComplexity =1, detectionCon= float(0.5), trackingCon = float(0.5)):
        self.mode = mode
        self.maxHands = maxHands
        self.modelComplexity = modelComplexity
        self.detectionCon = detectionCon
        self.trackingCon = trackingCon

        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands(self.mode, self.maxHands, self.modelComplexity, self.detectionCon, self.trackingCon)
        self.mpDraw = mp.solutions.drawing_utils

    def findHands(self, img, draw=True):
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(imgRGB)

        if draw:
            if self.results.multi_hand_landmarks:
                for handLms in self.results.multi_hand_landmarks:
                    for id, lm in enumerate(handLms.landmark):
                        h, w, c = img.shape
                        cx, cy = int(lm.x*w), int(lm.y*h)
                        print(id, cx, cy)

                        random.seed(int(id))
                        color = (random.randint(0,255), random.randint(0,255), random.randint(0,255))
                        cv2.circle(img, (cx, cy), 15, color, cv2.FILLED)
                    self.mpDraw.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)
        return img
    def findPosition(self, img, handNo = 0, draw = True):
        imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(imgRGB)
        lmList = []
        if self.results.multi_hand_landmarks:
            myHand = self.results.multi_hand_landmarks[handNo]
            for id, lm in enumerate(myHand.landmark):
                h, w, c = img.shape
                cx, cy = int(lm.x*w), int(lm.y*h)
                print(id, cx, cy)
                lmList.append([id, cx, cy])
                if draw:
                    cv2.circle(img, (cx, cy), 15, (255, 0, 255), cv2.FILLED)
            self.mpDraw.draw_landmarks(img, myHand, self.mpHands.HAND_CONNECTIONS)

        return lmList
def main():
    pTime = 0
    cTime = 0
    cap = cv2.VideoCapture(0)
    detector = HandDetector()
    arduino = serial.Serial(port='COM5', baudrate=9600, timeout=.01)
    while True:
        success, img = cap.read()
        # img = detector.findHands(img)
        lmList = detector.findPosition(img,draw = False)
        if len(lmList) != 0:
            # Get coordinates of landmark 9
            x, y = lmList[9][1], lmList[9][2]  # [1] is x-coordinate, [2] is y-coordinate

            # Format the data to send (e.g., "x,y\n")
            data = f"{x},{y}\n"

            # Send the data to Arduino
            arduino.write(data.encode())

            # Print the data being sent (for debugging)
            print(f"Sending to Arduino: {data.strip()}")
        cTime = time.time()
        fps = 1/(cTime-pTime)
        pTime = cTime
        img = cv2.flip(img, 1)
        cv2.putText(img, str(int(fps)), (10, 70), cv2.FONT_HERSHEY_PLAIN,
            3, (255, 0, 255), 3)
        cv2.imshow("Image", img)
        cv2.waitKey(1)
if __name__ == "__main__":
    main()
