# Face detection Code

import cv2 as cv

img = cv.imread("girl_bg.jpg")
cv.imshow("Girl", img)

grey = cv.cvcolor(img, cv.COLOR_BGR2GRAY)
cv.imshow("Grey Girl", grey)

haar_cascade = cv.CascadeClassifier("haar_face.xml")
faces= haar_cascade.detectMultiScale(grey, scaleFactor = 1.2 )