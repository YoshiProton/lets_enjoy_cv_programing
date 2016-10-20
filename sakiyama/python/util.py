# -*- coding: utf-8 -*-

import cv2
import numpy as np
from scipy import weave
import const
import math
import sys


class ImageProcessing:
    # 細線化の補助プログラミング
    @classmethod
    def _thinningIteration(cls, im, iter):
        # Cに渡す入力画像をI,戻り値をMとする
        I, M = im, np.zeros(im.shape, np.uint8)

        # N{I}でIのshapeを取得
        # I2でIが二次元配列であることを指定
        # アルゴリズムが謎、みんなに相談しよう
        expr = """
        for (int i = 1; i < NI[0]-1; i++) {
            for (int j = 1; j < NI[1]-1; j++) {
                int p2 = I2(i-1, j);
                int p3 = I2(i-1, j+1);
                int p4 = I2(i, j+1);
                int p5 = I2(i+1, j+1);
                int p6 = I2(i+1, j);
                int p7 = I2(i+1, j-1);
                int p8 = I2(i, j-1);
                int p9 = I2(i-1, j-1);
                int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                         (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                         (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                         (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
                int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
                int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);
                if (A == 1 && B >= 2 && B <= 6 && m1 == 0 && m2 == 0) {
                    M2(i,j) = 1;
                }
            }
        }
        """

        weave.inline(expr, ["I", "iter", "M"])

        return (I & ~M)

    # 細線化
    @classmethod
    def thinning(cls, src):
        # 画素値を0~1にする
        dst = src.copy() / 255
        # 入力画像と同じサイズの真っ黒画像を用意
        prev = np.zeros(src.shape[:2], np.uint8)

        while True:
            dst = cls._thinningIteration(dst, 0)
            dst = cls._thinningIteration(dst, 1)
            diff = np.absolute(dst - prev)
            prev = dst.copy()
            if np.sum(diff) == 0:
                break

        return dst * 255

    @classmethod
    def loadImg(cls, fileName, flags=1):
        img = cv2.imread(fileName, flags)
        if img is None:
            print "invalid input_file_full_path : " + fileName
            exit()
        return img

    @classmethod
    def segment(cls, img):

        bin_img = img / 255

        seg_img = np.zeros((img.shape[0],img.shape[1],3)).astype(np.uint8)

        for v in const.SEGMENT_LIST:

            color, segment_list = v

            for segment in segment_list:

                rows, cols = bin_img.shape

                #ここが古典的なフィルタリングのforで気持ち悪い
                for row in range(1, rows - 1):
                    for col in range(1, cols - 1):

                        v = 0

                        for i in range(3):
                            for j in range(3):

                                if segment[i, j] == const.SEG_NO_CHECK_VALUE or \
                                                segment[i, j] == bin_img[row + i - 1, col + j - 1]:
                                    v += 1

                        if v == 9:
                            seg_img[row, col] = color
        return seg_img
