# -*- coding: utf-8 -*-
import numpy as np

SEG_NO_CHECK_VALUE = -1
SEG_TANTEN_LIST = [
    np.array([
        [0, 0, 0],
        [0, 1, 0],
        [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
    ]),
    np.array(
        [
            [SEG_NO_CHECK_VALUE, 0, 0],
            [1, 1, 0],
            [SEG_NO_CHECK_VALUE, 0, 0],
        ]),
    np.array(
        [
            [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
            [0, 1, 0],
            [0, 0, 0],
        ]),
    np.array(
        [
            [0, 0, SEG_NO_CHECK_VALUE],
            [0, 1, 1],
            [0, 0, SEG_NO_CHECK_VALUE],
        ]),
    np.array(
        [
            [0, 0, 0],
            [0, 1, 0],
            [1, 0, 0],
        ]),
    np.array(
        [
            [1, 0, 0],
            [0, 1, 0],
            [0, 0, 0],
        ]),
    np.array(
        [
            [0, 0, 1],
            [0, 1, 0],
            [0, 0, 0],
        ]),
    np.array(
        [
            [0, 0, 0],
            [0, 1, 0],
            [0, 0, 1],
        ])
]

SEG_BUNKI_3_LIST = [
    np.array(
        [
            [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
            [1, 1, 1],
            [0, 0, 0],
        ]),
    np.array(
        [
            [0, 1, SEG_NO_CHECK_VALUE],
            [0, 1, 1],
            [0, 1, SEG_NO_CHECK_VALUE],
        ]),
    np.array(
        [
            [0, 0, 0],
            [1, 1, 1],
            [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
        ]),
    np.array(
        [
            [SEG_NO_CHECK_VALUE, 1, 0],
            [1, 1, 0],
            [SEG_NO_CHECK_VALUE, 1, 0],
        ]),
    np.array(
        [
            [1, 0, 0],
            [0, 1, 0],
            [1, 0, 1],
        ]),
    np.array(
        [
            [1, 0, 1],
            [0, 1, 0],
            [1, 0, 0],
        ]),
    np.array(
        [
            [1, 0, 1],
            [0, 1, 0],
            [0, 0, 1],
        ]),
    np.array(
        [
            [0, 0, 1],
            [0, 1, 0],
            [1, 0, 1],
        ]),
]

SEG_BUNKI_4_LIST = [
    np.array(
        [
            [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
            [1, 1, 1],
            [SEG_NO_CHECK_VALUE, 1, SEG_NO_CHECK_VALUE],
        ]),
    np.array(
        [
            [1, 0, 1],
            [0, 1, 0],
            [1, 0, 1],
        ]),
]

SEG_KORITSU_LIST = [
    np.array(
        [
            [0, 0, 0],
            [0, 1, 0],
            [0, 0, 0],
        ]),
]

SEGMENT_LIST = [
    [[0, 0, 255], SEG_TANTEN_LIST],
    [[0, 255, 0], SEG_BUNKI_3_LIST],
    [[255, 0, 0], SEG_BUNKI_4_LIST],
    [[255, 0, 255], SEG_KORITSU_LIST]
]
