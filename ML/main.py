import cv2 as cv
import numpy as np

img = cv.imread('girl_bg.jpg')
cv.imshow("CAT", img)

# Drawing on images
blankimg = np.zeros((500, 500, 3), dtype='uint8')
# cv.imshow("Blank Image", blankimg)

# rescaling and resizing
def rescaleImage(image, scale= 0.5):
      width = int(image.shape[1] * scale)
      height = int(image.shape[0] * scale)
      dimensions = (width, height)
      return cv.resize(image, dimensions, interpolation=cv.INTER_AREA)

resizeImage = rescaleImage(img, scale = 0.8)
# cv.imshow("Resized Image", resizeImage)

# opencv color scheme : BGR (Blue, Green, Red)
cv.rectangle(blankimg, (0, 0), (250, 250), (0, 255, 0), thickness=3)
# cv.imshow("Rectangle", blankimg)

#cropping an image
img = img[50:100, 20:30]
# cv.imshow("Cropped Image", img)

# adding text in an image
cv.putText(blankimg, "Discussion", (0, 100), cv.FONT_HERSHEY_TRIPLEX, 1.0, (255, 255, 255), 2)
# cv.imshow("img", blankimg)

# Black and white
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
# cv.imshow("grey", gray)

blur = cv.GaussianBlur(gray, (5,5), cv.BORDER_DEFAULT)
# cv.imshow("BLUR", blur)

girl = cv.imread("girl_bg.jpg")
# cv.imshow("girl", girl)

girl_gray = cv.cvtColor(girl, cv.COLOR_BGR2GRAY)
canny_girl = cv.Canny(girl_gray, 125, 175)
cv.imshow("cannied minion", canny_girl)

#laplacian method 
lap_girl = cv.Laplacian(girl_gray, cv.CV_64F)
# cv.imshow("Lapped Girl", lap_girl)

# sobel method 
sobelX = cv.Sobel(girl_gray, cv.CV_64F, 1,0)
sobelY = cv.Sobel(girl_gray, cv.CV_64F, 0,1)
combineSobel = cv.bitwise_or(sobelX, sobelY)

cv.imshow("Sobel Girl", sobelX)
cv.imshow("Sobel Girl", sobelY)
cv.imshow("Combined Girl", combineSobel)

# thresholds 
_, thresh = cv.threshold(girl, 150, 255, cv.THRESH_BINARY)
cv.imshow("threshold Girl", thresh)

# Contours 
contours, hierarchies = cv.

cv.waitKey(0)