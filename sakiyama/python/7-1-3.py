# -*- coding: utf-8 -*-

import cv2
import numpy as np
import math

def loadImg(fileName, flags = 1):
    img = cv2.imread(fileName, flags)
    if(len(img.shape) == 2):
        rows, cols = img.shape
    else:
        rows, cols, depth = img.shape
    if rows == 0 or cols == 0:
        print "invalid input_file_full_path : " + fileName
        exit()
    return img

def imshowOnFFT(title, img):
    a = np.log(np.abs(img) ** 2)
    cv2.imshow(title, (a / a.max() * 255).astype(np.uint8))

def filter2DOnFFT(img, kernel):
    imgs = cv2.split(img)
    rtns = []
    for im in imgs:
        f_im = np.fft.fftshift(np.fft.fft2(im))

        k_f_im = kernel * f_im
        # replace division by zero (NaN) with zeroes
        k_f_im = np.nan_to_num(k_f_im)

        # showOnFFT("k_f_im", k_f_im)

        f_inv = np.fft.ifft2(np.fft.ifftshift(k_f_im))

        f_inv = np.abs(f_inv)

        f_inv = np.where(f_inv < 0, 0, f_inv)
        f_inv = np.where(f_inv > 255, 255, f_inv)

        rtns.append(f_inv)

    rtn = cv2.merge(rtns)
    rtn = rtn.astype(np.uint8)

    return rtn

def makeBokeFilter(rows, cols, sigma, is_center = True):
    sigma2 = 2 * sigma ** 2
    kernel = np.ones((rows, cols), np.float32) / (math.pi * sigma2)
    for i in range(0, rows):
        row2 = (float(i - rows / 2) / rows) ** 2 if(is_center) else (float(i) / rows) ** 2
        for j in range(0, cols):
            col2 = (float(j - cols / 2) / cols) ** 2 if(is_center) else (float(j) / cols) ** 2
            v = -1 * (col2 + row2) / sigma2
            v = math.exp(v)
            kernel[i, j] = kernel[i, j] * v

    kernel = kernel / kernel.max()
    kernel = kernel / kernel.sum()

    return kernel

def makeWienerFilter(rows, cols, sigma, tau = 0):
    kernel = makeBokeFilter(rows, cols, sigma, False)
    fftK = np.fft.fftshift(np.fft.fft2(kernel))
    fftK_ = np.conj(fftK)
    powerH2 = np.abs(fftK) ** 2

    return fftK_ / (powerH2 + tau)


if __name__ == '__main__':
    try:
        img_path = "../img/test_b.jpg"
        img = loadImg(img_path)

        if (len(img.shape) == 2):
            rows, cols = img.shape
        else:
            rows, cols, depth = img.shape

        sigma = 0.005
        kernel = makeBokeFilter(rows, cols, sigma)

        #畳み込み積分でボケ画像を生成
        boke = cv2.filter2D(img, -1, kernel)
        boke = boke.astype(np.uint8)

        #周波数領域でボケ画像を生成
        k = makeBokeFilter(rows, cols, sigma, False)
        f_kernel = np.fft.fftshift(np.fft.fft2(k))
        boke_on_f = filter2DOnFFT(img, f_kernel)

        # cv2.imshow("or", img)
        # cv2.imshow("boke", boke)
        # cv2.imshow("boke_on_f", boke_on_f)
        cv2.imwrite("boke.png", boke)
        cv2.imwrite("boke_on_f.png", boke_on_f)

        tau = 0.1
        wiener = makeWienerFilter(rows, cols, sigma, tau)

        fukugen_boke = filter2DOnFFT(boke, wiener)
        fukugen_boke_of_f = filter2DOnFFT(boke_on_f, wiener)

        cv2.imwrite("fukugen_boke.png", fukugen_boke)
        cv2.imwrite("fukugen_boke_of_f.png", fukugen_boke_of_f)


    except Exception as e:
        print str(e)