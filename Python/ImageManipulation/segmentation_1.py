import matplotlib.pyplot as plt
import matplotlib.image as mimg
import cv2 as cv
import skimage
import scipy
from skimage import filters, feature
from skimage.segmentation import felzenszwalb, slic, quickshift, watershed, mark_boundaries

def brain(scr):
    base_image = mimg.imread("brain_tumor.bmp")
    image_2 = cv.threshold(base_image, 130, 255, cv.THRESH_BINARY)[1]
    image_3 = cv.threshold(base_image, 130, 255, cv.THRESH_OTSU)[1]
    image_5 = cv.threshold(base_image, 130, 255, cv.THRESH_TRUNC)[1]
    image_6 = cv.threshold(base_image, 130, 255, cv.THRESH_TOZERO)[1]
    images = ((0, base_image, "original"), (1, image_2, "thresh_binary"),
              (2, image_3, "thresh_otsu"),
              (3, image_5, "trunc"), (4, image_6, "tozero"))
    for index, image, description in images:
        plt.subplot(2, 3, index + 1)
        plt.imshow(image, 'gray')
        plt.title(description)
        plt.xticks([])
        plt.yticks([])
    plt.show()
    image_7 = cv.adaptiveThreshold(base_image, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 11, 2)
    image_8 = cv.adaptiveThreshold(base_image, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY, 11, 2)
    images = (
        (0, image_7, "Gaussian"),
        (1, image_8, "Mean")
    )
    for index, image, description in images:
        plt.subplot(1, 2, index + 1)
        plt.imshow(image, 'gray')
        plt.title(description)
        plt.xticks([])
        plt.yticks([])
    plt.show()

# brain("brain_tumor.bmp")

def segmentation(scr):
    low = 0.1
    high = 0.35
    base_image = mimg.imread(scr)
    image2 = feature.canny(base_image)
    image3 = filters.sobel(base_image)
    lowt = (image3 > low).astype(int)
    hight = (image3 > high).astype(int)
    image4 = filters.prewitt(base_image)
    image5 = filters.apply_hysteresis_threshold(image3, low, high)
    image6 = scipy.ndimage.binary_fill_holes(image5)
    images = (
        (0, base_image, "original"),
        (1, image2, "canny"),
        (2, image3, "sobel"),
        (3, image4, "prewitt"),
        (4, lowt, "low"),
        (5, hight, "hight"),
        (6, image5, "hysteresis_threshold"),
        (7, image6, "binary_fill_holes")
    )
    for index, image, description in images:
        plt.subplot(3, 3, index + 1)
        plt.imshow(image, 'gray')
        plt.title(description)
        plt.xticks([])
        plt.yticks([])
    plt.show()

#segmentation("gears.bmp")

def klastry(scr):
    base_image = mimg.imread(klastry("fish.bmp"))
    felzen_filter = felzenszwalb(base_image, scale=100, sigma=0.5, min_size=50)
    image2 = mark_boundaries(base_image, felzen_filter)
    slic_filter = slic(base_image, n_segments=159, compactness=25, sigma=2)
    image3 = mark_boundaries(base_image, slic_filter)
    quickshift_filter = quickshift(base_image, kernel_size=3, max_dist=6, ratio=0.5)
    image4 = mark_boundaries(base_image, quickshift_filter)
    gray_filter = filters.sobel(skimage.color.rgb2gray(base_image))
    watershed_filter = watershed(gray_filter, markers=159, compactness=0.00001)
    image5 = mark_boundaries(base_image, watershed_filter)
    images = (
        (0, base_image, 'base'),
        (1, image2, 'felzenszwalb'),
        (2, image3, 'slic'),
        (3, image4, 'sobel'),
        (4, image5, 'watershed')
    )
    for index, image, description in images:
        plt.subplot(3, 2, index + 1)
        plt.imshow(image)
        plt.title(description)
        plt.xticks([])
        plt.yticks([])
    plt.show()

klastry("fish.bmp")
