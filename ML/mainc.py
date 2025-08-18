import cv2 as cv
import numpy as np

img = cv.imread("girl_bg.jpg")
cv.imshow("syndey", img)

# rescaling and resizing
"""
def rescaleImage(image, scale=0.5):
    width = int(image.shape[1]*scale)
    height = int(image.shape[0]*scale)
    dimensions = (width, height)
    return cv.resize(image, dimensions, interpolation=cv.INTER_AREA)

resizedImage = rescaleImage(img, scale=0.8)
cv.imshow("Resized Image", resizedImage)
"""

# Drawing on images
blankimg = np.zeros((500,500,3), dtype = 'uint8')
# cv.imshow("blank image", blankimg)

#opencv color scheme : BGR (blue,green,red)
# cv.rectangle(blankimg, (0,0), (250,250), (0, 0, 255), thickness = -1)
# cv.imshow("blank image", blankimg)

#drawing a circle
"""
cv.circle(blankimg, (250, 250), 40, (255, 0, 0), thickness = -1)
cv.imshow("circle", blankimg)
"""
# adding text in the image
"""
cv.putText(blankimg, "THIS IS A DISCUSSION", (0,100), cv.FONT_HERSHEY_TRIPLEX, 1.0,(0,255,0), thickness = 3)
cv.imshow("text", blankimg)
"""
#cropping an image
"""
img = img[50:100, 20:30]
cv.imshow("cropped image", img)
"""

# Y = 0.29R + 0.58G + 0.11B E (0,255)
#converting to b/w
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow("gray", gray)

#blurring the image
blur = cv.GaussianBlur(gray, (5,5), cv.BORDER_DEFAULT)
cv.imshow("BLUR", blur)

#initiating minions
minion = cv.imread("cat.jpg")
cv.imshow("minion", minion)

#canning minions
minion_gray = cv.cvtColor(minion, cv.COLOR_BGR2GRAY)
canny_minion = cv.Canny(minion_gray, 125, 175)
cv.imshow("cannied minion", canny_minion)



cv.waitKey(0)