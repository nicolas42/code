# Image url ==> https://upload.wikimedia.org/wikipedia/en/7/7d/Lenna_%28test_image%29.png
# Download the image and save it as 'lena.png' in your directory
import cv2
import numpy as np
import math
import matplotlib.pyplot as plt
src = cv2.imread('../Lenna.png')
img = cv2.cvtColor(src, cv2.COLOR_BGR2RGB)
plt.figure(figsize=(8, 5))
plt.axis("off")
plt.imshow(img)
