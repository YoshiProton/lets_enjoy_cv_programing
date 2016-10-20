# -*- coding: utf-8 -*-

import util
import cv2
import numpy as np
import const

IMG_DIR = "../img/"

if __name__ == '__main__':
    try:
        img_path = IMG_DIR + "tegaki.jpg"
        # 画像読み込み
        img = util.ImageProcessing.loadImg(img_path)
        # グレースケール画像に変換
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        # 2値化処理
        ret, th_img = cv2.threshold(gray_img, 128, 255, cv2.THRESH_BINARY)
        # 細線化処理 9-3-2
        thin_img = util.ImageProcessing.thinning(th_img)
        # セグメント処理 9-3-3
        seg_img = util.ImageProcessing.segment(thin_img)
        # ベクトル化 9-3-4
        # 間に合いませんでした

        cv2.imwrite("gray.jpg", gray_img)
        cv2.imwrite("thresh.jpg", th_img)
        cv2.imwrite("thining.jpg", thin_img)
        disp_seg_img = np.zeros((seg_img.shape[0], seg_img.shape[1], 3), np.uint8)
        for point in np.argwhere(seg_img != [0,0,0]):
            cv2.circle(disp_seg_img, (point[1], point[0]), 5, seg_img[point[0], point[1]].tolist(), -1)
        cv2.imwrite("segment.jpg", disp_seg_img)
    except Exception as e:
        print str(e)
